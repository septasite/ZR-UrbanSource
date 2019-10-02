#include "StdAfx.h"
#include "./CharacterWindowChar.h"

#include "../EngineUiLib/GUInterface/BasicTextBox.h"
#include "../EngineUiLib/GUInterface/BasicButton.h"
#include "../EngineUiLib/GUInterface/BasicButtonRadio.h"
#include "../EngineLib/DxCommon/d3dfont.h"
#include "../UITextControl.h"
#include "../GameTextControl.h"
#include "../RanClientLib/G-Logic/GLGaeaClient.h"

#include "../InnerInterface.h"
#include "../ModalCallerID.h"
#include "../ModalWindow.h"

#include "../BasicLineBox.h"

#include "CharacterWindowCharStat.h"
#include "CharacterWindowCharWear.h"
#include "CharacterWindowCharWearEx.h"
#include "CharacterWindowCharRender.h"
#include "DxGlobalStage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterWindowChar::CCharacterWindowChar () :
	m_pStatRegion ( NULL )
	, m_pCharWear ( NULL )
	, m_pCharWearEx ( NULL )
	, m_pNameText ( NULL )
	, m_pClubText ( NULL )
	, m_pTitleText ( NULL )
	, m_pAcademy ( NULL )
	, m_pLifeP ( NULL )
	, m_pContP ( NULL )
	, m_pPremiumText ( NULL )
	, m_pHelp ( NULL )
	, m_pAbility( NULL )
	, m_pRender( NULL )
	, m_pPK( NULL )
{
}

CCharacterWindowChar::~CCharacterWindowChar ()
{
}


CBasicTextBox* CCharacterWindowChar::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}

CUIControl*	CCharacterWindowChar::CreateControl ( const char* szControl, const UIGUID& cID )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, UI_FLAG_DEFAULT, cID );
	RegisterControl ( pControl );
	return pControl;
}

CBasicButton* CCharacterWindowChar::CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID, WORD wFlipType )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, wFlipType );
	RegisterControl ( pButton );
	return pButton;
}

void CCharacterWindowChar::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, _DEFAULT_FONT_SHADOW_FLAG );
	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );

	const int nAlignLeft = TEXT_ALIGN_LEFT;
	const int nAlignCenter = TEXT_ALIGN_CENTER_X;	
	const DWORD& dwSilver = NS_UITEXTCOLOR::SILVER;

	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CHARACTER_WINDOW_SCHOOL_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CHARACTER_WINDOW_EQUIP_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CHARACTER_WINDOW_TITLE_NAME_REGION" );
	RegisterControl ( pBasicLineBox );

	CBasicTextBox* pTextBox = NULL;
	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_BRIGHT_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 5) );
	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_ACTIVITY_POINT_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 2) );
	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_CONTRIBUTION_POINT_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 7) );
	pTextBox = CreateStaticControl ( "CHARACTER_WINDOW_PK_TEXT", pFont, nAlignLeft );
	pTextBox->AddText ( ID2GAMEWORD("CHARACTER_SOCIAL_STATIC", 13) );

	m_pAcademy = CreateStaticControl ( "CHARACTER_WINDOW_ACADEMY_DEPARTMENT_TEXT", pFont, nAlignLeft );
	m_pLifeP = CreateStaticControl ( "CHARACTER_WINDOW_ACTIVITY_POINT_VALUE", pFont, nAlignLeft );
	m_pContP = CreateStaticControl ( "CHARACTER_WINDOW_CONTRIBUTION_POINT_VALUE", pFont, nAlignLeft );
	m_pPremiumText = CreateStaticControl ( "CHARACTER_WINDOW_CHECK_TEXT", pFont, nAlignLeft );
	m_pPK = CreateStaticControl ( "CHARACTER_WINDOW_PK_VALUE", pFont, nAlignLeft );

	m_pBrightFrame = CreateControl ( "CHARACTER_WINDOW_BRIGHTBAR" );		
	m_pBrightSlider = CreateControl ( "CHARACTER_WINDOW_BRIGHTBAR_THUMB" , CHARACTER_ACADEMY_BRIGHTBAR );

	m_pHelp = new CBasicButton;
	m_pHelp->CreateSub ( this, "CHARACTER_WINDOW_ACADEMY_QUESTION_BUTTON" , UI_FLAG_DEFAULT, CHARACTER_ACADEMY_HELP );
	m_pHelp->CreateFlip ( "CHARACTER_WINDOW_ACADEMY_QUESTION_BUTTON_OVER", CBasicButton::MOUSEIN_FLIP );
	m_pHelp->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pHelp );

	m_pStatRegion = new CCharacterWindowCharStat;
	m_pStatRegion->CreateSub ( this, "CHARACTER_WINDOW_STAT_REGION", UI_FLAG_YSIZE, CHARACTER_STATS );
	m_pStatRegion->CreateSubControl ();
	RegisterControl ( m_pStatRegion );

	m_pRender = new CCharacterWindowCharRender;
	m_pRender->CreateSub ( this, "CHARACTER_WINDOW_CHARACTER_MESHRENDER" );
	m_pRender->CreateSubControl ();
	RegisterControl ( m_pRender );

	if( nClassType == GLCI_EXTREME_W || nClassType == GLCI_EXTREME_M )
	{
		m_pCharWearEx = new CCharacterWindowCharWearEx;
		m_pCharWearEx->CreateSub ( this, "CHARACTER_WINDOW_WEAR_WINDOW", UI_FLAG_YSIZE, CHARACTER_WEAR_EX );
		m_pCharWearEx->CreateSubControl ();
		RegisterControl ( m_pCharWearEx );
	}else{
		m_pCharWear = new CCharacterWindowCharWear;
		m_pCharWear->CreateSub ( this, "CHARACTER_WINDOW_WEAR_WINDOW", UI_FLAG_YSIZE, CHARACTER_WEAR );
		m_pCharWear->CreateSubControl ();
		RegisterControl ( m_pCharWear );
	}

	m_pNameText = CreateStaticControl ( "CHARACTER_WINDOW_CHARACTER_NAME_TEXT", pFont, nAlignCenter );
	m_pClubText = CreateStaticControl ( "CHARACTER_WINDOW_CLUB_NAME_TEXT", pFont, nAlignCenter );
	m_pTitleText = CreateStaticControl ( "CHARACTER_WINDOW_TITLE_NAME_TEXT", pFont, nAlignCenter );
	
	m_pAbility = new CBasicButtonRadio;
	m_pAbility->CreateSub ( this, "CHARACTER_WINDOW_STAT_RADIO_BUTTON" );
	m_pAbility->CreateRadioWithText ( pFont, CBasicButtonRadio::SIZE_TEXT_50, nAlignLeft );
	m_pAbility->SetVisibleSingle ( TRUE );
	m_pAbility->SetFlip( TRUE );
	m_pAbility->SetOneLineText( ID2GAMEINTEXT("CHARACTER_WINDOW_STAT" ), dwSilver );
	RegisterControl ( m_pAbility );
}

