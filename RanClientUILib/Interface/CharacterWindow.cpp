#include "StdAfx.h"
#include "./CharacterWindow.h"

#include "./GLCharClient.h"
#include "./GLFactEffect.h"
#include "./GLGaeaClient.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineLib/DxCommon/d3dfont.h"
#include "InventoryPageWearEx.h"
#include "DxGlobalStage.h"
#include "GLCharacter.h"
#include "DxGameStage.h"
#include "../RanClientUILib/Interface/InnerInterface.h"

#include "../Interface/BasicTextButton.h"
#include "../Interface/UITextControl.h"
#include "../Interface/GameTextControl.h"
#include "../RanClientLib/G-Logic/GLGaeaClient.h"
#include "BasicComboBox.h"
#include "BasicComboBoxRollOver.h"

#include "DxEffectMan.h"
#include "DxEnvironment.h"
#include "DxSurfaceTex.h"
#include "DxGlowMan.h"
#include "DxPostProcess.h"
#include "DxCubeMap.h"
#include "DxSkyMan.h"
#include "DxEffGroupPlayer.h"
#include "../EngineLib/DxCommon/DxViewPort.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineLib/DxCommon/DxInputDevice.h"
#include "../EngineLib/DxCommon/DxLightMan.h"
#include "DxSkinChar.h"
#include "d3dfont.h"
#include "CharacterWindowCharRender.h"
#include "DxGlobalStage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//Vertex buffers are a method of storing vertices to be rendered in an optimized manner.

CCharacterWindow::CCharacterWindow () :
	m_pNameText ( NULL ),
	
	m_pButtonOk ( NULL ),
	m_pButtonCancel ( NULL ),
	//m_pButtonOk_F ( NULL ),
	//m_pButtonCancel_F ( NULL ),

	//Added by NjD
	//m_pButtonOk_F ( NULL ),
	//m_pButtonCancel_F ( NULL ),

	m_pEXP ( NULL ),
	m_pEXPText ( NULL ),

	m_pPageWear( NULL ),
	m_pPageWearEx( NULL ),

	//m_pStaDiaableButton ( NULL ),

	m_pPowText ( NULL ),
	m_pDexText ( NULL ),
	m_pSpiText ( NULL ),
	//m_pIntText ( NULL ),
	m_pStrText ( NULL ),
	m_pStaText ( NULL ),

	m_pPowText2 ( NULL ),
	m_pDexText2 ( NULL ),
	m_pSpiText2 ( NULL ),
	m_pStrText2 ( NULL ),
	m_pStaText2 ( NULL ),

	m_pNewPow ( 0 ),
	m_pNewDex ( 0 ),
	m_pNewSpi ( 0 ),
	m_pNewStr ( 0 ),
	m_pNewSta ( 0 ),
	m_pNewPoint ( 0 ),
	nIndex ( 0 ),

	m_pPointDisable ( NULL ),
	m_pPointEnable ( NULL ),
	m_pPointText ( NULL ),
	m_pPointText2 ( NULL ),

	m_pLevelText ( NULL ),
	m_pClubText ( NULL ),
	m_pDamageMinText ( NULL ),
	m_pDamageMaxText ( NULL ),
	m_pDefenseText ( NULL ),
	m_pReqPaText ( NULL ),
	m_pReqSaText ( NULL ),	
	m_pHPText ( NULL ),
	m_pMPText ( NULL ),
	m_pSPText ( NULL ),
	m_pCPText ( NULL ),
	m_pRBText ( NULL ),
	m_pHitRateText ( NULL ),
	m_pAvoidRateText ( NULL ),

	m_pDamageMinText2 ( NULL ),
	m_pDamageMaxText2 ( NULL ),
	m_pDefenseText2 ( NULL ),
	m_pReqPaText2 ( NULL ),
	m_pReqSaText2 ( NULL ),	
	m_pHPText2 ( NULL ),
	m_pMPText2 ( NULL ),
	m_pSPText2 ( NULL ),
	m_pCPText2 ( NULL ),
	m_pHitRateText2 ( NULL ),
	m_pAvoidRateText2 ( NULL ),

	m_pDamageMinText3 ( NULL ),
	m_pDamageMaxText3 ( NULL ),
	m_pDefenseText3 ( NULL ),
	m_pReqPaText3 ( NULL ),
	m_pReqSaText3 ( NULL ),	
	m_pHPText3 ( NULL ),
	m_pMPText3 ( NULL ),
	m_pSPText3 ( NULL ),
	m_pCPText3 ( NULL ),
	m_pHitRateText3 ( NULL ),
	m_pAvoidRateText3 ( NULL ),

	m_pFireText ( NULL ),
	m_pColdText ( NULL ),
	m_pElectricText ( NULL ),
	m_pPoisonText ( NULL ),
	m_pSpiritText ( NULL ),


	m_pPKStateText ( NULL ),
	m_pGradeText ( NULL ),		//ª×èÍàÊÕÂ§
	m_pGradeValue ( NULL ),		//ª×èÍàÊÕÂ§
	m_pBrightSlider ( NULL ),	//¤ÇÒÁ´Õ
	m_pActivityPointText ( NULL ),	//¼Å§Ò¹
	m_pActivityPointValue ( NULL ),	//¼Å§Ò¹
	m_pAcademy_Department ( NULL ),	//Ê¶ÒºÑ¹	//ÊÒÂÍÒªªÕ¾
	m_pd3dDevice ( NULL ),
	m_pMobileText( NULL ),
	m_pSkinChar(NULL),
    m_pRender( NULL )
{
	memset ( m_pButtonPlus, 0, sizeof ( m_pButtonPlus ) );
	memset ( m_pButtonMinus, 0, sizeof ( m_pButtonMinus ) );
	
	D3DXMatrixIdentity( &m_matTrans );
}

