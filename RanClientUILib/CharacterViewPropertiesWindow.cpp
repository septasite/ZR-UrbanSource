#include "StdAfx.h"
#include "./CharacterViewPropertiesWindow.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineUiLib/GUInterface/BasicButtonText.h"
#include "../EngineLib/DxCommon/d3dfont.h"
#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../Interface/BasicTextButton.h"
#include "../Interface/UITextControl.h"
#include "../Interface/GameTextControl.h"
#include "../RanClientLib/G-Logic/GLGaeaClient.h"
#include "GLogicData.h"
#include "GLCharData.h"
#include "../Interface/ModalCallerID.h"
#include "../Interface/ModalWindow.h"
#include "../Interface/InnerInterface.h"

#include "Interface/BasicLineBox.h"
#include "DxGlobalStage.h"
#include "Interface/ModalCallerID.h"
#include "Interface/ConftModalWindow.h"
#include "Interface/PartyModalWindow.h"
#include "Interface/BasicVarTextBox.h"
#include "Interface/BasicChat.h"
#include "Interface/CharacterWindowCharRenderView.h"
#include "Interface/InventoryPageWearView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterViewPropertiesWindow::CCharacterViewPropertiesWindow () :
	m_pNameText ( NULL ),
	m_bSetThisFrame(FALSE),
	m_pNameBox(NULL),
	m_pSkinChar(NULL),
	m_pRender( NULL ),
    m_nOverMenu(NO_ID)
{
}

CCharacterViewPropertiesWindow::~CCharacterViewPropertiesWindow ()
{
}

CBasicTextButton*  CCharacterViewPropertiesWindow::CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText ,_DEFAULT_FONT_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicButtonText* CCharacterViewPropertiesWindow::CreateButtonRed ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText )
{
	CBasicButtonText* pButton = new CBasicButtonText;
	pButton->CreateRanButtonRed ( this, szButton, ControlID );
	pButton->CreateTextBox ( szTextBox, pFont, nAlign );
	pButton->SetOneLineText( strText.GetString() );
	RegisterControl ( pButton );

	return pButton;
}

CBasicTextButton*  CCharacterViewPropertiesWindow::CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE25;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON28", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText , _DEFAULT_FONT_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicTextBox* CCharacterViewPropertiesWindow::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}