void CCharacterWindowChar::SetData ( const GLCHARLOGIC& sCharData )
{
	m_pAcademy->ClearText();
	m_pLifeP->ClearText();
	m_pContP->ClearText();
	m_pNameText->ClearText();
	m_pPK->ClearText();

	if ( m_pNameText )
	{
		CString strTemp;
		strTemp.Format("[ID:%d] [Name:%s]",sCharData.m_dwCharID,sCharData.m_szName);
		m_pNameText->SetOneLineText ( strTemp.GetString() , NS_UITEXTCOLOR::WHITE);
	}

	CString strCombine;
	strCombine.Format ( "%s,%s", GLCONST_CHAR::strSCHOOLNAME[sCharData.m_wSchool].c_str() , COMMENT::CHARCLASS[CharClassToIndex( sCharData.m_emClass )].c_str() );
	m_pAcademy->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );

	strCombine.Format ( "%d", sCharData.m_nLiving );
	m_pLifeP->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITE );

	strCombine.Format ( "%d", sCharData.m_lnContribP );
	m_pContP->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITE );

	strCombine.Format ( "%d", sCharData.m_wPK );
	m_pPK->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITE );
	
	{
		const int nMIN = -100;
		const int nMAX = 100;
		const int nRANGE = nMAX - nMIN;
		int nPercent = sCharData.GETBRIGHTPER ();
		nPercent = -(nPercent);
		if ( nPercent < nMIN ) nPercent = nMIN;
		if ( nPercent > nMAX ) nPercent = nMAX;
		nPercent += nMAX;
		float fPercent = static_cast<float>(nPercent) / static_cast<float>(nRANGE);
		const UIRECT& rcFramePos = m_pBrightFrame->GetGlobalPos ();
		const UIRECT& rcThumbPos = m_pBrightSlider->GetGlobalPos ();
		float fMOVE = (rcFramePos.sizeX - rcThumbPos.sizeX) * fPercent;
		float fLeft = rcFramePos.left + fMOVE;
		m_pBrightSlider->SetGlobalPos ( D3DXVECTOR2 ( fLeft, rcThumbPos.top ) );
	}

	{
		GLCLUB& sCLUB = GLGaeaClient::GetInstance().GetCharacter ()->m_sCLUB;
		CString strTemp;
		if ( sCLUB.IsMember( sCharData.m_dwCharID ) )
		{
			strTemp.Format("[ID:%d][Name:%s]",sCLUB.m_dwID,sCLUB.m_szName);
		}else{
			strTemp.Format("[%s]",ID2GAMEINTEXT("CHARACTER_WINDOW_EMPTY_CLUB") );
		}
		if ( m_pClubText )	m_pClubText->SetOneLineText ( strTemp.GetString(), NS_UITEXTCOLOR::YELLOW );
	}

	{
		if ( m_pPremiumText )
		{
			bool bPREMIUM = GLGaeaClient::GetInstance().GetCharacter()->m_bPREMIUM;
			if ( bPREMIUM )
			{
				__time64_t tPREMIUM = GLGaeaClient::GetInstance().GetCharacter()->m_tPREMIUM;
				CTime cTime ( tPREMIUM );
				CString strExpireDate;
				strExpireDate.Format ( "Inquiry %02d/%02d/%02d", cTime.GetYear()%2000, cTime.GetMonth(), cTime.GetDay () );
				m_pPremiumText->SetOneLineText ( strExpireDate, NS_UITEXTCOLOR::WHITE );
			}else{
				m_pPremiumText->SetOneLineText ( "Inquiry", NS_UITEXTCOLOR::WHITE );
			}
		}
	}
}