CCharacterWindow::~CCharacterWindow ()
{
}
CBasicTextBox* CCharacterWindow::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}

CBasicTextButton*  CCharacterWindow::CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE19;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON19", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;
}
CBasicTextButton*  CCharacterWindow::CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText ,_DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicTextButton*  CCharacterWindow::CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE24;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText , _DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicTextButton*  CCharacterWindow::CreateTextButton25 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE25;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON25", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText , _DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}


void CCharacterWindow::CreateSubControl ()
{
	CD3DFontPar* pFont8Shadow = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFontName = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );

	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );


	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, CHARWINDOW_INFO_BUTTON );
	pTextButton->CreateBaseButton ( "CHARACTER_PAGE_BUTTON", nBUTTONSIZE, CBasicButton::RADIO_FLIP, "Character", D3DFONT_SHADOW );
	RegisterControl ( pTextButton );


		CUIControl*	m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "CHARACTERWINDOW_BG_WHITE", UI_FLAG_DEFAULT);	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	

	const int nAlignLeft = TEXT_ALIGN_LEFT;
	const int nAlignCenter = TEXT_ALIGN_CENTER_X;		
	const DWORD& dwSilver = NS_UITEXTCOLOR::SILVER;
	const DWORD& dwSubTitle = NS_UITEXTCOLOR::PALEGOLDENROD;

	CUIControl* pControl = CreateControl ( "CHARACTER_BACK1" );
	pControl->SetAlignFlag ( UI_FLAG_DEFAULT );

	CUIControl* pControl2 = CreateControl ( "CHARACTER_BACK2" );
	pControl2->SetAlignFlag ( UI_FLAG_DEFAULT );

	CUIControl* pControl3 = CreateControl ( "CHARACTER_BACK3" );
	pControl3->SetAlignFlag ( UI_FLAG_DEFAULT );

	CUIControl* pControl4 = CreateControl ( "CHARACTER_BACK4" );
	pControl4->SetAlignFlag ( UI_FLAG_DEFAULT );

	CUIControl* pControl5 = CreateControl ( "CHARACTER_BACK5" );
	pControl5->SetAlignFlag ( UI_FLAG_DEFAULT );

	for (int i = 1; i <= 24 ; i++)
	{
		CString strCombine;
		strCombine.Format ( "CHARACTER_LINE%d", i );
		CUIControl* pControl6 = CreateControl ( strCombine );
		pControl6->SetAlignFlag ( UI_FLAG_DEFAULT );
	}

	if( nClassType == GLCI_EXTREME_W || nClassType == GLCI_EXTREME_M || nClassType == GLCI_ARMS_W || nClassType == GLCI_ARMS_M || nClassType == GLCI_FIGHTER_W || nClassType == GLCI_FIGHTER_M || nClassType == GLCI_ARCHER_W || nClassType == GLCI_ARCHER_M || nClassType == GLCI_SPIRIT_W || nClassType == GLCI_SPIRIT_M || nClassType == GLCI_SCIENCE_W || nClassType == GLCI_SCIENCE_M || nClassType == GLCI_ASSASSIN_W || nClassType == GLCI_ASSASSIN_M ) 
	{
		m_pPageWearEx = new CInventoryPageWearEx;
		m_pPageWearEx->CreateSub ( this, "INVENTORY_PAGE_WEAR", UI_FLAG_DEFAULT, INVENTORY_PAGEWEAR_EX );
		m_pPageWearEx->CreateSubControl ( nClassType );
		RegisterControl ( m_pPageWearEx );
	}

	/*else
	{
		m_pPageWear = new CInventoryPageWear;
		m_pPageWear->CreateSub ( this, "INVENTORY_PAGE_WEAR", UI_FLAG_DEFAULT, INVENTORY_PAGEWEAR );
		m_pPageWear->CreateSubControl ( nClassType );
		RegisterControl ( m_pPageWear );
	}*/

	{
		CBasicComboBox* pComboBox = NULL;
		CBasicComboBoxRollOver*	pComboBoxRollOver = NULL;

		pComboBox = new CBasicComboBox;
		pComboBox->CreateSub ( this, "BASIC_COMBOBOX", UI_FLAG_XSIZE, NICKNAME_COMBO_OPEN );
		pComboBox->CreateBaseComboBox ( "NICKNAME_COMBO_OPEN" );
		pComboBox->SetVisibleSingle(FALSE);
		RegisterControl ( pComboBox );
		m_pComboBoxNickNameOpen = pComboBox;

		pComboBoxRollOver = new CBasicComboBoxRollOver;
		pComboBoxRollOver->CreateSub ( this, "BASIC_COMBOBOX_ROLLOVER", UI_FLAG_XSIZE | UI_FLAG_YSIZE, NICKNAME_COMBO_ROLLOVER );
		pComboBoxRollOver->CreateBaseComboBoxRollOver ( "NICKNAME_COMBO_ROLLOVER" );
		pComboBoxRollOver->SetVisibleSingle ( FALSE );
		RegisterControl ( pComboBoxRollOver );
		m_pComboBoxNickNameRollOver = pComboBoxRollOver;
	}

    CBasicTextBox* pTextBox = NULL;

	{	//	ÀÌ¸§        
		//CreateControl ( "CHARACTER_NAMEBACK_L" );
		//CreateControl ( "CHARACTER_NAMEBACK_R" );
		//m_pNameText = CreateStaticControl ( "CHARACTER_NAMEBOX", pFont, nAlignCenter );
	}

	{	//	°æÇèÄ¡
		//m_pEXP = new CBasicProgressBar;
		//m_pEXP->CreateSub ( this, "CHARACTER_EXP" );
		//m_pEXP->CreateOverImage ( "CHARACTER_EXP_OVERIMAGE" );
		//m_pEXP->SetControlNameEx ( "EXP ÇÁ·Î±×·¡½º¹Ù" );
		//RegisterControl ( m_pEXP );

		//CreateControl ( "CHARACTER_EXPBACK" );

		//m_pEXPText = CreateStaticControl ( "CHARACTER_EXPNUMBER_TEXTBOX", pFont8Shadow, nAlignCenter );
	}
	
	{	//	Stats
		//pTextBox = CreateStaticControl ( "CHARACTER_EXP_STATIC", pFont, nAlignCenter );
		//pTextBox->AddText ( ID2GAMEWORD("CHARACTER_EXP_STATIC"), dwSilver );		

		m_pPowTextStatic = CreateStaticControl ( "CHARACTER_POW_STATIC", pFont, nAlignLeft );
		m_pPowTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC_NEW", 1), dwSilver );

		m_pDexTextStatic = CreateStaticControl ( "CHARACTER_DEX_STATIC", pFont, nAlignLeft );
		m_pDexTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC_NEW", 2), dwSilver );

		m_pSpiTextStatic = CreateStaticControl ( "CHARACTER_SPI_STATIC", pFont, nAlignLeft );
		m_pSpiTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC_NEW", 3), dwSilver );

		//m_pIntTextStatic = CreateStaticControl ( "CHARACTER_INT_STATIC", pFont, nAlignLeft );
		//m_pIntTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC", 3), dwSilver );
		//m_pIntTextStatic->SetVisibleSingle ( FALSE );

		m_pStrTextStatic = CreateStaticControl ( "CHARACTER_STR_STATIC", pFont, nAlignLeft );
		m_pStrTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC_NEW", 4), dwSilver );

		m_pStaTextStatic = CreateStaticControl ( "CHARACTER_STA_STATIC", pFont, nAlignLeft );
		m_pStaTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC_NEW", 5), dwSilver );
	
	CString	strButtonPlus[5] = 
	{
		"RNCHARACTER_WINDOW_STAT_POW_PLUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_DEX_PLUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_SPI_PLUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_STR_PLUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_STA_PLUS_BUTTON"
	};

	CString	strButtonMinus[5] = 
	{
		"RNCHARACTER_WINDOW_STAT_POW_MINUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_DEX_MINUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_SPI_MINUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_STR_MINUS_BUTTON",
		"RNCHARACTER_WINDOW_STAT_STA_MINUS_BUTTON"
	};

	for ( int i = 0; i < 5; i++ )
	{	
		m_pButtonPlus[i] = CreateTextButton24 ( strButtonPlus[i].GetString (), CHARACTER_WINDOW_STAT_POW_PLUS_BUTTON + i, "+" );
		m_pButtonMinus[i] = CreateTextButton24 ( strButtonMinus[i].GetString (), CHARACTER_WINDOW_STAT_POW_MINUS_BUTTON + i, "-" );
		m_pButtonPlus[i]->SetVisibleSingle ( FALSE );
		m_pButtonMinus[i]->SetVisibleSingle ( FALSE );
	} 

	m_pButtonOk = CreateTextButton25 ( "RNCHARACTER_WINDOW_STAT_APPLY_BUTTON", CHARACTER_WINDOW_STAT_OK , ID2GAMEWORD("CHARACTER_STAT_APPLY") );
	m_pButtonCancel = CreateTextButton25 ( "RNCHARACTER_WINDOW_STAT_INIT_BUTTON", CHARACTER_WINDOW_STAT_CANCEL , ID2GAMEWORD("CHARACTER_STAT_INIT") );
	//m_pButtonOk_F = CreateTextButtonBlackButton ( "RNCHARACTER_WINDOW_STAT_APPLY_BUTTON", CHARACTER_WINDOW_STAT_OK_F , ID2GAMEWORD("CHARACTER_STAT_APPLY") );
	//m_pButtonCancel_F = CreateTextButtonBlackButton ( "RNCHARACTER_WINDOW_STAT_INIT_BUTTON", CHARACTER_WINDOW_STAT_CANCEL_F , ID2GAMEWORD("CHARACTER_STAT_INIT") );
	

	m_pButtonOk->SetVisibleSingle ( FALSE );
	m_pButtonCancel->SetVisibleSingle ( FALSE );

		m_pPowText = CreateStaticControl ( "CHARACTER_POW_TEXT", pFont8Shadow, nAlignLeft );
		m_pDexText = CreateStaticControl ( "CHARACTER_DEX_TEXT", pFont8Shadow, nAlignLeft );
		m_pSpiText = CreateStaticControl ( "CHARACTER_SPI_TEXT", pFont8Shadow, nAlignLeft );
		//m_pIntText = CreateStaticControl ( "CHARACTER_INT_TEXT", pFont8Shadow, nAlignLeft );
		//m_pIntText->SetVisibleSingle ( FALSE );
		m_pStrText = CreateStaticControl ( "CHARACTER_STR_TEXT", pFont8Shadow, nAlignLeft );
		m_pStaText = CreateStaticControl ( "CHARACTER_STA_TEXT", pFont8Shadow, nAlignLeft );

		m_pPowText2 = CreateStaticControl ( "CHARACTER_POW_TEXT2", pFont8Shadow, nAlignLeft );
		m_pDexText2 = CreateStaticControl ( "CHARACTER_DEX_TEXT2", pFont8Shadow, nAlignLeft );
		m_pSpiText2 = CreateStaticControl ( "CHARACTER_SPI_TEXT2", pFont8Shadow, nAlignLeft );
		m_pStrText2 = CreateStaticControl ( "CHARACTER_STR_TEXT2", pFont8Shadow, nAlignLeft );
		m_pStaText2 = CreateStaticControl ( "CHARACTER_STA_TEXT2", pFont8Shadow, nAlignLeft );
	}

	{	//	°¡¿ëÆ÷ÀÎÆ®

		//m_pPointDisable = CreateControl ( "CHARACTER_POINT_DISABLE" );
		//m_pPointEnable = CreateControl ( "CHARACTER_POINT_ENABLE" );

		//CreateControl ( "CHARACTER_POINT_BACK" );
	
		m_pPointText = CreateStaticControl ( "CHARACTER_POINT_TEXT", pFont8Shadow, nAlignCenter );

		m_pPointText2 = CreateStaticControl ( "CHARACTER_POINT_TEXT2", pFont, nAlignCenter );
		m_pPointText2->SetOneLineText( ID2GAMEWORD("CHARACTER_STAT_STATIC_NEW", 6), NS_UITEXTCOLOR::WHITE );

	}

	{	//	Status
       // CreateControl ( "CHARACTER_STATUS_BACK_L" );
		//CreateControl ( "CHARACTER_STATUS_BACK_R" );
		//pTextBox = CreateStaticControl ( "CHARACTER_STATUS_STATIC_TITLE", pFont, nAlignCenter );
		//pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 0), dwSubTitle );

		//pTextBox = CreateStaticControl ( "CHARACTER_LEVEL_STATIC", pFont, nAlignLeft );
		//pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 1), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_DAMAGE_MIN_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 2), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_DAMAGE_MAX_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 3), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_DEFENSE_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 4), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_REQPA_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 5), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_REQSA_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 6), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_REQMA_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 12), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_HP_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 7), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_MP_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 8), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_SP_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 9), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_CP_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 14), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_REBORN_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 15), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_HITRATE_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 10), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_AVOIDRATE_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 11), dwSilver );

		m_pPremiumTextStatic = CreateStaticControl ( "CHARACTER_PREMIUM_STATIC", pFont, nAlignLeft );
		m_pPremiumTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 13), dwSilver );

		m_pLevelText = CreateStaticControl ( "CHARACTER_LEVEL_AND_NAME_TEXT", pFontName, TEXT_ALIGN_CENTER_X );
		m_pClubText = CreateStaticControl ( "CHARACTER_CLUB_TEXT", pFontName, TEXT_ALIGN_CENTER_X );
		m_pDamageMinText = CreateStaticControl ( "CHARACTER_DAMAGE_MIN_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pDamageMaxText = CreateStaticControl ( "CHARACTER_DAMAGE_MAX_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pDefenseText = CreateStaticControl ( "CHARACTER_DEFENSE_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pReqPaText = CreateStaticControl ( "CHARACTER_REQPA_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pReqSaText = CreateStaticControl ( "CHARACTER_REQSA_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pReqMaText = CreateStaticControl ( "CHARACTER_REQMA_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		
		m_pHPText = CreateStaticControl ( "CHARACTER_HP_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pMPText = CreateStaticControl ( "CHARACTER_MP_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pSPText = CreateStaticControl ( "CHARACTER_SP_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pCPText = CreateStaticControl ( "CHARACTER_CP_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pHitRateText = CreateStaticControl ( "CHARACTER_HITRATE_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pAvoidRateText = CreateStaticControl ( "CHARACTER_AVOIDRATE_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
		m_pPremiumText = CreateStaticControl ( "CHARACTER_PREMIUM_TEXT", pFont8Shadow, nAlignLeft, CHARACTER_PREMIUM_TEXT );
		m_pRBText = CreateStaticControl ( "CHARACTER_REBORN_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );

		m_pDamageMinText2 = CreateStaticControl ( "CHARACTER_DAMAGE_MIN_TEXT2", pFont8Shadow, nAlignLeft );
		m_pDamageMaxText2 = CreateStaticControl ( "CHARACTER_DAMAGE_MAX_TEXT2", pFont8Shadow, nAlignLeft );
		m_pDefenseText2 = CreateStaticControl ( "CHARACTER_DEFENSE_TEXT2", pFont8Shadow, nAlignLeft );
		m_pReqPaText2 = CreateStaticControl ( "CHARACTER_REQPA_TEXT2", pFont8Shadow, nAlignLeft );
		m_pReqSaText2 = CreateStaticControl ( "CHARACTER_REQSA_TEXT2", pFont8Shadow, nAlignLeft );
		m_pReqMaText2 = CreateStaticControl ( "CHARACTER_REQMA_TEXT2", pFont8Shadow, nAlignLeft );
		m_pHPText2 = CreateStaticControl ( "CHARACTER_HP_TEXT2", pFont8Shadow, nAlignLeft );
		m_pMPText2 = CreateStaticControl ( "CHARACTER_MP_TEXT2", pFont8Shadow, nAlignLeft );
		m_pSPText2 = CreateStaticControl ( "CHARACTER_SP_TEXT2", pFont8Shadow, nAlignLeft );
		m_pCPText2 = CreateStaticControl ( "CHARACTER_CP_TEXT2", pFont8Shadow, nAlignLeft );
		m_pHitRateText2 = CreateStaticControl ( "CHARACTER_HITRATE_TEXT2", pFont8Shadow, nAlignLeft );
		m_pAvoidRateText2 = CreateStaticControl ( "CHARACTER_AVOIDRATE_TEXT2", pFont8Shadow, nAlignLeft );

		m_pDamageMinText3 = CreateStaticControl ( "CHARACTER_DAMAGE_MIN_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pDamageMaxText3 = CreateStaticControl ( "CHARACTER_DAMAGE_MAX_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pDefenseText3 = CreateStaticControl ( "CHARACTER_DEFENSE_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pReqPaText3 = CreateStaticControl ( "CHARACTER_REQPA_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pReqSaText3 = CreateStaticControl ( "CHARACTER_REQSA_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pReqMaText3 = CreateStaticControl ( "CHARACTER_REQMA_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pHPText3 = CreateStaticControl ( "CHARACTER_HP_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pMPText3 = CreateStaticControl ( "CHARACTER_MP_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pSPText3 = CreateStaticControl ( "CHARACTER_SP_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pCPText3 = CreateStaticControl ( "CHARACTER_CP_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pHitRateText3 = CreateStaticControl ( "CHARACTER_HITRATE_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
		m_pAvoidRateText3 = CreateStaticControl ( "CHARACTER_AVOIDRATE_TEXT3", pFont8Shadow, TEXT_ALIGN_CENTER_X );
	}

	{	//	ÀúÇ×·Â
       // CreateControl ( "CHARACTER_RESI_BACK_L" );
		//CreateControl ( "CHARACTER_RESI_BACK_R" );
		//pTextBox = CreateStaticControl ( "CHARACTER_RESI_STATIC_TITLE", pFont, nAlignCenter );
		//pTextBox->AddText ( ID2GAMEWORD("CHARACTER_RESI_STATIC", 0), dwSubTitle );

		pTextBox = CreateStaticControl ( "CHARACTER_FIRE_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_RESI_STATIC", 1), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_COLD_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_RESI_STATIC", 2), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_ELECTRIC_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_RESI_STATIC", 3), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_POISON_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_RESI_STATIC", 4), dwSilver );

		pTextBox = CreateStaticControl ( "CHARACTER_SPIRIT_STATIC", pFont, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_RESI_STATIC", 5), dwSilver );

		m_pFireText = CreateStaticControl ( "CHARACTER_FIRE_TEXT", pFont8Shadow, nAlignLeft );
		m_pColdText = CreateStaticControl ( "CHARACTER_COLD_TEXT", pFont8Shadow, nAlignLeft );
		m_pElectricText = CreateStaticControl ( "CHARACTER_ELECTRIC_TEXT", pFont8Shadow, nAlignLeft );
		m_pPoisonText = CreateStaticControl ( "CHARACTER_POISON_TEXT", pFont8Shadow, nAlignLeft );
		m_pSpiritText = CreateStaticControl ( "CHARACTER_SPIRIT_TEXT", pFont8Shadow, nAlignLeft );
	}

	{	//	»çÈ¸¼ºÇâ
       // CreateControl ( "CHARACTER_SOCIAL_BACK_L" );
		//CreateControl ( "CHARACTER_SOCIAL_BACK_R" );
		//pTextBox = CreateStaticControl ( "CHARACTER_SOCIAL_STATIC_TITLE", pFont, nAlignCenter );
		//pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 0), dwSubTitle );

		pTextBox = CreateStaticControl ( "RNCHARACTER_WINDOW_PKSTATE_TEXT", pFont8Shadow, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 3), dwSilver );

		m_pPKStateText = CreateStaticControl ( "RNCHARACTER_WINDOW_PKSTATE_VALUE", pFont8Shadow, nAlignLeft );

		m_pAcademy_Department = CreateStaticControl ( "RNCHARACTER_WINDOW_ACADEMY_DEPARTMENT_TEXT", pFont, nAlignLeft );
	
		CBasicTextBox* pTextBox = CreateStaticControl ( "RNCHARACTER_WINDOW_BRIGHT_TEXT", pFont8Shadow, nAlignLeft );
		pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 5), dwSilver );

		m_pGradeText = CreateStaticControl ( "RNCHARACTER_WINDOW_CONTRIBUTION_POINT_TEXT", pFont8Shadow, nAlignLeft );
		m_pGradeValue = CreateStaticControl ( "RNCHARACTER_WINDOW_CONTRIBUTION_POINT_VALUE", pFont8Shadow, nAlignLeft );
	
		m_pActivityPointText = CreateStaticControl ( "RNCHARACTER_WINDOW_ACTIVITY_POINT_TEXT", pFont8Shadow, nAlignLeft );
		m_pActivityPointValue = CreateStaticControl ( "RNCHARACTER_WINDOW_ACTIVITY_POINT_VALUE", pFont8Shadow, nAlignLeft );
	
		m_pBrightFrame = CreateControl ( "RNCHARACTER_WINDOW_BRIGHTBAR",CHARACTER_BIRGHTER );		
		m_pBrightSlider = CreateControl ( "RNCHARACTER_WINDOW_BRIGHTBAR_THUMB" );

		CreateControl ( "CHARACTER_BRIGHTBAR_DUMMY", CHARACTER_BIRGHTER );

		{ // Render Caller Gui || X,Y Control

   	    m_pRender = new CCharacterWindowCharRender;
	    m_pRender->CreateSub ( this, "CHARACTER_WINDOW_CHARACTER_MESHRENDER" );
	    m_pRender->CreateSubControl ();
	    RegisterControl ( m_pRender );
		}
		
#if defined(KRT_PARAM)
		CBasicTextButton * pButton = new CBasicTextButton;
		pButton->CreateSub( this, "BASIC_TEXT_BUTTON14", UI_FLAG_XSIZE, CHARACTER_MOBILE_BUTTON );
		pButton->CreateBaseButton( _T("CHARACTER_MOBILE_BUTTON"), 
									CBasicTextButton::SIZE14, 
									CBasicButton::CLICK_FLIP, 
									(char*)ID2GAMEWORD("CHARACTER_MOBILE_BUTTON") );
		RegisterControl( pButton );

		m_pMobileText = CreateStaticControl ( "CHARACTER_MOBILE_TEXT", pFont8Shadow, nAlignLeft );
#endif
	}

	/*{
		CUIControl	TempControl;
		TempControl.Create ( 1, "CHARACTER_SCHOOL_MARK" );

		const UIRECT& rcLocalPos = TempControl.GetLocalPos ();

		CString strSchoolMark[] = 
		{
			"NAME_DISPLAY_SCHOOL1",
			"NAME_DISPLAY_SCHOOL2",
			"NAME_DISPLAY_SCHOOL3"
		};

		for ( int i = 0; i < nSCHOOL_MARK; ++i )
		{
			m_pSchoolMark[i] = CreateControl ( strSchoolMark[i].GetString() );
			m_pSchoolMark[i]->SetLocalPos ( rcLocalPos );
			m_pSchoolMark[i]->SetVisibleSingle ( FALSE );
		}
	}*/
}

void CCharacterWindow::LoadComboData()
{
	m_pComboBoxNickNameRollOver->ClearText ();
	for ( int i = 0; i < EMPTYITEMOPT_SIZE; i++ )
	{
		m_pComboBoxNickNameRollOver->SetTextAlign( TEXT_ALIGN_CENTER_X );
		m_pComboBoxNickNameRollOver->AddText( (char*)ID2GAMEWORD("PARTY_MODAL_ITEM_OPTION", i) );
	}
}
void CCharacterWindow::LoadItem ()
{
	m_pComboBoxNickNameOpen->SetTextAlign( TEXT_ALIGN_CENTER_X );
	m_pComboBoxNickNameOpen->SetText ( (char*)ID2GAMEWORD("PARTY_MODAL_ITEM_OPTION", nIndex) );
}

BOOL CCharacterWindow::IsCurUseArm( EMSLOT emSlot )
{
	if( IsUseArmSub() )
	{
		if( emSlot == SLOT_RHAND || emSlot == SLOT_LHAND ) return FALSE;
	}
	else
	{
		if( emSlot == SLOT_RHAND_S || emSlot == SLOT_LHAND_S ) return FALSE;
	}

	return TRUE;
}

void CCharacterWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		if( m_pPageWearEx )
		{
			if( GLGaeaClient::GetInstance().GetCharacter()->IsUseArmSub() )
			{
				m_pPageWearEx->SetTabButton( FALSE );
			}
			else
			{
				m_pPageWearEx->SetTabButton( TRUE );
			}

		}
	} else{
		ClearRender();
	}
}

void CCharacterWindow::SetArmSwapTabButton( BOOL bArmSub )
{
	if( m_pPageWearEx )
	{
		m_pPageWearEx->SetTabButton( bArmSub );
	}
}

HRESULT	CCharacterWindow::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	GASSERT( pd3dDevice );

	if ( !IsVisible () ) return S_OK;

	HRESULT hr = S_OK;

	//m_pClubMark->SetVisibleSingle ( FALSE );
	{
		hr = CUIWindowEx::Render ( pd3dDevice );
		if( FAILED ( hr ) ) return hr;
	}
	//m_pClubMark->SetVisibleSingle ( TRUE );

	GLCLUB& sCLUB = GLGaeaClient::GetInstance().GetCharacter ()->m_sCLUB;

	//	±æµå¿øÀÌ ¾Æ´Ñ °æ¿ì
	if ( sCLUB.m_dwID==CLUB_NULL ) return S_OK;

	int nServer = static_cast<int>(GLGaeaClient::GetInstance().GetCharacter()->m_dwServerID);
	int nID = static_cast<int>(sCLUB.m_dwID);
	DWORD dwVer = sCLUB.m_dwMarkVER;

 
	m_pRender->SetVisibleSingle ( TRUE );
	{
	hr= m_pRender->Render ( pd3dDevice );
	if( FAILED ( hr ) ) return hr;
	}

	return S_OK;
}