void CCharacterViewPropertiesWindow::CreateSubControl ()
{
	CD3DFontPar* pFont8Shadow = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont10Shadow = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	const int nAlignLeft = TEXT_ALIGN_LEFT;
	const int nAlignCenter = TEXT_ALIGN_CENTER_X;		
	const DWORD& dwSilver = NS_UITEXTCOLOR::SILVER;
	const DWORD& dwSubTitle = NS_UITEXTCOLOR::PALEGOLDENROD;

	{
		m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "VIEWCHARACTER_WINDOW_REGION", UI_FLAG_DEFAULT);	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	}
	
	{	
		// Background Khung Trang Bi
		m_pBackLine1 = new CBasicLineBox;
		m_pBackLine1->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine1->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_EQUIP_REGION" );
		RegisterControl ( m_pBackLine1 );

		// Background Khung Thong Tin
		m_pBackLine2 = new CBasicLineBox;
		m_pBackLine2->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine2->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_INFO_REGION" );
		RegisterControl ( m_pBackLine2 );
		
		// Background Khung ADD
		m_pBackLine3 = new CBasicLineBox;
		m_pBackLine3->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine3->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_ADD_REGION" );
		RegisterControl ( m_pBackLine3 );
	}
	
	{
		m_pStatusLine1 = new CBasicLineBox;
		m_pStatusLine1->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pStatusLine1->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_STAT_POINT1_REGION" );
		RegisterControl ( m_pStatusLine1 );	
	
		m_pStatusLine2 = new CBasicLineBox;
		m_pStatusLine2->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pStatusLine2->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_STAT_POINT2_REGION" );
		RegisterControl ( m_pStatusLine2 );	
	
		m_pStatusLine3 = new CBasicLineBox;
		m_pStatusLine3->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pStatusLine3->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_STAT_POINT3_REGION" );
		RegisterControl ( m_pStatusLine3 );
	}

	{
		m_pStatusLine4 = new CBasicLineBox;
		m_pStatusLine4->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pStatusLine4->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_STAT_POINT4_REGION" );
		RegisterControl ( m_pStatusLine4 );

		m_pStatusLine5 = new CBasicLineBox;
		m_pStatusLine5->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pStatusLine5->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_STAT_POINT5_REGION" );
		RegisterControl ( m_pStatusLine5 );

		m_pStatusLine6 = new CBasicLineBox;
		m_pStatusLine6->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pStatusLine6->CreateBaseBoxSkill ( "VIEWCHARACTER_WINDOW_STAT_POINT6_REGION" );
		RegisterControl ( m_pStatusLine6 );
	}
	
	{
		const int nBUTTONSIZE23 = CBasicTextButton::SIZE23;
	CBasicTextButton* pCostumeButton = new CBasicTextButton;
	pCostumeButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, VIEWCHARACTER_COSTUME_BUTTON );
	pCostumeButton->CreateBaseButton ( "VIEWCHARACTER_COSTUME_BUTTON", nBUTTONSIZE23, CBasicButton::RADIO_FLIP, (char*)ID2GAMEWORD("VIEWCHARACTER_BUTTON", 0), _DEFAULT_FONT_FLAG );
	pCostumeButton->SetFlip ( TRUE );
	RegisterControl ( pCostumeButton );
	m_pCostumeButton = pCostumeButton;
	
	CBasicTextButton* pSkillButton = new CBasicTextButton;
	pSkillButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, VIEWCHARACTER_SKILL_BUTTON );
	pSkillButton->CreateBaseButton ( "VIEWCHARACTER_SKILL_BUTTON", nBUTTONSIZE23, CBasicButton::RADIO_FLIP, (char*)ID2GAMEWORD("VIEWCHARACTER_BUTTON", 1), _DEFAULT_FONT_FLAG );
	pSkillButton->SetFlip ( FALSE );
	RegisterControl ( pSkillButton );
	m_pSkillButton = pSkillButton;
	
	}
		
	{
		m_pRender = new CCharacterWindowCharRenderView;
	    m_pRender->CreateSub ( this, "CHARACTER_WINDOW_NEW_CHARACTER_MESHRENDER" );
	    m_pRender->CreateSubControl ();
	    RegisterControl ( m_pRender );

	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );

		m_pPageWearEx = new CInventoryPageWearView;
		m_pPageWearEx->CreateSub ( this, "INVENTORY_PAGE_WEAR_VIEW", UI_FLAG_DEFAULT, INVENTORY_PAGEWEAR_VIEW );
		m_pPageWearEx->CreateSubControl ( nClassType );
		RegisterControl ( m_pPageWearEx );
	}
	{
		CString	strButtonWhisper[1] = 
		{
			"VIEWCHARACTER_WHISPER_BUTTON"
		};
		CString	strButtonAddFriend[1] = 
		{
			"VIEWCHARACTER_FRIEND_BUTTON"
		};
		CString	strButtonParty[1] = 
		{
			"VIEWCHARACTER_PARTY_BUTTON"
		};
		CString	strButtonRefresh[1] = 
		{
			"VIEWCHARACTER_FRESH_BUTTON"
		};
		CString	strButtonAdd[1] = 
		{
			"VIEWCHARACTER_ADD_BUTTON"
		};

		for ( int i = 0; i < 1; i++ )
		{	
			m_pButtonWhisper[i] = CreateButtonRed ( "VIEWCHARACTER_WHISPER_BUTTON", "VIEWCHARACTER_WHISPER_BUTTON_TEXT_POS", pFont8Shadow, TEXT_ALIGN_CENTER_X, VIEWCHARACTER_WHISPER_BUTTON, ID2GAMEWORD("VIEWCHARACTER_BUTTON", 2) );
			m_pButtonAddFriend[i] = CreateButtonRed ( "VIEWCHARACTER_FRIEND_BUTTON", "VIEWCHARACTER_FRIEND_BUTTON_TEXT_POS", pFont8Shadow, TEXT_ALIGN_CENTER_X, VIEWCHARACTER_FRIEND_BUTTON, ID2GAMEWORD("VIEWCHARACTER_BUTTON", 3) );
			m_pButtonParty[i] = CreateButtonRed ( "VIEWCHARACTER_PARTY_BUTTON", "VIEWCHARACTER_PARTY_BUTTON_TEXT_POS", pFont8Shadow, TEXT_ALIGN_CENTER_X, VIEWCHARACTER_PARTY_BUTTON, ID2GAMEWORD("VIEWCHARACTER_BUTTON", 4) );
			m_pButtonRefresh[i] = CreateButtonRed ( "VIEWCHARACTER_FRESH_BUTTON", "VIEWCHARACTER_FRESH_BUTTON_TEXT_POS", pFont8Shadow, TEXT_ALIGN_CENTER_X, VIEWCHARACTER_FRESH_BUTTON, ID2GAMEWORD("VIEWCHARACTER_BUTTON", 5) );
			//m_pButtonAdd[i] = CreateButtonRed ( "VIEWCHARACTER_ADD_BUTTON", "VIEWCHARACTER_ADD_BUTTON_TEXT_POS", pFont8Shadow, TEXT_ALIGN_CENTER_X, VIEWCHARACTER_ADD_BUTTON, ID2GAMEWORD("VIEWCHARACTER_BUTTON", 6) );
		}
	}
		
	/*{
		pBackGroundName = CreateControl ( "BACKGROUND_CHARACTER_NAME", BACKGROUND_CHARACTER_NAME );
	}*/
	{
		//Level Green Arrow
		pCharacterLevelGreenArrow = new CUIControl;
		pCharacterLevelGreenArrow->CreateSub ( this, "CHARINFOVIEW_LEVEL_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterLevelGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterLevelGreenArrow );
		//Level Red Arrow
		pCharacterLevelRedArrow = new CUIControl;
		pCharacterLevelRedArrow->CreateSub ( this, "CHARINFOVIEW_LEVEL_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterLevelRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterLevelRedArrow );

		//Pow Green Arrow
		pCharacterPowGreenArrow = new CUIControl;
		pCharacterPowGreenArrow->CreateSub ( this, "CHARINFOVIEW_POW_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterPowGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterPowGreenArrow );
		//Pow Red Arrow
		pCharacterPowRedArrow = new CUIControl;
		pCharacterPowRedArrow->CreateSub ( this, "CHARINFOVIEW_POW_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterPowRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterPowRedArrow );

		//Dex Green Arrow
		pCharacterDexGreenArrow = new CUIControl;
		pCharacterDexGreenArrow->CreateSub ( this, "CHARINFOVIEW_DEX_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterDexGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDexGreenArrow );
		//Dex Red Arrow
		pCharacterDexRedArrow = new CUIControl;
		pCharacterDexRedArrow->CreateSub ( this, "CHARINFOVIEW_DEX_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterDexRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDexRedArrow );

		//Int Green Arrow
		pCharacterIntGreenArrow = new CUIControl;
		pCharacterIntGreenArrow->CreateSub ( this, "CHARINFOVIEW_INT_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterIntGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterIntGreenArrow );
		//Int Red Arrow
		pCharacterIntRedArrow = new CUIControl;
		pCharacterIntRedArrow->CreateSub ( this, "CHARINFOVIEW_INT_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterIntRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterIntRedArrow );

		//Str/Vit Green Arrow
		pCharacterStrGreenArrow = new CUIControl;
		pCharacterStrGreenArrow->CreateSub ( this, "CHARINFOVIEW_STR_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterStrGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterStrGreenArrow );
		//Str/Vit Red Arrow
		pCharacterStrRedArrow = new CUIControl;
		pCharacterStrRedArrow->CreateSub ( this, "CHARINFOVIEW_STR_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterStrRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterStrRedArrow );

		//Sta Green Arrow
		pCharacterStaGreenArrow = new CUIControl;
		pCharacterStaGreenArrow->CreateSub ( this, "CHARINFOVIEW_STA_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterStaGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterStaGreenArrow );
		//Sta Red Arrow
		pCharacterStaRedArrow = new CUIControl;
		pCharacterStaRedArrow->CreateSub ( this, "CHARINFOVIEW_STA_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterStaRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterStaRedArrow );

		//Damage Low Green Arrow
		pCharacterDamageLowGreenArrow = new CUIControl;
		pCharacterDamageLowGreenArrow->CreateSub ( this, "CHARINFOVIEW_DAMAGELOW_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterDamageLowGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDamageLowGreenArrow );
		//Damage Low Red Arrow
		pCharacterDamageLowRedArrow = new CUIControl;
		pCharacterDamageLowRedArrow->CreateSub ( this, "CHARINFOVIEW_DAMAGELOW_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterDamageLowRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDamageLowRedArrow );

		//Damage High Green Arrow
		pCharacterDamageHighGreenArrow = new CUIControl;
		pCharacterDamageHighGreenArrow->CreateSub ( this, "CHARINFOVIEW_DAMAGEHIGH_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterDamageHighGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDamageHighGreenArrow );
		//Damage High Red Arrow
		pCharacterDamageHighRedArrow = new CUIControl;
		pCharacterDamageHighRedArrow->CreateSub ( this, "CHARINFOVIEW_DAMAGEHIGH_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterDamageHighRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDamageHighRedArrow );

		//Defense Green Arrow
		pCharacterDefenseGreenArrow = new CUIControl;
		pCharacterDefenseGreenArrow->CreateSub ( this, "CHARINFOVIEW_DEFENSE_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterDefenseGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDefenseGreenArrow );
		//Defense Red Arrow
		pCharacterDefenseRedArrow = new CUIControl;
		pCharacterDefenseRedArrow->CreateSub ( this, "CHARINFOVIEW_DEFENSE_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterDefenseRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterDefenseRedArrow );

		//Fight Green Arrow
		pCharacterReqPaGreenArrow = new CUIControl;
		pCharacterReqPaGreenArrow->CreateSub ( this, "CHARINFOVIEW_FIGHT_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterReqPaGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterReqPaGreenArrow );
		//Fight Red Arrow
		pCharacterReqPaRedArrow = new CUIControl;
		pCharacterReqPaRedArrow->CreateSub ( this, "CHARINFOVIEW_FIGHT_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterReqPaRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterReqPaRedArrow );

		//Shoot Green Arrow
		pCharacterReqSaGreenArrow = new CUIControl;
		pCharacterReqSaGreenArrow->CreateSub ( this, "CHARINFOVIEW_SHOOT_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterReqSaGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterReqSaGreenArrow );
		//Shoot Red Arrow
		pCharacterReqSaRedArrow = new CUIControl;
		pCharacterReqSaRedArrow->CreateSub ( this, "CHARINFOVIEW_SHOOT_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterReqSaRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterReqSaRedArrow );

		//Shoot Green Arrow
		pCharacterReqMaGreenArrow = new CUIControl;
		pCharacterReqMaGreenArrow->CreateSub ( this, "CHARINFOVIEW_STAMINA_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterReqMaGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterReqMaGreenArrow );
		//Shoot Red Arrow
		pCharacterReqMaRedArrow = new CUIControl;
		pCharacterReqMaRedArrow->CreateSub ( this, "CHARINFOVIEW_STAMINA_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterReqMaRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterReqMaRedArrow );

		//HitRate Green Arrow
		pCharacterHitRateGreenArrow = new CUIControl;
		pCharacterHitRateGreenArrow->CreateSub ( this, "CHARINFOVIEW_HIT_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterHitRateGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterHitRateGreenArrow );
		//HitRate Red Arrow
		pCharacterHitRateRedArrow = new CUIControl;
		pCharacterHitRateRedArrow->CreateSub ( this, "CHARINFOVIEW_HIT_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterHitRateRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterHitRateRedArrow );

		//AvoidRate Green Arrow
		pCharacterAvoidRateGreenArrow = new CUIControl;
		pCharacterAvoidRateGreenArrow->CreateSub ( this, "CHARINFOVIEW_AVOID_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterAvoidRateGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterAvoidRateGreenArrow );
		//AvoidRate Red Arrow
		pCharacterAvoidRateRedArrow = new CUIControl;
		pCharacterAvoidRateRedArrow->CreateSub ( this, "CHARINFOVIEW_AVOID_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterAvoidRateRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterAvoidRateRedArrow );

		//HP Green Arrow
		pCharacterHPGreenArrow = new CUIControl;
		pCharacterHPGreenArrow->CreateSub ( this, "CHARINFOVIEW_HP_GREENARROW",  UI_FLAG_DEFAULT );
		pCharacterHPGreenArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterHPGreenArrow );
		//HP Red Arrow
		pCharacterHPRedArrow = new CUIControl;
		pCharacterHPRedArrow->CreateSub ( this, "CHARINFOVIEW_HP_REDARROW",  UI_FLAG_DEFAULT );
		pCharacterHPRedArrow->SetVisibleSingle ( FALSE );
		RegisterControl ( pCharacterHPRedArrow );
	}
	{	
		CBasicButton * pButtonInv = new CBasicButton;
		pButtonInv->CreateSub( this, "VIEWCHARACTERHELP_BUTTON", UI_FLAG_BOTTOM, VIEWCHARACTERHELP_BUTTON );
		pButtonInv->CreateFlip( "VIEWCHARACTERHELP_BUTTON_OVER", CBasicButton::MOUSEIN_FLIP );
		pButtonInv->SetUseGlobalAction ( TRUE );	
		RegisterControl( pButtonInv );
	}
	
	{	
		CBasicButton * pButtonInv = new CBasicButton;
		pButtonInv->CreateSub( this, "VIEWCHARACTER_REFRESH_BUTTON", UI_FLAG_BOTTOM, VIEWCHARACTER_REFRESH_BUTTON );
		pButtonInv->CreateFlip( "VIEWCHARACTER_REFRESH_BUTTON_OVER", CBasicButton::MOUSEIN_FLIP );
		pButtonInv->SetUseGlobalAction ( TRUE );	
		RegisterControl( pButtonInv );
	}
	
	/*{	
		CBasicButton * pButtonInv = new CBasicButton;
		pButtonInv->CreateSub( this, "VIEWCHARACTER_AROW_BUTTON", UI_FLAG_BOTTOM, VIEWCHARACTER_AROW_BUTTON );
		pButtonInv->CreateFlip( "VIEWCHARACTER_AROW_BUTTON_OVER", CBasicButton::MOUSEIN_FLIP );
		pButtonInv->SetUseGlobalAction ( TRUE );	
		RegisterControl( pButtonInv );
	}*/
	
	/*{
		pButtonCheck0 = CreateControl ( "CHECK_BUTTON0", CHECK_BUTTON0 );
		pButtonCheckOver0 = CreateControl ( "CHECK_BUTTON_OVER0");
		pButtonCheckOver0->SetVisibleSingle ( FALSE );
	}
	{
		pButtonCheck1 = CreateControl ( "CHECK_BUTTON1", CHECK_BUTTON1 );
		pButtonCheckOver1 = CreateControl ( "CHECK_BUTTON_OVER1");
		pButtonCheckOver1->SetVisibleSingle ( FALSE );
	}
	{
		pButtonCheck2 = CreateControl ( "CHECK_BUTTON2", CHECK_BUTTON2 );
		pButtonCheckOver2 = CreateControl ( "CHECK_BUTTON_OVER2");
		pButtonCheckOver2->SetVisibleSingle ( FALSE );
	}
	{
		pButtonCheck3 = CreateControl ( "CHECK_BUTTON3", CHECK_BUTTON3 );
		pButtonCheckOver3 = CreateControl ( "CHECK_BUTTON_OVER3");
		pButtonCheckOver3->SetVisibleSingle ( FALSE );
	}*/
	
	m_pNameText = CreateStaticControl 	( "2014_VIEWCHARACTER_NAME_TEXT", pFont10Shadow, TEXT_ALIGN_CENTER_X );

	m_pLevelText = CreateStaticControl 	( "2014_VIEWCHARACTER_LEVEL_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pLevelTextStatic = CreateStaticControl ( "2014_VIEWCHARACTER_LEVEL_CHU", pFont8Shadow, nAlignLeft );
	m_pLevelTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 1), dwSilver );
	
	m_pAcademyText = CreateStaticControl ( "2014_VIEWCHARACTER_ACADEMY_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
	m_pClubText = CreateStaticControl 	( "2014_VIEWCHARACTER_CLUB_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
    //m_pClassText = CreateStaticControl 	( "2014_VIEWCHARACTER_CLASS_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
	
	m_pPkWText = CreateStaticControl ( "2014_VIEWCHARACTER_PKW_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
	m_pPkLText = CreateStaticControl ( "2014_VIEWCHARACTER_PKL_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
	
	m_pMoneyText = CreateStaticControl 	( "2014_VIEWCHARACTER_MONEY_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
	m_pMoney2Text = CreateStaticControl ( "2014_VIEWCHARACTER_MONEY2_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
	m_pMoney3Text = CreateStaticControl ( "2014_VIEWCHARACTER_MONEY3_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );
	
	m_pPowText = CreateStaticControl ( "2014_VIEWCHARACTER_POW_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pDexText = CreateStaticControl ( "2014_VIEWCHARACTER_DEX_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
    m_pSpiText = CreateStaticControl ( "2014_VIEWCHARACTER_SPI_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pStrText = CreateStaticControl ( "2014_VIEWCHARACTER_STR_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pStaText = CreateStaticControl ( "2014_VIEWCHARACTER_STA_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	
	m_pPowTextStatic = CreateStaticControl ( "2014_VIEWCHARACTER_POW_CHU", pFont8Shadow, nAlignLeft );
	m_pDexTextStatic = CreateStaticControl ( "2014_VIEWCHARACTER_DEX_CHU", pFont8Shadow, nAlignLeft );
	m_pSpiTextStatic = CreateStaticControl ( "2014_VIEWCHARACTER_SPI_CHU", pFont8Shadow, nAlignLeft );
	m_pStrTextStatic = CreateStaticControl ( "2014_VIEWCHARACTER_STR_CHU", pFont8Shadow, nAlignLeft );
	m_pStaTextStatic = CreateStaticControl ( "2014_VIEWCHARACTER_STA_CHU", pFont8Shadow, nAlignLeft );

	m_pPowTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC", 0), dwSilver );
	m_pDexTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC", 1), dwSilver );
	m_pSpiTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC", 2), dwSilver );
	m_pStrTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC", 4), dwSilver );
	m_pStaTextStatic->AddText ( ID2GAMEWORD("CHARACTER_STAT_STATIC", 5), dwSilver );
	
	m_pDamageLowText = CreateStaticControl 	( "2014_VIEWCHARACTER_DAMAGE_LOW_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pDamageHighText = CreateStaticControl ( "2014_VIEWCHARACTER_DAMAGE_HIGH_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pDefenseText = CreateStaticControl 	( "2014_VIEWCHARACTER_DEFENSE_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pReqPaText = CreateStaticControl 		( "2014_VIEWCHARACTER_FIGHT_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pReqSaText = CreateStaticControl 		( "2014_VIEWCHARACTER_SHOOT_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pReqMaText = CreateStaticControl 		( "2014_VIEWCHARACTER_STAMINA_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pHitRateText = CreateStaticControl 	( "2014_VIEWCHARACTER_HIT_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pAvoidRateText = CreateStaticControl 	( "2014_VIEWCHARACTER_AVOID_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pHPText = CreateStaticControl 		( "2014_VIEWCHARACTER_HP_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pMPText = CreateStaticControl 		( "2014_VIEWCHARACTER_MP_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pSPText = CreateStaticControl 		( "2014_VIEWCHARACTER_SP_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	
	m_pDamageHighTextStatic = CreateStaticControl	( "2014_VIEWCHARACTER_ATTACK_MAX_CHU", pFont, nAlignLeft );
	m_pDamageLowTextStatic = CreateStaticControl 	( "2014_VIEWCHARACTER_ATTACK_MIN_CHU", pFont, nAlignLeft );
	m_pDefenseTextStatic = CreateStaticControl 		( "2014_VIEWCHARACTER_DEFENSE_CHU", pFont, nAlignLeft );
	m_pReqPaTextStatic = CreateStaticControl 		( "2014_VIEWCHARACTER_FIGHT_CHU", pFont, nAlignLeft );
	m_pReqSaTextStatic = CreateStaticControl 		( "2014_VIEWCHARACTER_SHOOT_CHU", pFont, nAlignLeft );
	m_pReqMaTextStatic = CreateStaticControl 		( "2014_VIEWCHARACTER_STAMINA_CHU", pFont, nAlignLeft );
	m_pHitRateTextStatic = CreateStaticControl 		( "2014_VIEWCHARACTER_HIT_CHU", pFont, nAlignLeft );
	m_pAvoidRateTextv = CreateStaticControl 		( "2014_VIEWCHARACTER_AVOID_CHU", pFont, nAlignLeft );
	m_pHPTextStatic = CreateStaticControl 			( "2014_VIEWCHARACTER_HP_CHU", pFont, nAlignLeft );
	m_pMPTextStatic = CreateStaticControl 			( "2014_VIEWCHARACTER_MP_CHU", pFont, nAlignLeft );
	m_pSPTextStatic = CreateStaticControl 			( "2014_VIEWCHARACTER_SP_CHU", pFont, nAlignLeft );
	
	m_pDamageHighTextStatic->AddText 	( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 14), dwSilver );
	m_pDamageLowTextStatic->AddText 	( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 15), dwSilver );
	m_pDefenseTextStatic->AddText 		( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 3), dwSilver );
	m_pReqPaTextStatic->AddText 		( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 4), dwSilver );
	m_pReqSaTextStatic->AddText 		( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 5), dwSilver );
	m_pReqMaTextStatic->AddText 		( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 11), dwSilver );
	m_pHitRateTextStatic->AddText 		( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 9), dwSilver );
	m_pAvoidRateTextv->AddText 			( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 10), dwSilver );
	m_pHPTextStatic->AddText 			( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 16), dwSilver );
	m_pMPTextStatic->AddText 			( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 17), dwSilver );
	m_pSPTextStatic->AddText 			( ID2GAMEWORD("CHARACTER_STATUS_STATIC", 18), dwSilver );
	
	m_pFireText = CreateStaticControl 		( "2014_VIEWCHARACTER_FIRE_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pColdText = CreateStaticControl 		( "2014_VIEWCHARACTER_COLD_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pElectricText = CreateStaticControl 	( "2014_VIEWCHARACTER_ELEC_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pPoisonText = CreateStaticControl 	( "2014_VIEWCHARACTER_POISON_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pSpiritText = CreateStaticControl 	( "2014_VIEWCHARACTER_SPIRIT_TEXT", pFont8Shadow, TEXT_ALIGN_RIGHT );
	
	m_pFireTextStatic = CreateStaticControl 	( "2014_VIEWCHARACTER_FIRE_RESIST_TEXT", pFont8Shadow, nAlignLeft );
	m_pColdTextStatic = CreateStaticControl 	( "2014_VIEWCHARACTER_COLD_RESIST_TEXT", pFont8Shadow, nAlignLeft );
	m_pElectricTextStatic = CreateStaticControl ( "2014_VIEWCHARACTER_ELEC_RESIST_TEXT", pFont8Shadow, nAlignLeft );
	m_pPoisonTextStatic = CreateStaticControl 	( "2014_VIEWCHARACTER_POISON_RESIST_TEXT", pFont8Shadow, nAlignLeft );
	m_pSpiritTextStatic = CreateStaticControl 	( "2014_VIEWCHARACTER_SPIRIT_RESIST_TEXT", pFont8Shadow, nAlignLeft );

	m_pFireTextStatic->AddText 		( ID2GAMEWORD("CHARACTER_RESI_STATIC", 1), dwSilver );
	m_pColdTextStatic->AddText 		( ID2GAMEWORD("CHARACTER_RESI_STATIC", 2), dwSilver );
	m_pElectricTextStatic->AddText 	( ID2GAMEWORD("CHARACTER_RESI_STATIC", 3), dwSilver );
	m_pPoisonTextStatic->AddText 	( ID2GAMEWORD("CHARACTER_RESI_STATIC", 4), dwSilver );
	m_pSpiritTextStatic->AddText 	( ID2GAMEWORD("CHARACTER_RESI_STATIC", 5), dwSilver );
	//
	m_pStaffText = CreateStaticControl ( "2014_VIEWCHARACTER_STAFF_TEXT", pFont8Shadow, TEXT_ALIGN_LEFT );

	m_pLevelTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_LEVEL_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pPowTextCompare	= CreateStaticControl 	( "2014_VIEWCHARACTER_POW_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pDexTextCompare	= CreateStaticControl 	( "2014_VIEWCHARACTER_DEX_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pIntTextCompare	= CreateStaticControl 	( "2014_VIEWCHARACTER_INT_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pStrTextCompare	= CreateStaticControl 	( "2014_VIEWCHARACTER_STR_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pStaTextCompare	= CreateStaticControl 	( "2014_VIEWCHARACTER_STA_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pDamageLowTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_LOWDAMAGE_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pDamageHighTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_HIGHDAMAGE_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pDefenseTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_DEFENSE_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pReqPaTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_FIGHT_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pReqSaTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_SHOOT_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pReqMaTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_STAMINA_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pHitRateTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_HIT_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pAvoidRateTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_AVOID_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );
	m_pHPTextCompare = CreateStaticControl 	( "2014_VIEWCHARACTER_HP_TEXT_COMPARE", pFont8Shadow, TEXT_ALIGN_RIGHT );

}
void CCharacterViewPropertiesWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}
void CCharacterViewPropertiesWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle( bVisible );
}
void CCharacterViewPropertiesWindow::SetGlobalPos(const D3DXVECTOR2& vPos)
{
	CUIGroup::SetGlobalPos( vPos );

}

void CCharacterViewPropertiesWindow::SetViewCharInfo ( CString strPlayerName, DWORD dwMasterID )
{		
	m_dwMasterID = dwMasterID;
}

DWORD CCharacterViewPropertiesWindow::GetMasterID ()
{
	return m_dwMasterID;
}

void CCharacterViewPropertiesWindow::SetName ( NET_MSG_GENERIC* nmg )
{

	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;



	CString strCombine1;
	strCombine1.Format ( "[Name:%s]", pNetMsg->Data.szName );

	if ( m_pNameText )
	{
		m_pNameText->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::GOLD );
	}
}

void CCharacterViewPropertiesWindow::SetLevel ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wLevelChar = GLGaeaClient::GetInstance().GetCharacter()->m_wLevel;
	const WORD& wLevel = pNetMsg->Data.wLevel;

	m_pLevelTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wLevel );
	if ( m_pLevelText )
	{
		m_pLevelText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
	}

	CString strCombine1;
	if ( (wLevel <= wLevelChar) && m_pLevelTextCompare )
	{
		strCombine1.Format ( "%d", wLevelChar - wLevel );
		pCharacterLevelGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterLevelRedArrow->SetVisibleSingle ( FALSE );
		m_pLevelTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wLevel > wLevelChar) && m_pLevelTextCompare )
	{
		strCombine1.Format ( "%d", wLevel - wLevelChar);
		pCharacterLevelRedArrow->SetVisibleSingle ( TRUE );
		pCharacterLevelGreenArrow->SetVisibleSingle ( FALSE );
		m_pLevelTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}

}

void CCharacterViewPropertiesWindow::SetAcademy ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	if ( m_pAcademyText )
	{
		CString strCombine;
		strCombine.Format ( "%s,%s",ID2GAMEWORD("ACADEMY_NAME", pNetMsg->Data.wSchool), COMMENT::CHARCLASS[CharClassToIndex( pNetMsg->Data.emClass)].c_str()  );
		m_pAcademyText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
	}
}

/*void CCharacterViewPropertiesWindow::SetClass ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	

	if ( m_pClassText )
	{
		CString strCombine;
		strCombine.Format ( "%s: %s",ID2GAMEWORD("VIEW_CHARACTER_SOCIAL_STATIC", 3), COMMENT::CHARCLASS[CharClassToIndex( pNetMsg->Data.emClass)].c_str() );
		m_pClassText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
	}
}*/

void CCharacterViewPropertiesWindow::SetClub ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const DWORD& wClub = pNetMsg->Data.dwGuild;

	DWORD dwCharID = pNetMsg->Data.dwCharID;

	CString strCombine;


	strCombine.Format ( "%s: %s", ID2GAMEWORD("VIEW_CHARACTER_SOCIAL_STATIC", 18),pNetMsg->Data.szClubName );

	if ( m_pClubText )
	{
		if(wClub == 0)
		{
			strCombine.Format ( "%s: %s",ID2GAMEWORD("VIEW_CHARACTER_SOCIAL_STATIC", 18),ID2GAMEWORD("CLUB_TEXT_STATIC", 14) );
		}

		m_pClubText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::YELLOW );
	}

}

void CCharacterViewPropertiesWindow::SetPkW ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const DWORD& m_dwPkWin = pNetMsg->Data.m_dwPkWin;

	CString strCombine;
	strCombine.Format ( "%s: %d", ID2GAMEWORD("VIEW_CHARACTER_SOCIAL_STATIC", 5), m_dwPkWin );
	if ( m_pPkWText )
	{
		m_pPkWText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
	}

}

void CCharacterViewPropertiesWindow::SetPkL ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const DWORD& m_dwPkLoss = pNetMsg->Data.m_dwPkLoss;

	CString strCombine;
	strCombine.Format ( "%s: %d", ID2GAMEWORD("VIEW_CHARACTER_SOCIAL_STATIC", 6), m_dwPkLoss );
	if ( m_pPkLText )
	{
		m_pPkLText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
	}
}

void CCharacterViewPropertiesWindow::SetMoney ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	CString strCombine;
	LONGLONG lnMoney = pNetMsg->Data.m_lnMoney;

	CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( lnMoney, 3, "," );

	strCombine.Format ( "%s: %s", ID2GAMEWORD("VIEW_CHARACTER_SOCIAL_STATIC", 15), strTemp ); 
	m_pMoney2Text->SetOneLineText ( strCombine, NS_UITEXTCOLOR::GOLD );

}

void CCharacterViewPropertiesWindow::SetMoney2 ( NET_MSG_GENERIC* nmg )
{
	/*GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	CString strCombine;
	LONGLONG lnMoney2 = pNetMsg->Data.m_lnVoteP;

	CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( lnMoney2, 3, "," );

	strCombine.Format ( "%s: %s", ID2GAMEWORD("VIEW_CHARACTER_SOCIAL_STATIC", 16), strTemp ); 

	//m_pMoney2Text->SetOneLineText ( strCombine, NS_UITEXTCOLOR::GREEN );*/

}

void CCharacterViewPropertiesWindow::SetMoney3 ( NET_MSG_GENERIC* nmg )
{
	/*GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	DWORD wTotal = pNetMsg->Data.m_sStats.GetTotal();
/
	CString strCombine;

	//CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( lnMoney3, 3, "," );

	//strCombine.Format ( "Total Stats: %d", wTotal); 

	//m_pMoney3Text->SetOneLineText ( strCombine, NS_UITEXTCOLOR::GOLD );*/

}

void CCharacterViewPropertiesWindow::SetPow ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;
	WORD wPowChar = GLGaeaClient::GetInstance().GetCharacter()->m_sSUMSTATS.dwPow;
	WORD wPow = pNetMsg->Data.m_sStats.dwPow;

	m_pPowText->ClearText ();
	m_pPowTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wPow);
	m_pPowText->AddText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wPow <= wPowChar) && m_pPowTextCompare )
	{
		strCombine1.Format ( "%d", wPowChar - wPow);
		pCharacterPowGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterPowRedArrow->SetVisibleSingle ( FALSE );
		m_pPowTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wPow > wPowChar) && m_pPowTextCompare )
	{
		strCombine1.Format ( "%d", wPow - wPowChar);
		pCharacterPowRedArrow->SetVisibleSingle ( TRUE );
		pCharacterPowGreenArrow->SetVisibleSingle ( FALSE );
		m_pPowTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}

}

void CCharacterViewPropertiesWindow::SetDex ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wDexChar = GLGaeaClient::GetInstance().GetCharacter()->m_sSUMSTATS.dwDex;
	const WORD& wDex = pNetMsg->Data.m_sStats.dwDex;

	m_pDexText->ClearText ();
	m_pDexTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wDex );
	m_pDexText->AddText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wDex <= wDexChar) && m_pDexTextCompare )
	{
		strCombine1.Format ( "%d", wDexChar - wDex);
		pCharacterDexGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterDexRedArrow->SetVisibleSingle ( FALSE );
		m_pDexTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wDex > wDexChar) && m_pDexTextCompare )
	{
		strCombine1.Format ( "%d", wDex - wDexChar);
		pCharacterDexRedArrow->SetVisibleSingle ( TRUE );
		pCharacterDexGreenArrow->SetVisibleSingle ( FALSE );
		m_pDexTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetSpi ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wSpiChar = GLGaeaClient::GetInstance().GetCharacter()->m_sSUMSTATS.dwSpi;
	const WORD& wSpi = pNetMsg->Data.m_sStats.dwSpi;

	m_pSpiText->ClearText ();
	m_pIntTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wSpi );
	m_pSpiText->AddText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wSpi <= wSpiChar) && m_pIntTextCompare )
	{
		strCombine1.Format ( "%d", wSpiChar - wSpi );
		pCharacterIntGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterIntRedArrow->SetVisibleSingle ( FALSE );
		m_pIntTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wSpi > wSpiChar) && m_pIntTextCompare )
	{
		strCombine1.Format ( "%d", wSpi - wSpiChar);
		pCharacterIntRedArrow->SetVisibleSingle ( TRUE );
		pCharacterIntGreenArrow->SetVisibleSingle ( FALSE );
		m_pIntTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetStr ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wStrChar = GLGaeaClient::GetInstance().GetCharacter()->m_sSUMSTATS.dwStr;
	const WORD& wStr = pNetMsg->Data.m_sStats.dwStr;

	m_pStrText->ClearText ();
	m_pStrTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wStr ); 
	m_pStrText->AddText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wStr <= wStrChar) && m_pStrTextCompare )
	{
		strCombine1.Format ( "%d", wStrChar - wStr);
		pCharacterStrGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterStrRedArrow->SetVisibleSingle ( FALSE );
		m_pStrTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wStr> wStrChar) && m_pStrTextCompare )
	{
		strCombine1.Format ( "%d", wStr - wStrChar);
		pCharacterStrRedArrow->SetVisibleSingle ( TRUE );
		pCharacterStrGreenArrow->SetVisibleSingle ( FALSE );
		m_pStrTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetSta ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wStaChar = GLGaeaClient::GetInstance().GetCharacter()->m_sSUMSTATS.dwSta;
	const WORD& wSta = pNetMsg->Data.m_sStats.dwSta;

	m_pStaText->ClearText ();
	m_pStaTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wSta ); 
	m_pStaText->AddText ( strCombine, NS_UITEXTCOLOR::SILVER );

	
	CString strCombine1;
	if ( (wSta <= wStaChar) && m_pStaTextCompare )
	{
		strCombine1.Format ( "%d", wStaChar - wSta);
		pCharacterStaGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterStaRedArrow->SetVisibleSingle ( FALSE );
		m_pStaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wSta > wStaChar) && m_pStaTextCompare )
	{
		strCombine1.Format ( "%d", wSta - wStaChar);
		pCharacterStaRedArrow->SetVisibleSingle ( TRUE );
		pCharacterStaGreenArrow->SetVisibleSingle ( FALSE );
		m_pStaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}

}

void CCharacterViewPropertiesWindow::SetDamage ( NET_MSG_GENERIC* nmg )
{	
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const int& nLow = pNetMsg->Data.m_gdDAMAGE_PHYSIC.dwLow;
	const int& nHigh = pNetMsg->Data.m_gdDAMAGE_PHYSIC.dwHigh;
	const int& nLowChar = GLGaeaClient::GetInstance().GetCharacter()->m_gdDAMAGE_PHYSIC.dwLow;
	const int& nHighChar = GLGaeaClient::GetInstance().GetCharacter()->m_gdDAMAGE_PHYSIC.dwHigh;

	m_pDamageLowText->ClearText ();
	m_pDamageHighText->ClearText();
	m_pDamageLowTextCompare->ClearText();
	m_pDamageHighTextCompare->ClearText();
	
	CString strCombine;
	strCombine.Format ( "%d", nLow );
	if ( m_pDamageLowText ) m_pDamageLowText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
	
	strCombine.Format ( "%d", nHigh );
	if ( m_pDamageHighText ) m_pDamageHighText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	
	CString strCombine1;
	if ( (nLow <= nLowChar) && m_pDamageLowTextCompare )
	{
		strCombine1.Format ( "%d", nLowChar - nLow);
		pCharacterDamageLowGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterDamageLowRedArrow->SetVisibleSingle ( FALSE );
		m_pDamageLowTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (nLow > nLowChar) && m_pDamageLowTextCompare )
	{
		strCombine1.Format ( "%d", nLow - nLowChar);
		pCharacterDamageLowRedArrow->SetVisibleSingle ( TRUE );
		pCharacterDamageLowGreenArrow->SetVisibleSingle ( FALSE );
		m_pDamageLowTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}

	CString strCombine2;
	if ( (nHigh <= nHighChar) && m_pDamageHighTextCompare )
	{
		strCombine2.Format ( "%d", nHighChar - nHigh);
		pCharacterDamageHighGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterDamageHighRedArrow->SetVisibleSingle ( FALSE );
		m_pDamageHighTextCompare->SetOneLineText ( strCombine2, NS_UITEXTCOLOR::LIME );
	}

	if ( (nHigh > nHighChar) && m_pDamageHighTextCompare )
	{
		strCombine2.Format ( "%d", nHigh - nHighChar);
		pCharacterDamageHighRedArrow->SetVisibleSingle ( TRUE );
		pCharacterDamageHighGreenArrow->SetVisibleSingle ( FALSE );
		m_pDamageHighTextCompare->SetOneLineText ( strCombine2, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetDefense ( NET_MSG_GENERIC* nmg )
{	
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const int& nDEFENSE_SKILL = pNetMsg->Data.m_nDEFENSE_SKILL;
	const int& nDEFENSE_SKILL_CHAR = GLGaeaClient::GetInstance().GetCharacter()->m_nDEFENSE_SKILL;

	m_pDefenseText->ClearText ();
	m_pDefenseTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", nDEFENSE_SKILL );
	if ( m_pDefenseText ) m_pDefenseText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (nDEFENSE_SKILL <= nDEFENSE_SKILL_CHAR) && m_pDefenseTextCompare )
	{
		strCombine1.Format ( "%d", nDEFENSE_SKILL_CHAR - nDEFENSE_SKILL);
		pCharacterDefenseGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterDefenseRedArrow->SetVisibleSingle ( FALSE );
		m_pDefenseTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (nDEFENSE_SKILL > nDEFENSE_SKILL_CHAR) && m_pDefenseTextCompare )
	{
		strCombine1.Format ( "%d", nDEFENSE_SKILL - nDEFENSE_SKILL_CHAR);
		pCharacterDefenseRedArrow->SetVisibleSingle ( TRUE );
		pCharacterDefenseGreenArrow->SetVisibleSingle ( FALSE );
		m_pDefenseTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetReqPa ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wReqPaChar = GLGaeaClient::GetInstance().GetCharacter()->m_wSUM_PA;
	const WORD& wReqPa = pNetMsg->Data.m_wSUM_PA;

	m_pReqPaText->ClearText ();
	m_pReqPaTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wReqPa );
	if ( m_pReqPaText ) m_pReqPaText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wReqPa <= wReqPaChar) && m_pReqPaTextCompare )
	{
		strCombine1.Format ( "%d", wReqPaChar - wReqPa);
		pCharacterReqPaGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterReqPaRedArrow->SetVisibleSingle ( FALSE );
		m_pReqPaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wReqPa > wReqPaChar) && m_pReqPaTextCompare )
	{
		strCombine1.Format ( "%d", wReqPa - wReqPaChar);
		pCharacterReqPaRedArrow->SetVisibleSingle ( TRUE );
		pCharacterReqPaGreenArrow->SetVisibleSingle ( FALSE );
		m_pReqPaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetReqSa ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wReqSaChar = GLGaeaClient::GetInstance().GetCharacter()->m_wSUM_SA;
	const WORD& wReqSa = pNetMsg->Data.m_wSUM_SA;

	m_pReqSaText->ClearText ();
	m_pReqSaTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wReqSa );
	if ( m_pReqSaText ) m_pReqSaText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wReqSa <= wReqSaChar) && m_pReqSaTextCompare )
	{
		strCombine1.Format ( "%d", wReqSaChar - wReqSa);
		pCharacterReqSaGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterReqSaRedArrow->SetVisibleSingle ( FALSE );
		m_pReqSaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wReqSa > wReqSaChar) && m_pReqSaTextCompare )
	{
		strCombine1.Format ( "%d", wReqSa - wReqSaChar);
		pCharacterReqSaRedArrow->SetVisibleSingle ( TRUE );
		pCharacterReqSaGreenArrow->SetVisibleSingle ( FALSE );
		m_pReqSaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetReqMa ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wReqMaChar = GLGaeaClient::GetInstance().GetCharacter()->m_wSUM_MA;
	const WORD& wReqMa = pNetMsg->Data.m_wSUM_MA;

	m_pReqMaText->ClearText ();
	m_pReqMaTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wReqMa );
	if ( m_pReqMaText ) m_pReqMaText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wReqMa <= wReqMaChar) && m_pReqMaTextCompare )
	{
		strCombine1.Format ( "%d", wReqMaChar - wReqMa);
		pCharacterReqMaGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterReqMaRedArrow->SetVisibleSingle ( FALSE );
		m_pReqMaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wReqMa > wReqMaChar) && m_pReqMaTextCompare )
	{
		strCombine1.Format ( "%d", wReqMa - wReqMaChar);
		pCharacterReqMaRedArrow->SetVisibleSingle ( TRUE );
		pCharacterReqMaGreenArrow->SetVisibleSingle ( FALSE );
		m_pReqMaTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetHitRate ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const WORD& wHitRateChar = GLGaeaClient::GetInstance().GetCharacter()->m_nSUM_HIT;
	const WORD& wHitRate = pNetMsg->Data.m_nSUM_HIT;

	m_pHitRateText->ClearText ();
	m_pHitRateTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wHitRate );
	if ( m_pHitRateText ) m_pHitRateText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wHitRate <= wHitRateChar) && m_pHitRateTextCompare )
	{
		strCombine1.Format ( "%d", wHitRateChar - wHitRate);
		pCharacterHitRateGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterHitRateRedArrow->SetVisibleSingle ( FALSE );
		m_pHitRateTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wHitRate > wHitRateChar) && m_pHitRateTextCompare )
	{
		strCombine1.Format ( "%d", wHitRate - wHitRateChar);
		pCharacterHitRateRedArrow->SetVisibleSingle ( TRUE );
		pCharacterHitRateGreenArrow->SetVisibleSingle ( FALSE );
		m_pHitRateTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetAvoidRate ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const int wAvoidRateChar = GLGaeaClient::GetInstance().GetCharacter()->m_nSUM_AVOID;
	const int wAvoidRate = pNetMsg->Data.m_nSUM_AVOID;

	m_pAvoidRateText->ClearText ();
	m_pAvoidRateTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", wAvoidRate );
	if ( m_pAvoidRateText ) m_pAvoidRateText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (wAvoidRate <= wAvoidRateChar) && m_pAvoidRateTextCompare )
	{
		strCombine1.Format ( "%d", wAvoidRateChar - wAvoidRate);
		pCharacterAvoidRateGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterAvoidRateRedArrow->SetVisibleSingle ( FALSE );
		m_pAvoidRateTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (wAvoidRate > wAvoidRateChar) && m_pAvoidRateTextCompare )
	{
		strCombine1.Format ( "%d", wAvoidRate - wAvoidRateChar);
		pCharacterAvoidRateRedArrow->SetVisibleSingle ( TRUE );
		pCharacterAvoidRateGreenArrow->SetVisibleSingle ( FALSE );
		m_pAvoidRateTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetHP ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;
	
	const int nHPChar = GLGaeaClient::GetInstance().GetCharacter()->m_sHP.dwMax;
	const int nHP = pNetMsg->Data.sHP.dwMax;

	m_pHPText->ClearText ();
	m_pHPTextCompare->ClearText ();

	CString strCombine;
	strCombine.Format ( "%d", nHP );
	if ( m_pHPText ) m_pHPText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );

	CString strCombine1;
	if ( (nHP <= nHPChar) && m_pHPTextCompare )
	{
		strCombine1.Format ( "%d", nHPChar - nHP);
		pCharacterHPGreenArrow->SetVisibleSingle ( TRUE );
		pCharacterHPRedArrow->SetVisibleSingle ( FALSE );
		m_pHPTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::LIME );
	}

	if ( (nHP > nHPChar) && m_pHPTextCompare )
	{
		strCombine1.Format ( "%d", nHP - nHPChar);
		pCharacterHPRedArrow->SetVisibleSingle ( TRUE );
		pCharacterHPGreenArrow->SetVisibleSingle ( FALSE );
		m_pHPTextCompare->SetOneLineText ( strCombine1, NS_UITEXTCOLOR::RED );
	}
}

