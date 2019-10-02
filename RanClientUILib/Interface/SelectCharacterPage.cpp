#include "StdAfx.h"
#include "SelectCharacterPage.h"
#include "SelectCharacterInfoPage.h"
#include "BasicTextButton.h"
#include "GameTextControl.h"
#include "BasicLineBox.h"
#include "OuterInterface.h"
#include "DxGlobalStage.h"
#include "ModalWindow.h"
#include "DxLobyStage.h"
#include "UITextControl.h"
#include "RANPARAM.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "./DxLobyStage.h"
#include "CharacterEnum.h"
#include "d3dfont.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSelectCharacterPage::CSelectCharacterPage ()
	: m_pStartButton(NULL)
	, m_pNewButton(NULL)
	, m_pCancelButton(NULL)
	, m_pDeleteButton(NULL)
	, m_pBasicLineBox(NULL)
	, m_pNameStatic(NULL)
	, m_pBasicLineBoxServer(NULL)
	, m_pBasicLineBoxSelect(NULL)
	, m_uCharRemain ( USHRT_MAX )
	, m_pCharInfoBack(NULL)
	, m_nPosition(-1)
	, Select(-1)
	, MousePose(D3DXVECTOR3(0.0f,0.0f,0.0f))
	, m_pFirstPosition(NULL)
	, HaveCharacter_A(FALSE)
	, HaveCharacter_B(FALSE)
	, HaveCharacter_C(FALSE)
	, HaveCharacter_D(FALSE)
	, DelChar(FALSE)
{
	memset ( m_pCharacterPosition, 0, sizeof( CUIControl* ) * 4 );
	memset ( m_pCharacterPositionSet, 0, sizeof( CUIControl* ) * 4 );
	memset ( m_pCharacterClassPos1, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pCharacterClassSetPos1, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pCharacterClassPos2, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pCharacterClassSetPos2, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pCharacterClassPos3, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pCharacterClassSetPos3, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pCharacterClassPos4, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pCharacterClassSetPos4, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST );
	memset ( m_pNameClassPos, 0, sizeof( CBasicTextBox* ) * 4 );
	memset ( m_pNameClass, 0, sizeof( CBasicTextBox* ) * 4 );
	memset ( m_pLevelClass, 0, sizeof( CBasicTextBox* ) * 4 );
}

CSelectCharacterPage::~CSelectCharacterPage ()
{
}