void CCharacterWindowChar::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case CHARACTER_ACADEMY_BRIGHTBAR:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter ();

				CString strTemp;				
				strTemp.Format ( "%d", pCharacter->m_nBright );

				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strTemp, NS_UITEXTCOLOR::WHITE );
			}
		}
		break;

	case CHARACTER_ACADEMY_HELP:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CString strTemp;
				strTemp.Format( "%s %s %s %s %s %s", 
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_1_TEXT" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_1" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_2_TEXT" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_2" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_3_TEXT" ),
					ID2GAMEINTEXT( "CHARACTER_WINDOW_ACADEMY_QUESTION_SENTENCE_3" ) );
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO_SPLIT( strTemp.GetString(), NS_UITEXTCOLOR::DARKLBUE );
			}
		}
		break;

	case CHARACTER_WEAR:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pCharWear->GetItemIndex ();
				if ( nIndex < 0 ) return ;		

				SITEMCUSTOM sItemCustom = m_pCharWear->GetItem ( nIndex );
				if ( sItemCustom.sNativeID != NATIVEID_NULL () )
				{
					CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );

					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( sItemCustom.GETOptVALUE(EMR_OPT_ATTACK_VOL) >= 101 )
					{
						return;
					}

					if ( sItemCustom.GETOptVALUE(EMR_OPT_DEFENSE_VOL) >= 101 )
					{
						return;
					}
					if ( sItemCustom.GETOptVALUE(EMR_OPT_MELEE) >= 101 )
					{
						return;
					}
					if ( sItemCustom.GETOptVALUE(EMR_OPT_SHOOTING) >= 101 )
					{
						return;
					}
					if ( sItemCustom.GETOptVALUE(EMR_OPT_VITALITY) >= 151 )
					{
						return;
					}
					if ( sItemCustom.GETOptVALUE(EMR_OPT_DAMAGE) >= 10.01 )
					{
						return;
					}
					if ( sItemCustom.GETOptVALUE(EMR_OPT_AVOID_VOL) >= 31 )
					{
						return;
					}
					if ( sItemCustom.GETOptVALUE(EMR_OPT_HIT_VOL) >= 31 )
					{
						return;
					}
					if ( sItemCustom.GETOptVALUE(EMR_OPT_RESIST) >= 21 )
					{
						return;
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pCharWear->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}

				if ( dwMsg & UIMSG_RB_UP )
				{
					EMSLOT emSlot = m_pCharWear->GetItemSlot ();

					BOOL bHOLDITEM = GLGaeaClient::GetInstance().GetCharacter()->VALID_HOLD_ITEM();
					if ( bHOLDITEM )
					{	
						//GLGaeaClient::GetInstance().GetCharacter()->ReqSlotUseItem ( emSlot );
					}else{
						//GLGaeaClient::GetInstance().GetCharacter()->ReqSlotToInven ( emSlot );
					}	
				}
			}
		}
		break;

	case CHARACTER_WEAR_EX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pCharWearEx->GetItemIndex ();
				if ( nIndex < 0 ) return ;	

				SITEMCUSTOM sItemCustom = m_pCharWearEx->GetItem ( nIndex );
				if ( sItemCustom.sNativeID != NATIVEID_NULL () )
				{
					CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );

					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						if ( dwMsg & UIMSG_LB_UP )
						{
							CInnerInterface::GetInstance().PreviewItem( sItemCustom );
							return;
						}
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pCharWearEx->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}

				if ( dwMsg & UIMSG_RB_UP )
				{
					EMSLOT emSlot = m_pCharWearEx->GetItemSlot ();
					//GLGaeaClient::GetInstance().GetCharacter()->ReqSlotToInven ( emSlot );
				}
			}
		}
		break;
	};
}

void CCharacterWindowChar::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();	
	SetData ( sCharData );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCharacterWindowChar::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		if( m_pCharWearEx )
		{
			if( GLGaeaClient::GetInstance().GetCharacter()->IsUseArmSub() )
			{
				m_pCharWearEx->SetTabButton( FALSE );
			}else{
				m_pCharWearEx->SetTabButton( TRUE );
			}
		}
	}else{
		ClearRender();
	}
}

void CCharacterWindowChar::SetArmSwapTabButton( BOOL bArmSub )
{
	if( m_pCharWearEx )
	{
		m_pCharWearEx->SetTabButton( bArmSub );
	}
}

void CCharacterWindowChar::ClearRender()
{
	if( m_pRender )
	{
		m_pRender->ClearRender();
	}
}