void CCharacterViewPropertiesWindow::SetMP ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;
	
	const int nMP = pNetMsg->Data.sMP.dwMax;

	CString strCombine;
	strCombine.Format ( "%d", nMP );
	if ( m_pMPText ) m_pMPText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
}

void CCharacterViewPropertiesWindow::SetSP ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	const int nSP = pNetMsg->Data.sSP.dwMax;

	CString strCombine;
	strCombine.Format ( "%d", nSP );
	if ( m_pSPText ) m_pSPText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
}

void CCharacterViewPropertiesWindow::SetFireResi ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	CString strCombine;
	strCombine.Format ( "%d", pNetMsg->Data.sSUMRESIST_SKILL.nFire );
	if ( m_pFireText ) m_pFireText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
}
void CCharacterViewPropertiesWindow::SetColdResi ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	CString strCombine;
	strCombine.Format ( "%d", pNetMsg->Data.sSUMRESIST_SKILL.nIce );
	if ( m_pColdText ) m_pColdText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
}
void CCharacterViewPropertiesWindow::SetElectricResi ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	CString strCombine;
	strCombine.Format ( "%d", pNetMsg->Data.sSUMRESIST_SKILL.nElectric );
	if ( m_pElectricText ) m_pElectricText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
}
void CCharacterViewPropertiesWindow::SetPoisonResi ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	CString strCombine;
	strCombine.Format ( "%d", pNetMsg->Data.sSUMRESIST_SKILL.nPoison );
	if ( m_pPoisonText ) m_pPoisonText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
}
void CCharacterViewPropertiesWindow::SetSpiritResi ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	CString strCombine;
	strCombine.Format ( "%d", pNetMsg->Data.sSUMRESIST_SKILL.nSpirit );
	if ( m_pSpiritText ) m_pSpiritText->SetOneLineText ( strCombine, NS_UITEXTCOLOR::SILVER );
}