void CSelectCharacterPage::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont10 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );


	CSelectCharacterInfoPage* pSelectCharacterPage = new CSelectCharacterInfoPage;
	pSelectCharacterPage->CreateSub ( this, "BASIC_WINDOW", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pSelectCharacterPage->CreateBaseWindowBlackRed ( "SELECT_CHARACTER_UPWINDOW", (char*)ID2GAMEWORD("SELECT_CHARACTER_PAGE") );
	pSelectCharacterPage->CreateSubControl ();
	RegisterControl ( pSelectCharacterPage );
	m_pSelectCharacterPage = pSelectCharacterPage;

	const int nBUTTONSIZE = CBasicTextButton::SIZE40;


	//พื้นหลังเลือกตัวละคร
	{
		m_pBasicLineBoxSelect = new CBasicLineBox;
		m_pBasicLineBoxSelect->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBoxSelect->CreateBaseBoxOuter ( "SELECT_CHARACTER_PAGE_DOWNBACK2" );
		RegisterControl ( m_pBasicLineBoxSelect );
	}
	//พื้นหลัง
	{
		m_pBasicLineBox = new CBasicLineBox;
		m_pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox->CreateBaseBoxOuter ( "SELECT_CHARACTER_PAGE_DOWNBACK" );
		RegisterControl ( m_pBasicLineBox );
	}
	//พื้นหลัง Server
	{
		m_pBasicLineBoxServer = new CBasicLineBox;
		m_pBasicLineBoxServer->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBoxServer->CreateBaseBoxOuter ( "SELECT_CHARACTER_PAGE_DOWNBACK_SERVER" );
		RegisterControl ( m_pBasicLineBoxServer );
	}
	{
		m_pNameStatic = new CBasicTextBox;
		m_pNameStatic->CreateSub ( this, "SELECT_CHARACTER_PAGE_SERVER_CHANEL", UI_FLAG_DEFAULT );
		m_pNameStatic->SetFont ( pFont9 );
		m_pNameStatic->AddText( ID2GAMEEXTEXT("SELECT_CHARACTER_PAGE_SERVER_CHANEL"), NS_UITEXTCOLOR::WHITE );
		m_pNameStatic->SetTextAlign ( TEXT_ALIGN_LEFT );		
		RegisterControl ( m_pNameStatic );
	}
	//ปุ่มเริ่ม
	{
		m_pStartButton = new CBasicTextButton;
		m_pStartButton->CreateSub ( this, "BASIC_TEXT_BUTTON40", UI_FLAG_XSIZE, SELECT_CHARACTER_START );
		m_pStartButton->CreateBaseButton ( "SELECT_CHARACTER_START", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "SELECT_CHARACTER_PAGE_BUTTON", 1 ) );
		m_pStartButton->SetShortcutKey ( DIK_RETURN, DIK_NUMPADENTER );
		RegisterControl ( m_pStartButton );
	}
	//ปุ่มยกเลิก
	{
		m_pCancelButton = new CBasicTextButton;
		m_pCancelButton->CreateSub ( this, "BASIC_TEXT_BUTTON40", UI_FLAG_XSIZE, SELECT_CHARACTER_CANCEL );
		m_pCancelButton->CreateBaseButton ( "SELECT_CHARACTER_CANCEL", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "SELECT_CHARACTER_PAGE_BUTTON", 3 ) );
		m_pCancelButton->SetShortcutKey ( DIK_ESCAPE );
		RegisterControl ( m_pCancelButton );
	}
	//ปุ่มสร้างตัวละครใหม่
	{
		m_pNewButton = new CBasicTextButton;
		m_pNewButton->CreateSub ( this, "BASIC_TEXT_BUTTON40", UI_FLAG_XSIZE, SELECT_CHARACTER_NEW );
		m_pNewButton->CreateBaseButton ( "SELECT_CHARACTER_NEW", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "SELECT_CHARACTER_PAGE_BUTTON", 0 ) );		
		RegisterControl ( m_pNewButton );
	}
	//ปุ่มลบตัวละคร
	{
		m_pDeleteButton = new CBasicTextButton;
		m_pDeleteButton->CreateSub ( this, "BASIC_TEXT_BUTTON40", UI_FLAG_XSIZE, SELECT_CHARACTER_DELETE );
		m_pDeleteButton->CreateBaseButton ( "SELECT_CHARACTER_DELETE", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "SELECT_CHARACTER_PAGE_BUTTON", 2 ) );
		m_pDeleteButton->SetShortcutKey ( DIK_DELETE );
		RegisterControl ( m_pDeleteButton );
	}
	CString strTemp;

	for ( int i = 0 ; i < 4; ++i ) 
	{
		strTemp.Format ("SELECT_PAGE_CHARACTER_POSITION%d",i); 	
		m_pCharacterPosition[i] = new CUIControl;
		m_pCharacterPosition[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE, SELECT_PAGE_CHARACTER_POSITION0 + i );
		m_pCharacterPosition[i]->SetVisibleSingle ( FALSE );
		m_pCharacterPosition[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_pCharacterPosition[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_SET_POSITION%d",i); 	
		m_pCharacterPositionSet[i] = new CUIControl;
		m_pCharacterPositionSet[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pCharacterPositionSet[i]->SetVisibleSingle ( FALSE );
		m_pCharacterPositionSet[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_pCharacterPositionSet[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_CLASS_NAME%d",i); 
		m_pNameClassPos[i] = new CBasicTextBox;
		m_pNameClassPos[i]->CreateSub ( this, strTemp, UI_FLAG_DEFAULT );
		m_pNameClassPos[i]->SetFont ( pFont9 );
		m_pNameClassPos[i]->SetTextAlign ( TEXT_ALIGN_LEFT );		
		RegisterControl ( m_pNameClassPos[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_NAME%d",i); 
		m_pNameClass[i] = new CBasicTextBox;
		m_pNameClass[i]->CreateSub ( this, strTemp, UI_FLAG_DEFAULT );
		m_pNameClass[i]->SetFont ( pFont9 );
		m_pNameClass[i]->SetTextAlign ( TEXT_ALIGN_LEFT );		
		RegisterControl ( m_pNameClass[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_CLASS_LEVEL%d",i); 
		m_pLevelClass[i] = new CBasicTextBox;
		m_pLevelClass[i]->CreateSub ( this, strTemp, UI_FLAG_DEFAULT );
		m_pLevelClass[i]->SetFont ( pFont9 );
		m_pLevelClass[i]->SetTextAlign ( TEXT_ALIGN_LEFT );		
		RegisterControl ( m_pLevelClass[i] );


	}

	for ( int i = 0 ; i < GLCI_NUM_NEWEST; ++i ) 
	{
		strTemp.Format ("SELECT_PAGE_CHARACTER_POS1_CLASS%d",i); 	
		m_pCharacterClassPos1[i] = new CUIControl;
		m_pCharacterClassPos1[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassPos1[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassPos1[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_POS1_CLASS_SET%d",i); 	
		m_pCharacterClassSetPos1[i] = new CUIControl;
		m_pCharacterClassSetPos1[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassSetPos1[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassSetPos1[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_POS2_CLASS%d",i); 	
		m_pCharacterClassPos2[i] = new CUIControl;
		m_pCharacterClassPos2[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassPos2[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassPos2[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_POS2_CLASS_SET%d",i); 	
		m_pCharacterClassSetPos2[i] = new CUIControl;
		m_pCharacterClassSetPos2[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassSetPos2[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassSetPos2[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_POS3_CLASS%d",i); 	
		m_pCharacterClassPos3[i] = new CUIControl;
		m_pCharacterClassPos3[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassPos3[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassPos3[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_POS3_CLASS_SET%d",i); 	
		m_pCharacterClassSetPos3[i] = new CUIControl;
		m_pCharacterClassSetPos3[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassSetPos3[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassSetPos3[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_POS4_CLASS%d",i); 	
		m_pCharacterClassPos4[i] = new CUIControl;
		m_pCharacterClassPos4[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassPos4[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassPos4[i] );

		strTemp.Format ("SELECT_PAGE_CHARACTER_POS4_CLASS_SET%d",i); 	
		m_pCharacterClassSetPos4[i] = new CUIControl;
		m_pCharacterClassSetPos4[i]->CreateSub ( this, strTemp, UI_FLAG_XSIZE | UI_FLAG_YSIZE);
		m_pCharacterClassSetPos4[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCharacterClassSetPos4[i] );
	}
}

BOOL CSelectCharacterPage::SndGameJoin ()
{
	SCHARINFO_LOBBY* pCharInfo = DxGlobalStage::GetInstance().GetLobyStage()->GetSelectCharInfo();
	if ( pCharInfo )		//ผฑลรวั ฤณธฏลอฐก ภึดย ฐๆฟ์
	{
		DxGlobalStage::GetInstance().GetNetClient()->SndGameJoin ( pCharInfo->m_dwCharID );

		COuterInterface::GetInstance().START_WAIT_TIME ( 60.0f );
		DoModalOuter ( ID2GAMEEXTEXT ("CHARACTERSTAGE_GAME_JOIN"), MODAL_INFOMATION, CANCEL, OUTER_MODAL_CHARACTERSTAGE_GAME_JOIN_WAIT );
		return TRUE;
	}

	return FALSE;
}

void CSelectCharacterPage::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{
		AddMessageEx ( UIMSG_MOUSEIN_SELECT_CHARACTERPAGE );
	}

	switch ( ControlID )
	{
	case SELECT_CHARACTER_START:
		{
			DxLobyStage * pLobbyStage = DxGlobalStage::GetInstance().GetLobyStage();

			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				if ( !SndGameJoin()|| !pLobbyStage->IsCharSelect() )
				{
					DoModalOuter ( ID2GAMEEXTEXT ("CHARACTERSTAGE_8"), MODAL_INFOMATION, OK );
				}
			}
		}
		break;
	case SELECT_CHARACTER_CANCEL:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				DoModalOuter ( ID2GAMEEXTEXT ("CHARACTERSTAGE_6"), MODAL_INFOMATION, OKCANCEL, OUTER_MODAL_LOGOUT );
				DelChar = TRUE;
			}
		}
		break;
	case SELECT_CHARACTER_NEW:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				const USHORT uCharRemain = COuterInterface::GetInstance().GetCharRemain ();
				const int nChaSNum = DxGlobalStage::GetInstance().GetLobyStage()->GetChaSNum ();

				if ( MAX_ONESERVERCHAR_NUM <= nChaSNum )
				{
					DoModalOuter ( ID2GAMEEXTEXT ("CHARACTER_THIS_SERVER_SLOT_FULL" ), MODAL_INFOMATION );
					break;
				}
				if ( !uCharRemain )
				{
					DoModalOuter ( ID2GAMEEXTEXT ("CHARACTER_NOT_ENOUGH_CHARREMAIN" ), MODAL_INFOMATION );
					break;
				}
				if (m_nPosition > -1)
				{
					m_pCharacterPositionSet[m_nPosition]->SetVisibleSingle ( FALSE );
					m_pCharacterPosition[m_nPosition]->SetVisibleSingle ( TRUE );

					if (m_nPosition == 0)
					{
						//pCharInfoA = charA;
						const CString strClassName1 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoA->m_emClass)].c_str();
						CString strName1;
						strName1.Format("%s",pCharInfoA->m_szName);
						m_pNameClassPos[0]->ClearText();
						m_pNameClassPos[0]->SetText( strClassName1, NS_UITEXTCOLOR::SILVER );
						m_pNameClass[0]->ClearText();
						m_pNameClass[0]->SetText( strName1, NS_UITEXTCOLOR::SILVER );

						strName1.Format("Lv.%d",pCharInfoA->m_wLevel);
						m_pLevelClass[0]->ClearText();
						m_pLevelClass[0]->SetText( strName1, NS_UITEXTCOLOR::SILVER );

						if( pCharInfoA->m_emClass == GLCC_FIGHTER_M )
						{
							m_pCharacterClassPos1[0]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[0]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_ARMS_M )
						{
							m_pCharacterClassPos1[1]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[1]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_ARCHER_W )
						{
							m_pCharacterClassPos1[2]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[2]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_SPIRIT_W )
						{
							m_pCharacterClassPos1[3]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[3]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_EXTREME_M )
						{
							m_pCharacterClassPos1[4]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[4]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_EXTREME_W )
						{
							m_pCharacterClassPos1[5]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[5]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_FIGHTER_W )
						{
							m_pCharacterClassPos1[6]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[6]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_ARMS_W )
						{
							m_pCharacterClassPos1[7]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[7]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_ARCHER_M )
						{
							m_pCharacterClassPos1[8]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[8]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_SPIRIT_M )
						{
							m_pCharacterClassPos1[9]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[9]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_SCIENCE_M )
						{
							m_pCharacterClassPos1[10]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[10]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_SCIENCE_W )
						{
							m_pCharacterClassPos1[11]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[11]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_M )
						{
							m_pCharacterClassPos1[12]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[12]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_W )
						{
							m_pCharacterClassPos1[13]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[13]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_TESTING_M )
						{
							m_pCharacterClassPos1[14]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[14]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoA->m_emClass == GLCC_TESTING_W )
						{
							m_pCharacterClassPos1[15]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos1[15]->SetVisibleSingle ( FALSE );
						}
					}
					else if (m_nPosition == 1)
					{
						//pCharInfoB = charB;
						const CString strClassName2 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoB->m_emClass)].c_str();
						CString strName2;
						strName2.Format("%s",pCharInfoB->m_szName);
						m_pNameClassPos[1]->ClearText();
						m_pNameClassPos[1]->SetText( strClassName2, NS_UITEXTCOLOR::SILVER );
						m_pNameClass[1]->ClearText();
						m_pNameClass[1]->SetText( strName2, NS_UITEXTCOLOR::SILVER );

						strName2.Format("Lv.%d",pCharInfoB->m_wLevel);
						m_pLevelClass[1]->ClearText();
						m_pLevelClass[1]->SetText( strName2, NS_UITEXTCOLOR::SILVER );

						if( pCharInfoB->m_emClass == GLCC_FIGHTER_M )
						{
							m_pCharacterClassPos2[0]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[0]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_ARMS_M )
						{
							m_pCharacterClassPos2[1]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[1]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_ARCHER_W )
						{
							m_pCharacterClassPos2[2]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[2]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_SPIRIT_W )
						{
							m_pCharacterClassPos2[3]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[3]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_EXTREME_M )
						{
							m_pCharacterClassPos2[4]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[4]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_EXTREME_W )
						{
							m_pCharacterClassPos2[5]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[5]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_FIGHTER_W )
						{
							m_pCharacterClassPos2[6]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[6]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_ARMS_W )
						{
							m_pCharacterClassPos2[7]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[7]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_ARCHER_M )
						{
							m_pCharacterClassPos2[8]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[8]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_SPIRIT_M )
						{
							m_pCharacterClassPos2[9]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[9]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_SCIENCE_M )
						{
							m_pCharacterClassPos2[10]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[10]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_SCIENCE_W )
						{
							m_pCharacterClassPos2[11]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[11]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_M )
						{
							m_pCharacterClassPos2[12]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[12]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_W )
						{
							m_pCharacterClassPos2[13]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[13]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_TESTING_M )
						{
							m_pCharacterClassPos2[14]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[14]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoB->m_emClass == GLCC_TESTING_W )
						{
							m_pCharacterClassPos2[15]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos2[15]->SetVisibleSingle ( FALSE );
						}
					}
					else if (m_nPosition == 2)
					{
						//pCharInfoC = charC;
						const CString strClassName3 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoC->m_emClass)].c_str();
						CString strName3;
						strName3.Format("%s",pCharInfoC->m_szName);
						m_pNameClassPos[2]->ClearText();
						m_pNameClassPos[2]->SetText( strClassName3, NS_UITEXTCOLOR::SILVER );
						m_pNameClass[2]->ClearText();
						m_pNameClass[2]->SetText( strName3, NS_UITEXTCOLOR::SILVER );

						strName3.Format("Lv.%d",pCharInfoC->m_wLevel);
						m_pLevelClass[2]->ClearText();
						m_pLevelClass[2]->SetText( strName3, NS_UITEXTCOLOR::SILVER );

						if( pCharInfoC->m_emClass == GLCC_FIGHTER_M )
						{
							m_pCharacterClassPos3[0]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[0]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_ARMS_M )
						{
							m_pCharacterClassPos3[1]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[1]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_ARCHER_W )
						{
							m_pCharacterClassPos3[2]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[2]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_SPIRIT_W )
						{
							m_pCharacterClassPos3[3]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[3]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_EXTREME_M )
						{
							m_pCharacterClassPos3[4]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[4]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_EXTREME_W )
						{
							m_pCharacterClassPos3[5]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[5]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_FIGHTER_W )
						{
							m_pCharacterClassPos3[6]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[6]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_ARMS_W )
						{
							m_pCharacterClassPos3[7]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[7]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_ARCHER_M )
						{
							m_pCharacterClassPos3[8]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[8]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_SPIRIT_M )
						{
							m_pCharacterClassPos3[9]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[9]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_SCIENCE_M )
						{
							m_pCharacterClassPos3[10]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[10]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_SCIENCE_W )
						{
							m_pCharacterClassPos3[11]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[11]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_M )
						{
							m_pCharacterClassPos3[12]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[12]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_W )
						{
							m_pCharacterClassPos3[13]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[13]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_TESTING_M )
						{
							m_pCharacterClassPos3[14]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[14]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoC->m_emClass == GLCC_TESTING_W )
						{
							m_pCharacterClassPos3[15]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos3[15]->SetVisibleSingle ( FALSE );
						}
					}
					else if (m_nPosition == 3)
					{
						//pCharInfoD = charD;
						const CString strClassName4 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoD->m_emClass)].c_str();
						CString strName4;
						strName4.Format("%s",pCharInfoD->m_szName);
						m_pNameClassPos[3]->ClearText();
						m_pNameClassPos[3]->SetText( strClassName4, NS_UITEXTCOLOR::SILVER );
						m_pNameClass[3]->ClearText();
						m_pNameClass[3]->SetText( strName4, NS_UITEXTCOLOR::SILVER );

						strName4.Format("Lv.%d",pCharInfoD->m_wLevel);
						m_pLevelClass[3]->ClearText();
						m_pLevelClass[3]->SetText( strName4, NS_UITEXTCOLOR::SILVER );

						if( pCharInfoD->m_emClass == GLCC_FIGHTER_M )
						{
							m_pCharacterClassPos4[0]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[0]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_ARMS_M )
						{
							m_pCharacterClassPos4[1]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[1]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_ARCHER_W )
						{
							m_pCharacterClassPos4[2]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[2]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_SPIRIT_W )
						{
							m_pCharacterClassPos4[3]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[3]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_EXTREME_M )
						{
							m_pCharacterClassPos4[4]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[4]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_EXTREME_W )
						{
							m_pCharacterClassPos4[5]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[5]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_FIGHTER_W )
						{
							m_pCharacterClassPos4[6]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[6]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_ARMS_W )
						{
							m_pCharacterClassPos4[7]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[7]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_ARCHER_M )
						{
							m_pCharacterClassPos4[8]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[8]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_SPIRIT_M )
						{
							m_pCharacterClassPos4[9]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[9]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_SCIENCE_M )
						{
							m_pCharacterClassPos4[10]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[10]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_SCIENCE_W )
						{
							m_pCharacterClassPos4[11]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[11]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_M )
						{
							m_pCharacterClassPos4[12]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[12]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_W )
						{
							m_pCharacterClassPos4[13]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[13]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_TESTING_M )
						{
							m_pCharacterClassPos4[14]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[14]->SetVisibleSingle ( FALSE );
						}
						else if( pCharInfoD->m_emClass == GLCC_TESTING_W )
						{
							m_pCharacterClassPos4[15]->SetVisibleSingle ( TRUE );
							m_pCharacterClassSetPos4[15]->SetVisibleSingle ( FALSE );
						}
					}

					m_nPosition = -1;
				}

				COuterInterface::GetInstance().ToCreateCharacterPage ( GetWndID () );
			}
		}
		break;
	case SELECT_CHARACTER_DELETE:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_pDelCharInfo = DxGlobalStage::GetInstance().GetLobyStage()->GetSelectCharInfo();
				int m_pNumChar = DxGlobalStage::GetInstance().GetLobyStage()->GetChaSNum();
				if ( m_pDelCharInfo )
				{
					CString strTemp;					

					switch ( RANPARAM::emSERVICE_TYPE )
					{
					case EMSERVICE_DEFAULT:
					case EMSERVICE_INDONESIA:
					case EMSERVICE_FEYA:
					case EMSERVICE_THAILAND:
					case EMSERVICE_CHINA:
						strTemp = COuterInterface::GetInstance().MakeString ( ID2GAMEEXTEXT ("CHARACTERSTAGE_CAUTION_DELETE"), m_pDelCharInfo->m_szName );
						DoModalOuter ( strTemp.GetString(), MODAL_INPUT, EDITBOX, OUTER_MODAL_SECONDPASSWORD, TRUE );
						break;

					//added by tobets | 08-07-2012 | added pass2 to delete char
					default:
						strTemp = COuterInterface::GetInstance().MakeString ( ID2GAMEEXTEXT ("CHARACTERSTAGE_CAUTION_DELETE"), m_pDelCharInfo->m_szName );
						DoModalOuter ( strTemp.GetString(), MODAL_INPUT, EDITBOX, OUTER_MODAL_SECONDPASSWORD, TRUE );
						/*strTemp = COuterInterface::GetInstance().MakeString ( ID2GAMEEXTEXT ("CHARACTERSTAGE_CAUTION_DELETE_DAUM"), m_pDelCharInfo->m_szName );
						DoModalOuter ( strTemp.GetString(), MODAL_QUESTION, YESNO, OUTER_MODAL_SECONDPASSWORD );*/
						break;
					};
				}
				else
				{
					DoModalOuter ( ID2GAMEEXTEXT ("CHARACTERSTAGE_NOT_SELECTED"), MODAL_INFOMATION, OK );
				}
			}
		}
		break;
	case SELECT_PAGE_CHARACTER_POSITION0:
	case SELECT_PAGE_CHARACTER_POSITION1:
	case SELECT_PAGE_CHARACTER_POSITION2:
	case SELECT_PAGE_CHARACTER_POSITION3:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				int select = ControlID - SELECT_PAGE_CHARACTER_POSITION0;
				if ( select == m_nPosition ) return;				
				SELECT_CLASS_PROCESS( select );
			}
		}
		break;
	}
}
void CSelectCharacterPage::SELECT_CLASS_PROCESS( int nSelect )
{
	if ( m_nPosition > -1 )
	{
		m_pCharacterPosition[m_nPosition]->SetVisibleSingle(TRUE);
		m_pCharacterPositionSet[m_nPosition]->SetVisibleSingle(FALSE);

		if (m_nPosition == 0)
		{
			//pCharInfoA = charA;
			const CString strClassName1 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoA->m_emClass)].c_str();
			CString strName1;
			strName1.Format("%s",pCharInfoA->m_szName);
			m_pNameClassPos[0]->ClearText();
			m_pNameClassPos[0]->SetText( strClassName1, NS_UITEXTCOLOR::SILVER );
			m_pNameClass[0]->ClearText();
			m_pNameClass[0]->SetText( strName1, NS_UITEXTCOLOR::SILVER );

			strName1.Format("Lv.%d",pCharInfoA->m_wLevel);
			m_pLevelClass[0]->ClearText();
			m_pLevelClass[0]->SetText( strName1, NS_UITEXTCOLOR::SILVER );

			if( pCharInfoA->m_emClass == GLCC_FIGHTER_M )
			{
				m_pCharacterClassPos1[0]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[0]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_ARMS_M )
			{
				m_pCharacterClassPos1[1]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[1]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_ARCHER_W )
			{
				m_pCharacterClassPos1[2]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[2]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_SPIRIT_W )
			{
				m_pCharacterClassPos1[3]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[3]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_EXTREME_M )
			{
				m_pCharacterClassPos1[4]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[4]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_EXTREME_W )
			{
				m_pCharacterClassPos1[5]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[5]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_FIGHTER_W )
			{
				m_pCharacterClassPos1[6]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[6]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_ARMS_W )
			{
				m_pCharacterClassPos1[7]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[7]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_ARCHER_M )
			{
				m_pCharacterClassPos1[8]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[8]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_SPIRIT_M )
			{
				m_pCharacterClassPos1[9]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[9]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_SCIENCE_M )
			{
				m_pCharacterClassPos1[10]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[10]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_SCIENCE_W )
			{
				m_pCharacterClassPos1[11]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[11]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_M )
			{
				m_pCharacterClassPos1[12]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[12]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_W )
			{
				m_pCharacterClassPos1[13]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[13]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_TESTING_M )
			{
				m_pCharacterClassPos1[14]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[14]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoA->m_emClass == GLCC_TESTING_W )
			{
				m_pCharacterClassPos1[15]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos1[15]->SetVisibleSingle ( FALSE );
			}
		}
		else if (m_nPosition == 1)
		{
			//pCharInfoB = charB;
			const CString strClassName2 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoB->m_emClass)].c_str();
			CString strName2;
			strName2.Format("%s",pCharInfoB->m_szName);
			m_pNameClassPos[1]->ClearText();
			m_pNameClassPos[1]->SetText( strClassName2, NS_UITEXTCOLOR::SILVER );
			m_pNameClass[1]->ClearText();
			m_pNameClass[1]->SetText( strName2, NS_UITEXTCOLOR::SILVER );

			strName2.Format("Lv.%d",pCharInfoB->m_wLevel);
			m_pLevelClass[1]->ClearText();
			m_pLevelClass[1]->SetText( strName2, NS_UITEXTCOLOR::SILVER );

			if( pCharInfoB->m_emClass == GLCC_FIGHTER_M )
			{
				m_pCharacterClassPos2[0]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[0]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_ARMS_M )
			{
				m_pCharacterClassPos2[1]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[1]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_ARCHER_W )
			{
				m_pCharacterClassPos2[2]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[2]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_SPIRIT_W )
			{
				m_pCharacterClassPos2[3]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[3]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_EXTREME_M )
			{
				m_pCharacterClassPos2[4]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[4]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_EXTREME_W )
			{
				m_pCharacterClassPos2[5]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[5]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_FIGHTER_W )
			{
				m_pCharacterClassPos2[6]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[6]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_ARMS_W )
			{
				m_pCharacterClassPos2[7]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[7]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_ARCHER_M )
			{
				m_pCharacterClassPos2[8]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[8]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_SPIRIT_M )
			{
				m_pCharacterClassPos2[9]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[9]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_SCIENCE_M )
			{
				m_pCharacterClassPos2[10]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[10]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_SCIENCE_W )
			{
				m_pCharacterClassPos2[11]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[11]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_M )
			{
				m_pCharacterClassPos2[12]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[12]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_W )
			{
				m_pCharacterClassPos2[13]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[13]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_TESTING_M )
			{
				m_pCharacterClassPos2[14]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[14]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoB->m_emClass == GLCC_TESTING_W )
			{
				m_pCharacterClassPos2[15]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos2[15]->SetVisibleSingle ( FALSE );
			}
		}
		else if (m_nPosition == 2)
		{
			//pCharInfoC = charC;
			const CString strClassName3 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoC->m_emClass)].c_str();
			CString strName3;
			strName3.Format("%s",pCharInfoC->m_szName);
			m_pNameClassPos[2]->ClearText();
			m_pNameClassPos[2]->SetText( strClassName3, NS_UITEXTCOLOR::SILVER );
			m_pNameClass[2]->ClearText();
			m_pNameClass[2]->SetText( strName3, NS_UITEXTCOLOR::SILVER );

			strName3.Format("Lv.%d",pCharInfoC->m_wLevel);
			m_pLevelClass[2]->ClearText();
			m_pLevelClass[2]->SetText( strName3, NS_UITEXTCOLOR::SILVER );

			if( pCharInfoC->m_emClass == GLCC_FIGHTER_M )
			{
				m_pCharacterClassPos3[0]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[0]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_ARMS_M )
			{
				m_pCharacterClassPos3[1]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[1]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_ARCHER_W )
			{
				m_pCharacterClassPos3[2]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[2]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_SPIRIT_W )
			{
				m_pCharacterClassPos3[3]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[3]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_EXTREME_M )
			{
				m_pCharacterClassPos3[4]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[4]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_EXTREME_W )
			{
				m_pCharacterClassPos3[5]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[5]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_FIGHTER_W )
			{
				m_pCharacterClassPos3[6]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[6]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_ARMS_W )
			{
				m_pCharacterClassPos3[7]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[7]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_ARCHER_M )
			{
				m_pCharacterClassPos3[8]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[8]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_SPIRIT_M )
			{
				m_pCharacterClassPos3[9]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[9]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_SCIENCE_M )
			{
				m_pCharacterClassPos3[10]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[10]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_SCIENCE_W )
			{
				m_pCharacterClassPos3[11]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[11]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_M )
			{
				m_pCharacterClassPos3[12]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[12]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_W )
			{
				m_pCharacterClassPos3[13]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[13]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_TESTING_M )
			{
				m_pCharacterClassPos3[14]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[14]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoC->m_emClass == GLCC_TESTING_W )
			{
				m_pCharacterClassPos3[15]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos3[15]->SetVisibleSingle ( FALSE );
			}
		}
		else if (m_nPosition == 3)
		{
			//pCharInfoD = charD;
			const CString strClassName4 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoD->m_emClass)].c_str();
			CString strName4;
			strName4.Format("%s",pCharInfoD->m_szName);
			m_pNameClassPos[3]->ClearText();
			m_pNameClassPos[3]->SetText( strClassName4, NS_UITEXTCOLOR::SILVER );
			m_pNameClass[3]->ClearText();
			m_pNameClass[3]->SetText( strName4, NS_UITEXTCOLOR::SILVER );

			strName4.Format("Lv.%d",pCharInfoD->m_wLevel);
			m_pLevelClass[3]->ClearText();
			m_pLevelClass[3]->SetText( strName4, NS_UITEXTCOLOR::SILVER );

			if( pCharInfoD->m_emClass == GLCC_FIGHTER_M )
			{
				m_pCharacterClassPos4[0]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[0]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_ARMS_M )
			{
				m_pCharacterClassPos4[1]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[1]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_ARCHER_W )
			{
				m_pCharacterClassPos4[2]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[2]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_SPIRIT_W )
			{
				m_pCharacterClassPos4[3]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[3]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_EXTREME_M )
			{
				m_pCharacterClassPos4[4]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[4]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_EXTREME_W )
			{
				m_pCharacterClassPos4[5]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[5]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_FIGHTER_W )
			{
				m_pCharacterClassPos4[6]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[6]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_ARMS_W )
			{
				m_pCharacterClassPos4[7]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[7]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_ARCHER_M )
			{
				m_pCharacterClassPos4[8]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[8]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_SPIRIT_M )
			{
				m_pCharacterClassPos4[9]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[9]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_SCIENCE_M )
			{
				m_pCharacterClassPos4[10]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[10]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_SCIENCE_W )
			{
				m_pCharacterClassPos4[11]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[11]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_M )
			{
				m_pCharacterClassPos4[12]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[12]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_W )
			{
				m_pCharacterClassPos4[13]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[13]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_TESTING_M )
			{
				m_pCharacterClassPos4[14]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[14]->SetVisibleSingle ( FALSE );
			}
			else if( pCharInfoD->m_emClass == GLCC_TESTING_W )
			{
				m_pCharacterClassPos4[15]->SetVisibleSingle ( TRUE );
				m_pCharacterClassSetPos4[15]->SetVisibleSingle ( FALSE );
			}
		}

	}

	m_nPosition = nSelect;
	Select = nSelect;

	m_pCharacterPosition[m_nPosition]->SetVisibleSingle(FALSE);
	m_pCharacterPositionSet[m_nPosition]->SetVisibleSingle(TRUE);

	if (m_nPosition == 0)
	{
		//pCharInfoA = charA;
		const CString strClassName1 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoA->m_emClass)].c_str();
		CString strName1;
		strName1.Format("%s",pCharInfoA->m_szName);
		m_pNameClassPos[0]->ClearText();
		m_pNameClassPos[0]->SetText( strClassName1, NS_UITEXTCOLOR::WHITE );
		m_pNameClass[0]->ClearText();
		m_pNameClass[0]->SetText( strName1, NS_UITEXTCOLOR::WHITE );

		strName1.Format("Lv.%d",pCharInfoA->m_wLevel);
		m_pLevelClass[0]->ClearText();
		m_pLevelClass[0]->SetText( strName1, NS_UITEXTCOLOR::WHITE );

		if( pCharInfoA->m_emClass == GLCC_FIGHTER_M )
		{
			m_pCharacterClassPos1[0]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[0]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_ARMS_M )
		{
			m_pCharacterClassPos1[1]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[1]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_ARCHER_W )
		{
			m_pCharacterClassPos1[2]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[2]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_SPIRIT_W )
		{
			m_pCharacterClassPos1[3]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[3]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_EXTREME_M )
		{
			m_pCharacterClassPos1[4]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[4]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_EXTREME_W )
		{
			m_pCharacterClassPos1[5]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[5]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_FIGHTER_W )
		{
			m_pCharacterClassPos1[6]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[6]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_ARMS_W )
		{
			m_pCharacterClassPos1[7]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[7]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_ARCHER_M )
		{
			m_pCharacterClassPos1[8]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[8]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_SPIRIT_M )
		{
			m_pCharacterClassPos1[9]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[9]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_SCIENCE_M )
		{
			m_pCharacterClassPos1[10]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[10]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_SCIENCE_W )
		{
			m_pCharacterClassPos1[11]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[11]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_M )
		{
			m_pCharacterClassPos1[12]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[12]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_W )
		{
			m_pCharacterClassPos1[13]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[13]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_TESTING_M )
		{
			m_pCharacterClassPos1[14]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[14]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoA->m_emClass == GLCC_TESTING_W )
		{
			m_pCharacterClassPos1[15]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos1[15]->SetVisibleSingle ( TRUE );
		}
	}
	else if (m_nPosition == 1)
	{
		//pCharInfoB = charB;
		const CString strClassName2 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoB->m_emClass)].c_str();
		CString strName2;
		strName2.Format("%s",pCharInfoB->m_szName);
		m_pNameClassPos[1]->ClearText();
		m_pNameClassPos[1]->SetText( strClassName2, NS_UITEXTCOLOR::WHITE );
		m_pNameClass[1]->ClearText();
		m_pNameClass[1]->SetText( strName2, NS_UITEXTCOLOR::WHITE );

		strName2.Format("Lv.%d",pCharInfoB->m_wLevel);
		m_pLevelClass[1]->ClearText();
		m_pLevelClass[1]->SetText( strName2, NS_UITEXTCOLOR::WHITE );

		if( pCharInfoB->m_emClass == GLCC_FIGHTER_M )
		{
			m_pCharacterClassPos2[0]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[0]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_ARMS_M )
		{
			m_pCharacterClassPos2[1]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[1]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_ARCHER_W )
		{
			m_pCharacterClassPos2[2]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[2]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_SPIRIT_W )
		{
			m_pCharacterClassPos2[3]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[3]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_EXTREME_M )
		{
			m_pCharacterClassPos2[4]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[4]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_EXTREME_W )
		{
			m_pCharacterClassPos2[5]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[5]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_FIGHTER_W )
		{
			m_pCharacterClassPos2[6]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[6]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_ARMS_W )
		{
			m_pCharacterClassPos2[7]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[7]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_ARCHER_M )
		{
			m_pCharacterClassPos2[8]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[8]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_SPIRIT_M )
		{
			m_pCharacterClassPos2[9]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[9]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_SCIENCE_M )
		{
			m_pCharacterClassPos2[10]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[10]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_SCIENCE_W )
		{
			m_pCharacterClassPos2[11]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[11]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_M )
		{
			m_pCharacterClassPos2[12]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[12]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_W )
		{
			m_pCharacterClassPos2[13]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[13]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_TESTING_M )
		{
			m_pCharacterClassPos2[14]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[14]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoB->m_emClass == GLCC_TESTING_W )
		{
			m_pCharacterClassPos2[15]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos2[15]->SetVisibleSingle ( TRUE );
		}
	}
	else if (m_nPosition == 2)
	{
		//pCharInfoC = charC;
		const CString strClassName3 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoC->m_emClass)].c_str();
		CString strName3;
		strName3.Format("%s",pCharInfoC->m_szName);
		m_pNameClassPos[2]->ClearText();
		m_pNameClassPos[2]->SetText( strClassName3, NS_UITEXTCOLOR::WHITE );
		m_pNameClass[2]->ClearText();
		m_pNameClass[2]->SetText( strName3, NS_UITEXTCOLOR::WHITE );

		strName3.Format("Lv.%d",pCharInfoC->m_wLevel);
		m_pLevelClass[2]->ClearText();
		m_pLevelClass[2]->SetText( strName3, NS_UITEXTCOLOR::WHITE );

		if( pCharInfoC->m_emClass == GLCC_FIGHTER_M )
		{
			m_pCharacterClassPos3[0]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[0]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_ARMS_M )
		{
			m_pCharacterClassPos3[1]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[1]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_ARCHER_W )
		{
			m_pCharacterClassPos3[2]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[2]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_SPIRIT_W )
		{
			m_pCharacterClassPos3[3]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[3]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_EXTREME_M )
		{
			m_pCharacterClassPos3[4]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[4]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_EXTREME_W )
		{
			m_pCharacterClassPos3[5]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[5]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_FIGHTER_W )
		{
			m_pCharacterClassPos3[6]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[6]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_ARMS_W )
		{
			m_pCharacterClassPos3[7]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[7]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_ARCHER_M )
		{
			m_pCharacterClassPos3[8]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[8]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_SPIRIT_M )
		{
			m_pCharacterClassPos3[9]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[9]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_SCIENCE_M )
		{
			m_pCharacterClassPos3[10]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[10]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_SCIENCE_W )
		{
			m_pCharacterClassPos3[11]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[11]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_M )
		{
			m_pCharacterClassPos3[12]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[12]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_W )
		{
			m_pCharacterClassPos3[13]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[13]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_TESTING_M )
		{
			m_pCharacterClassPos3[14]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[14]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoC->m_emClass == GLCC_TESTING_W )
		{
			m_pCharacterClassPos3[15]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos3[15]->SetVisibleSingle ( TRUE );
		}
	}
	else if (m_nPosition == 3)
	{
		//pCharInfoD = charD;
		const CString strClassName4 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoD->m_emClass)].c_str();
		CString strName4;
		strName4.Format("%s",pCharInfoD->m_szName);
		m_pNameClassPos[3]->ClearText();
		m_pNameClassPos[3]->SetText( strClassName4, NS_UITEXTCOLOR::WHITE );
		m_pNameClass[3]->ClearText();
		m_pNameClass[3]->SetText( strName4, NS_UITEXTCOLOR::WHITE );

		strName4.Format("Lv.%d",pCharInfoD->m_wLevel);
		m_pLevelClass[3]->ClearText();
		m_pLevelClass[3]->SetText( strName4, NS_UITEXTCOLOR::WHITE );

		if( pCharInfoD->m_emClass == GLCC_FIGHTER_M )
		{
			m_pCharacterClassPos4[0]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[0]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_ARMS_M )
		{
			m_pCharacterClassPos4[1]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[1]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_ARCHER_W )
		{
			m_pCharacterClassPos4[2]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[2]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_SPIRIT_W )
		{
			m_pCharacterClassPos4[3]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[3]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_EXTREME_M )
		{
			m_pCharacterClassPos4[4]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[4]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_EXTREME_W )
		{
			m_pCharacterClassPos4[5]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[5]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_FIGHTER_W )
		{
			m_pCharacterClassPos4[6]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[6]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_ARMS_W )
		{
			m_pCharacterClassPos4[7]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[7]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_ARCHER_M )
		{
			m_pCharacterClassPos4[8]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[8]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_SPIRIT_M )
		{
			m_pCharacterClassPos4[9]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[9]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_SCIENCE_M )
		{
			m_pCharacterClassPos4[10]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[10]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_SCIENCE_W )
		{
			m_pCharacterClassPos4[11]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[11]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_M )
		{
			m_pCharacterClassPos4[12]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[12]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_W )
		{
			m_pCharacterClassPos4[13]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[13]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_TESTING_M )
		{
			m_pCharacterClassPos4[14]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[14]->SetVisibleSingle ( TRUE );
		}
		else if( pCharInfoD->m_emClass == GLCC_TESTING_W )
		{
			m_pCharacterClassPos4[15]->SetVisibleSingle ( FALSE );
			m_pCharacterClassSetPos4[15]->SetVisibleSingle ( TRUE );
		}
	}

}
void CSelectCharacterPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	const USHORT uCharRemain = COuterInterface::GetInstance().GetCharRemain ();

	if ( m_uCharRemain != uCharRemain )
	{
		CString strTemp;
		strTemp.Format ( "%s (%u)", (char*)ID2GAMEWORD ( "SELECT_CHARACTER_PAGE_BUTTON", 0 ), uCharRemain );
		m_pNewButton->SetOneLineText ( strTemp );

		m_uCharRemain = uCharRemain;
	}

	//m_pNameStatic->ClearText();
	//CString strTemp2;
	//strTemp2.Format ( "x:%1f y:%1f",MousePose.x,MousePose.y );
	//m_pNameStatic->SetText( strTemp2, NS_UITEXTCOLOR::WHITE );

	if ( HaveCharacter_A )
	{
		m_pCharacterPosition[0]->SetVisibleSingle ( TRUE );
		HaveCharacter_A = FALSE;
	}
	if ( HaveCharacter_B )
	{
		m_pCharacterPosition[1]->SetVisibleSingle ( TRUE );
		HaveCharacter_B = FALSE;
	}
	if ( HaveCharacter_C )
	{
		m_pCharacterPosition[2]->SetVisibleSingle ( TRUE );
		HaveCharacter_C = FALSE;
	}
	if ( HaveCharacter_D )
	{
		m_pCharacterPosition[3]->SetVisibleSingle ( TRUE );
		HaveCharacter_D = FALSE;
	}
}
void CSelectCharacterPage::SetDelCharacter()
{
	m_pCharacterPosition[0]->SetVisibleSingle ( FALSE );
	m_pCharacterPosition[1]->SetVisibleSingle ( FALSE );
	m_pCharacterPosition[2]->SetVisibleSingle ( FALSE );
	m_pCharacterPosition[3]->SetVisibleSingle ( FALSE );
	m_pCharacterPositionSet[0]->SetVisibleSingle ( FALSE );
	m_pCharacterPositionSet[1]->SetVisibleSingle ( FALSE );
	m_pCharacterPositionSet[2]->SetVisibleSingle ( FALSE );
	m_pCharacterPositionSet[3]->SetVisibleSingle ( FALSE );
	//m_pCharacterClass[0]->SetVisibleSingle( FALSE );
	//m_pCharacterClass[1]->SetVisibleSingle( FALSE );
	//m_pCharacterClass[2]->SetVisibleSingle( FALSE );
	//m_pCharacterClass[3]->SetVisibleSingle( FALSE );
	for ( int i = 0 ; i < GLCI_NUM_NEWEST; ++i ) 
	{
		m_pCharacterClassPos1[i]->SetVisibleSingle ( FALSE );
		m_pCharacterClassSetPos1[i]->SetVisibleSingle ( FALSE );
		m_pCharacterClassPos2[i]->SetVisibleSingle ( FALSE );
		m_pCharacterClassSetPos2[i]->SetVisibleSingle ( FALSE );
		m_pCharacterClassPos3[i]->SetVisibleSingle ( FALSE );
		m_pCharacterClassSetPos3[i]->SetVisibleSingle ( FALSE );
		m_pCharacterClassPos4[i]->SetVisibleSingle ( FALSE );
		m_pCharacterClassSetPos4[i]->SetVisibleSingle ( FALSE );
	}
	m_pNameClassPos[0]->ClearText();
	m_pNameClassPos[1]->ClearText();
	m_pNameClassPos[2]->ClearText();
	m_pNameClassPos[3]->ClearText();
	m_pLevelClass[0]->ClearText();
	m_pLevelClass[1]->ClearText();
	m_pLevelClass[2]->ClearText();
	m_pLevelClass[3]->ClearText();
	m_pNameClass[0]->ClearText();
	m_pNameClass[1]->ClearText();
	m_pNameClass[2]->ClearText();
	m_pNameClass[3]->ClearText();
	m_nPosition = -1;
}
void CSelectCharacterPage::ResetAll ()
{
	if ( m_pSelectCharacterPage ) 
	{
		m_pSelectCharacterPage->ResetAll ();
		if( DelChar )
		{
			SetDelCharacter();
			DelChar = FALSE;
		}
	}
}
void CSelectCharacterPage::SetCharInfoA( SCHARINFO_LOBBY* charA)
{
	pCharInfoA = charA;
	const CString strClassName1 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoA->m_emClass)].c_str();
	CString strName1;
	strName1.Format("%s",pCharInfoA->m_szName);
	m_pNameClassPos[0]->SetText( strClassName1, NS_UITEXTCOLOR::SILVER );
	m_pNameClass[0]->SetText( strName1, NS_UITEXTCOLOR::SILVER );
	strName1.Format("Lv.%d",pCharInfoA->m_wLevel);
	m_pLevelClass[0]->SetText( strName1, NS_UITEXTCOLOR::SILVER );
	ShowClassPos1();
}
void CSelectCharacterPage::SetCharInfoB( SCHARINFO_LOBBY* charB)
{
	pCharInfoB = charB;
	const CString strClassName2 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoB->m_emClass)].c_str();
	CString strName2;
	strName2.Format("%s",pCharInfoB->m_szName);
	m_pNameClassPos[1]->SetText( strClassName2, NS_UITEXTCOLOR::SILVER );
	m_pNameClass[1]->SetText( strName2, NS_UITEXTCOLOR::SILVER );
	strName2.Format("Lv.%d",pCharInfoB->m_wLevel);
	m_pLevelClass[1]->SetText( strName2, NS_UITEXTCOLOR::SILVER );
	ShowClassPos2();
}
void CSelectCharacterPage::SetCharInfoC( SCHARINFO_LOBBY* charC)
{
	pCharInfoC = charC;
	const CString strClassName3 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoC->m_emClass)].c_str();
	CString strName3;
	strName3.Format("%s",pCharInfoC->m_szName);
	m_pNameClassPos[2]->SetText( strClassName3, NS_UITEXTCOLOR::SILVER );
	m_pNameClass[2]->SetText( strName3, NS_UITEXTCOLOR::SILVER );
	strName3.Format("Lv.%d",pCharInfoC->m_wLevel);
	m_pLevelClass[2]->SetText( strName3, NS_UITEXTCOLOR::SILVER );
	ShowClassPos3();
}
void CSelectCharacterPage::SetCharInfoD( SCHARINFO_LOBBY* charD)
{
	pCharInfoD = charD;
	const CString strClassName4 = COMMENT::CHARCLASS[CharClassToIndex(pCharInfoD->m_emClass)].c_str();
	CString strName4;
	strName4.Format("%s",pCharInfoD->m_szName);
	m_pNameClassPos[3]->SetText( strClassName4, NS_UITEXTCOLOR::SILVER );
	m_pNameClass[3]->SetText( strName4, NS_UITEXTCOLOR::SILVER );
	strName4.Format("Lv.%d",pCharInfoD->m_wLevel);
	m_pLevelClass[3]->SetText( strName4, NS_UITEXTCOLOR::SILVER );
	ShowClassPos4();
}
void CSelectCharacterPage::ShowClassPos1()
{
	if( pCharInfoA->m_emClass == GLCC_FIGHTER_M )
	{
		m_pCharacterClassPos1[0]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_ARMS_M )
	{
		m_pCharacterClassPos1[1]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_ARCHER_W )
	{
		m_pCharacterClassPos1[2]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_SPIRIT_W )
	{
		m_pCharacterClassPos1[3]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_EXTREME_M )
	{
		m_pCharacterClassPos1[4]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_EXTREME_W )
	{
		m_pCharacterClassPos1[5]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_FIGHTER_W )
	{
		m_pCharacterClassPos1[6]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_ARMS_W )
	{
		m_pCharacterClassPos1[7]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_ARCHER_M )
	{
		m_pCharacterClassPos1[8]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_SPIRIT_M )
	{
		m_pCharacterClassPos1[9]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_SCIENCE_M )
	{
		m_pCharacterClassPos1[10]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_SCIENCE_W )
	{
		m_pCharacterClassPos1[11]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_M )
	{
		m_pCharacterClassPos1[12]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_ASSASSIN_W )
	{
		m_pCharacterClassPos1[13]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_TESTING_M )
	{
		m_pCharacterClassPos1[14]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoA->m_emClass == GLCC_TESTING_W )
	{
		m_pCharacterClassPos1[15]->SetVisibleSingle ( TRUE );
	}
}
void CSelectCharacterPage::ShowClassPos2()
{
	if( pCharInfoB->m_emClass == GLCC_FIGHTER_M )
	{
		m_pCharacterClassPos2[0]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_ARMS_M )
	{
		m_pCharacterClassPos2[1]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_ARCHER_W )
	{
		m_pCharacterClassPos2[2]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_SPIRIT_W )
	{
		m_pCharacterClassPos2[3]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_EXTREME_M )
	{
		m_pCharacterClassPos2[4]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_EXTREME_W )
	{
		m_pCharacterClassPos2[5]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_FIGHTER_W )
	{
		m_pCharacterClassPos2[6]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_ARMS_W )
	{
		m_pCharacterClassPos2[7]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_ARCHER_M )
	{
		m_pCharacterClassPos2[8]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_SPIRIT_M )
	{
		m_pCharacterClassPos2[9]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_SCIENCE_M )
	{
		m_pCharacterClassPos2[10]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_SCIENCE_W )
	{
		m_pCharacterClassPos2[11]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_M )
	{
		m_pCharacterClassPos2[12]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_ASSASSIN_W )
	{
		m_pCharacterClassPos2[13]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_TESTING_M )
	{
		m_pCharacterClassPos2[14]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoB->m_emClass == GLCC_TESTING_W )
	{
		m_pCharacterClassPos2[15]->SetVisibleSingle ( TRUE );
	}
}
void CSelectCharacterPage::ShowClassPos3()
{
	if( pCharInfoC->m_emClass == GLCC_FIGHTER_M )
	{
		m_pCharacterClassPos3[0]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_ARMS_M )
	{
		m_pCharacterClassPos3[1]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_ARCHER_W )
	{
		m_pCharacterClassPos3[2]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_SPIRIT_W )
	{
		m_pCharacterClassPos3[3]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_EXTREME_M )
	{
		m_pCharacterClassPos3[4]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_EXTREME_W )
	{
		m_pCharacterClassPos3[5]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_FIGHTER_W )
	{
		m_pCharacterClassPos3[6]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_ARMS_W )
	{
		m_pCharacterClassPos3[7]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_ARCHER_M )
	{
		m_pCharacterClassPos3[8]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_SPIRIT_M )
	{
		m_pCharacterClassPos3[9]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_SCIENCE_M )
	{
		m_pCharacterClassPos3[10]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_SCIENCE_W )
	{
		m_pCharacterClassPos3[11]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_M )
	{
		m_pCharacterClassPos3[12]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_ASSASSIN_W )
	{
		m_pCharacterClassPos3[13]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_TESTING_M )
	{
		m_pCharacterClassPos3[14]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoC->m_emClass == GLCC_TESTING_W )
	{
		m_pCharacterClassPos3[15]->SetVisibleSingle ( TRUE );
	}
}
void CSelectCharacterPage::ShowClassPos4()
{
	if( pCharInfoD->m_emClass == GLCC_FIGHTER_M )
	{
		m_pCharacterClassPos4[0]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_ARMS_M )
	{
		m_pCharacterClassPos4[1]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_ARCHER_W )
	{
		m_pCharacterClassPos4[2]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_SPIRIT_W )
	{
		m_pCharacterClassPos4[3]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_EXTREME_M )
	{
		m_pCharacterClassPos4[4]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_EXTREME_W )
	{
		m_pCharacterClassPos4[5]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_FIGHTER_W )
	{
		m_pCharacterClassPos4[6]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_ARMS_W )
	{
		m_pCharacterClassPos4[7]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_ARCHER_M )
	{
		m_pCharacterClassPos4[8]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_SPIRIT_M )
	{
		m_pCharacterClassPos4[9]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_SCIENCE_M )
	{
		m_pCharacterClassPos4[10]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_SCIENCE_W )
	{
		m_pCharacterClassPos4[11]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_M )
	{
		m_pCharacterClassPos4[12]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_ASSASSIN_W )
	{
		m_pCharacterClassPos4[13]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_TESTING_M )
	{
		m_pCharacterClassPos4[14]->SetVisibleSingle ( TRUE );
	}
	else if( pCharInfoD->m_emClass == GLCC_TESTING_W )
	{
		m_pCharacterClassPos4[15]->SetVisibleSingle ( TRUE );
	}
}
void CSelectCharacterPage::SetLeftButtonState(BOOL bState)
{
}

void CSelectCharacterPage::SetRightButtonState(BOOL bState)
{
	
}
// ฦไภฬม๖ ผýภฺธฆ ผณมควัดู.
void CSelectCharacterPage::SetPageNum(int nPageNum)
{

}

// ผณมคตศ ลุฝบฦฎ นฺฝบภว ฐชภป ฐกมฎฟยดู.
int CSelectCharacterPage::GetPageNum()
{
	return 0;
}