void CCharacterViewPropertiesWindow::SetStaff ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

}

void CCharacterViewPropertiesWindow::SetPtoPMenu( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	GASSERT( pNetMsg->szName );

	m_szPlayerName = pNetMsg->Data.szName;
	m_dwGaeaID = pNetMsg->Data.dwGaeaID;

	CString strCombine;
	strCombine.Format ( "Currently viewing %s character info", m_szPlayerName );
	SetTitleName ( strCombine ); 

	m_bSetThisFrame = FALSE;
	m_nOverMenu = NO_ID;
}
void CCharacterViewPropertiesWindow::SetRender ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

	m_pRender->m_CharData = pNetMsg->Data;
}
void CCharacterViewPropertiesWindow::SetItemInInventory(int m_nIndex, SITEMCUSTOM& sItemCustom)
{
	m_pPageWearEx->SetItemInInventoryEx(m_nIndex, sItemCustom);
}
void  CCharacterViewPropertiesWindow::ViewpropertiseNet(NET_MSG_GENERIC* nmg )
{
	m_nOverMenu = NO_ID;

	try {
		ClearRender();
		ReSetItemAll();

		GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*)nmg;
//		GLMSG::SNETPC_REQ_ALLOW_VIEW_CHARINFO* pNetMsgView = (GLMSG::SNETPC_REQ_ALLOW_VIEW_CHARINFO*)nmg;
		SetRender(nmg);
		SetName (nmg);
		SetLevel (nmg);
		SetAcademy (nmg);
		//SetClass (nmg);
		SetPkW (nmg);
		SetPkL (nmg);
		SetMoney (nmg);
		SetMoney2 (nmg);
		SetMoney3 (nmg);
		SetClub (nmg);
		SetPow (nmg);
		SetDex (nmg);
		SetSpi (nmg);
		SetStr (nmg);
		SetSta (nmg);
		SetDamage (nmg);
		SetDefense (nmg);
		SetReqPa (nmg);
		SetReqSa (nmg);
		SetReqMa (nmg);
		SetHitRate (nmg);
		SetAvoidRate (nmg);
		SetHP (nmg);
		SetMP (nmg);
		SetSP (nmg);
		SetFireResi (nmg);
		SetColdResi (nmg);
		SetElectricResi (nmg);
		SetPoisonResi (nmg);
		SetSpiritResi (nmg);
		SetPtoPMenu (nmg);

		if (pNetMsg->Viewpropertise)
		{
			if ( !CInnerInterface::GetInstance().IsVisibleGroup(VIEW_PROPERTIES_WINDOW) ) 	
			{
				CInnerInterface::GetInstance().ShowGroupFocus(VIEW_PROPERTIES_WINDOW);
			}
		}
	}
	catch ( std::exception const &e ) {
		CDebugSet::ToLogFile ( "UNHANDLED EXCEPTION in CCharacterViewPropertiesWindow ViewpropertiseNet" );
	}
}
void CCharacterViewPropertiesWindow::ReSetItemAll()
{
	m_pPageWearEx->ReSetAllItemEx();
}
HRESULT	CCharacterViewPropertiesWindow::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	GASSERT( pd3dDevice );

	if ( !IsVisible () ) return S_OK;

	HRESULT hr = S_OK;

	//m_pClubMark->SetVisibleSingle2 ( FALSE );
	{
		hr = CUIWindowEx::Render ( pd3dDevice );
		if( FAILED ( hr ) ) return hr;
	}
	//m_pClubMark->SetVisibleSingle2 ( TRUE );

	GLCLUB& sCLUB = GLGaeaClient::GetInstance().GetCharacter ()->m_sCLUB;

	//	길드원이 아닌 경우
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

void CCharacterViewPropertiesWindow::ClearRender()
{
	if( m_pRender )
	{
		m_pRender->ClearRender();
	}
}
void CCharacterViewPropertiesWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( INVENTORY_VIEW_WINDOW );
			}
		}
		break;

	case INVENTORY_PAGEWEAR_VIEW:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pPageWearEx->GetItemIndex ();
				if ( nIndex < 0 ) return ;

				{
					SITEMCUSTOM sItemCustom = m_pPageWearEx->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}
				}

			}
		}
		break;
		case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( INVENTORY_VIEW_WINDOW );
				m_pPageWearEx->ReSetAllItemEx();
				ClearRender();
			}
		}
		break;
/////////////// Help Button ////////////////////////////////
	case VIEWCHARACTER_WHISPER_BUTTON:
		{
			NET_MSG_GENERIC* nmg;
			GLMSG::SNET_VIEW_PROPERTIES_FB* pNetMsg = (GLMSG::SNET_VIEW_PROPERTIES_FB*) nmg;

			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( m_nOverMenu != ControlID )
				{	
				}
				m_nOverMenu = ControlID;

				if ( dwMsg & UIMSG_LB_UP )
				{
					CInnerInterface::GetInstance().GetChat ()->BEGIN_PRIVATE_CHAT ( m_szPlayerName );
					CInnerInterface::GetInstance().ADD_FRIEND_NAME_TO_EDITBOX ( m_szPlayerName );
				}
			}
		}
		break;

	case VIEWCHARACTER_PARTY_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( m_nOverMenu != ControlID )
				{
				}
				m_nOverMenu = ControlID;

				if ( dwMsg & UIMSG_LB_UP )
				{			
					CString strTemp = CInnerInterface::GetInstance().MakeString ( ID2GAMEINTEXT("PARTY_QUESTION"), m_szPlayerName.GetString() );
					DoPartyModal ( strTemp, MODAL_PARTY_REQ );
				}
			}
		}
		break;
		
	case VIEWCHARACTER_FRIEND_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( m_nOverMenu != ControlID )
				{
				}
				m_nOverMenu = ControlID;

				if ( dwMsg & UIMSG_LB_UP )
				{
					CInnerInterface::GetInstance().ADD_FRIEND ( m_szPlayerName );
				}
			}
		}
		break;
/////////////// Help Button ////////////////////////////////
	case	VIEWCHARACTERHELP_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( ID2GAMEINTEXT("VIEWCHARACTER_HELP_BUTTON_MESSAGE"),  NS_UITEXTCOLOR::AQUA );				
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
			}
		}
		break;	
////////////////////////////////////////////////////////////////////////////
	}
}