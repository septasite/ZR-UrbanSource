#include "StdAfx.h"
#include "./CharacterWindowVehicle.h"

#include "../EngineUiLib/GUInterface/BasicTextBox.h"
#include "../EngineUiLib/GUInterface/BasicButton.h"
#include "../EngineUiLib/GUInterface/BasicButtonRadio.h"
#include "../EngineLib/DxCommon/d3dfont.h"
#include "../UITextControl.h"
#include "../GameTextControl.h"
#include "../InnerInterface.h"
#include "../BasicLineBox.h"
#include "../ItemImage.h"
#include "../ItemMove.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "ItemImageVehicle.h"
#include "CharacterWindowVehicleRender.h"
#include "RANPARAM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterWindowVehicle::CCharacterWindowVehicle () :
	m_pMouseOver( NULL)
	, m_pVehicleName( NULL )
	, m_pVehicleSpeed( NULL )
	, m_pBatteryText( NULL )
	, m_pBoostText ( NULL )
	, m_nBatteryBack(-1)
	, bOWnVehicle( FALSE )
	, m_pActiveVehicle( NULL )
	, m_pListPrev( NULL )
	, m_pListNext( NULL )
	, m_pListNum( NULL )
	, m_pListPointShopPrev( NULL )
	, m_pListPointShopNext( NULL )
	, m_pListPointShopNum( NULL )
	, nCurrentPage(1)
	, nCurrentPageShop(1)
	, m_pBoardButton( NULL )
	, m_pBikeButton( NULL )
	, m_pPartsButton( NULL )
	, m_pBatteryButton( NULL )
	, m_pBoostIconOn( NULL )
	, m_pBoostIconOff( NULL )
	, m_pRender( NULL )
	, m_pMoveAnim( NULL )
	, m_pMoveAnimText( NULL )
{
	SecureZeroMemory( m_pSlotDisplay, sizeof(m_pSlotDisplay) );
	SecureZeroMemory( m_pSlotImage, sizeof(m_pSlotImage) );
	SecureZeroMemory( m_pVehicleList, sizeof(m_pVehicleList) );
	SecureZeroMemory( m_pVehiclePointShopList, sizeof(m_pVehiclePointShopList) );

	m_vecID.clear();
}

CCharacterWindowVehicle::~CCharacterWindowVehicle ()
{
}

CBasicTextBox* CCharacterWindowVehicle::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}

CUIControl*	CCharacterWindowVehicle::CreateControl ( const char* szControl, const UIGUID& cID )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, UI_FLAG_DEFAULT, cID );
	RegisterControl ( pControl );
	return pControl;
}

CBasicButton* CCharacterWindowVehicle::CreateFlipButton ( char* szButton, char* szButtonFlip, char* szButtonMouseOver, UIGUID ControlID, WORD wFlipType )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, wFlipType );
	pButton->CreateMouseOver ( szButtonMouseOver );
	RegisterControl ( pButton );
	return pButton;
}

CItemImageVehicle*	CCharacterWindowVehicle::CreateItemImageVehicle ( const char* szControl, UIGUID ControlID )
{
	CItemImageVehicle* pItemImage = new CItemImageVehicle;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );
	return pItemImage;
}

CBasicTextBox*	CCharacterWindowVehicle::CreateTextBox ( char* szKeyword, CD3DFontPar* pFont )
{
	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, szKeyword );
	pTextBox->SetFont ( pFont );
	RegisterControl ( pTextBox );
	return pTextBox;
}

CBasicTextBox*	CCharacterWindowVehicle::CreateTextBoxCenter ( char* szKeyword, CD3DFontPar* pFont )
{
	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, szKeyword );
	pTextBox->SetFont ( pFont );
	pTextBox->SetTextAlign( TEXT_ALIGN_CENTER_X );
	RegisterControl ( pTextBox );
	return pTextBox;
}

CBasicButtonRadio*	CCharacterWindowVehicle::CreateRadioButton( char* szKeyword, CD3DFontPar* pFont, int nTextSize, UIGUID ControlID )
{
	CBasicButtonRadio* pButton = new CBasicButtonRadio;
	pButton->CreateSub ( this, szKeyword, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateRadioWithText ( pFont, nTextSize, TEXT_ALIGN_LEFT );
	RegisterControl ( pButton );
	return pButton;
}

void CCharacterWindowVehicle::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, _DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, FALSE );

	m_pBoostIconOff = CreateControl( "CHARACTER_WINDOW_VEHICLE_BOOST_ICON", BOOSTER_ICON_OFF );

	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList ( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList ( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_PAGE_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList ( "CHARACTER_WINDOW_VEHICLE_SETTING_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList ( "CHARACTER_WINDOW_VEHICLE_BUY_TYPE_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList ( "CHARACTER_WINDOW_VEHICLE_BUY_LIST_REGION" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList ( "CHARACTER_WINDOW_VEHICLE_BUY_PAGE_REGION" );
	RegisterControl ( pBasicLineBox );

	CreateControl( "CHARACTER_WINDOW_VEHICLE_MESHRENDER_LINE_REGION" );

	//vehicle setting
	CString strVehicleSlot[SLOT_IMAGE_SIZE] = 
	{
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT1",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT2",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT3",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT4",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT5",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT6",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT7",
	};

	CString strVehicleSlotOver[SLOT_IMAGE_SIZE] = 
	{
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT1_OVER",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT2_OVER",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT3_OVER",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT4_OVER",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT5_OVER",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT6_OVER",
		"CHARACTER_WINDOW_VEHICLE_PARTS_SLOT7_OVER",
	};

	for ( int i = 0; i < SLOT_IMAGE_SIZE; i++ )
	{
		m_pSlotImage[i] = CreateItemImageVehicle( strVehicleSlot[i].GetString(), SLOT_SKIN_IMAGE_TYPE0 + i );
		m_pSlotDisplay[i] = CreateControl( strVehicleSlotOver[i].GetString() );
		m_pSlotDisplay[i]->SetVisibleSingle( FALSE );
	}

	m_pRender = new CCharacterWindowVehicleRender;
	m_pRender->CreateSub ( this, "CHARACTER_WINDOW_VEHICLE_MESHRENDER_REGION" );
	m_pRender->CreateSubControl ();
	RegisterControl ( m_pRender );

	m_pMouseOver = CreateControl( "ITEM_MOUSE_OVER" );
	m_pMouseOver->SetVisibleSingle( FALSE );

	m_pVehicleName = CreateTextBox ( "CHARACTER_WINDOW_VEHICLE_NAME", pFont9 );
	m_pVehicleSpeed = CreateTextBox ( "CHARACTER_WINDOW_VEHICLE_PARTS_SPEED_TEXT", pFont9 );
	m_pBatteryText = CreateTextBox ( "CHARACTER_WINDOW_VEHICLE_BATTERY_TEXT", pFont9 );
	m_pBoostText = CreateTextBox ( "CHARACTER_WINDOW_VEHICLE_BOOST_TEXT", pFont9 );
	m_pBoostText->SetTextAlign ( TEXT_ALIGN_RIGHT );
	
	//vehicle list
	m_pVehicleList[0] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_SLOT1", SLOT_VEHICLE_LIST0 );
	m_pVehicleList[1] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_SLOT2", SLOT_VEHICLE_LIST1 );
	m_pVehicleList[2] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_SLOT3", SLOT_VEHICLE_LIST2 );
	m_pVehicleList[3] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_SLOT4", SLOT_VEHICLE_LIST3 );
	m_pVehicleList[4] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_SLOT5", SLOT_VEHICLE_LIST4 );
	m_pVehicleList[5] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_SLOT6", SLOT_VEHICLE_LIST5 );
	m_pVehicleList[6] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_LIST_SLOT7", SLOT_VEHICLE_LIST6 );
	m_pActiveVehicle = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_MY_VEHICLE_SLOT", SLOT_VEHICLE_ACTIVE );
	m_pListPrev = CreateFlipButton ( "CHARACTER_WINDOW_VEHICLE_MY_LIST_PRE_PAGE_BUTTON_NORMAL", "CHARACTER_WINDOW_PRE_PAGE_BUTTON_CLICK_TEXTUREINFO", "CHARACTER_WINDOW_PRE_PAGE_BUTTON_OVER_TEXTUREINFO", LIST_BUTTON_PREV, CBasicButton::CLICK_FLIP );
	m_pListNext = CreateFlipButton ( "CHARACTER_WINDOW_VEHICLE_MY_LIST_NEXT_PAGE_BUTTON_NORMAL", "CHARACTER_WINDOW_NEXT_PAGE_BUTTON_CLICK_TEXTUREINFO", "CHARACTER_WINDOW_NEXT_PAGE_BUTTON_OVER_TEXTUREINFO", LIST_BUTTON_NEXT, CBasicButton::CLICK_FLIP );
	m_pListNum = CreateTextBoxCenter ( "CHARACTER_WINDOW_VEHICLE_MY_LIST_PAGE_NUMBER", pFont9 );	

	m_pVehiclePointShopList[0] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT1", SLOT_VEHICLE_POINTSHOP_LIST0 );
	m_pVehiclePointShopList[1] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT2", SLOT_VEHICLE_POINTSHOP_LIST1 );
	m_pVehiclePointShopList[2] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT3", SLOT_VEHICLE_POINTSHOP_LIST2 );
	m_pVehiclePointShopList[3] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT4", SLOT_VEHICLE_POINTSHOP_LIST3 );
	m_pVehiclePointShopList[4] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT5", SLOT_VEHICLE_POINTSHOP_LIST4 );
	m_pVehiclePointShopList[5] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT6", SLOT_VEHICLE_POINTSHOP_LIST5 );
	m_pVehiclePointShopList[6] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT7", SLOT_VEHICLE_POINTSHOP_LIST6 );
	m_pVehiclePointShopList[7] = CreateItemImageVehicle( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_VEHICLE_LIST_SLOT8", SLOT_VEHICLE_POINTSHOP_LIST7 );

	m_pListPointShopPrev = CreateFlipButton ( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_LIST_PRE_PAGE_BUTTON_NORMAL", "CHARACTER_WINDOW_PRE_PAGE_BUTTON_CLICK_TEXTUREINFO", "CHARACTER_WINDOW_PRE_PAGE_BUTTON_OVER_TEXTUREINFO", LIST_POINTSHOP_BUTTON_PREV, CBasicButton::CLICK_FLIP );
	m_pListPointShopNext = CreateFlipButton ( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_LIST_NEXT_PAGE_BUTTON_NORMAL", "CHARACTER_WINDOW_NEXT_PAGE_BUTTON_CLICK_TEXTUREINFO", "CHARACTER_WINDOW_NEXT_PAGE_BUTTON_OVER_TEXTUREINFO", LIST_POINTSHOP_BUTTON_NEXT, CBasicButton::CLICK_FLIP );
	m_pListPointShopNum = CreateTextBoxCenter ( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_LIST_PAGE_NUMBER", pFont9 );

	m_pBoardButton = CreateRadioButton( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_BOARD_RADIO_BUTTON", pFont8, CBasicButtonRadio::SIZE_TEXT_70, LIST_POINTSHOP_BUTTON_BOARD );
	m_pBikeButton = CreateRadioButton( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_BIKE_RADIO_BUTTON", pFont8, CBasicButtonRadio::SIZE_TEXT_70, LIST_POINTSHOP_BUTTON_BIKE );
	m_pPartsButton = CreateRadioButton( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_PARTS_RADIO_BUTTON", pFont8, CBasicButtonRadio::SIZE_TEXT_70, LIST_POINTSHOP_BUTTON_PARTS );
	m_pBatteryButton = CreateRadioButton( "CHARACTER_WINDOW_VEHICLE_POINT_SHOP_BATTERY_RADIO_BUTTON", pFont8, CBasicButtonRadio::SIZE_TEXT_70, LIST_POINTSHOP_BUTTON_BATTERY );

	m_pBoardButton->SetOneLineText( ID2GAMEWORD( "CHARACTER_WINDOW_VEHICLE_POINTSHOP_BUTTON_TEXT", 0 ) );
	m_pBikeButton->SetOneLineText( ID2GAMEWORD( "CHARACTER_WINDOW_VEHICLE_POINTSHOP_BUTTON_TEXT", 1 ) );
	m_pPartsButton->SetOneLineText( ID2GAMEWORD( "CHARACTER_WINDOW_VEHICLE_POINTSHOP_BUTTON_TEXT", 2 ) );
	m_pBatteryButton->SetOneLineText( ID2GAMEWORD( "CHARACTER_WINDOW_VEHICLE_POINTSHOP_BUTTON_TEXT", 3 ) );

	m_pBoostIconOn = CreateControl( "CHARACTER_WINDOW_VEHICLE_BOOST_ICON", BOOSTER_ICON_ON );

	m_pMoveAnim = new CBasicButton;
	m_pMoveAnim->CreateSub ( this, "CHARACTER_WINDOW_VEHICLE_ANIMATION_CHECKBOX", UI_FLAG_DEFAULT, MOVE_CHECKBOX );
	m_pMoveAnim->CreateFlip ( "CHARACTER_WINDOW_VEHICLE_ANIMATION_CHECKBOX_ON", CBasicButton::RADIO_FLIP );
	m_pMoveAnim->SetControlNameEx ( "CHARACTER_WINDOW_VEHICLE_ANIMATION_CHECKBOX" );
	RegisterControl ( m_pMoveAnim );
	m_pMoveAnim->SetFlip( RANPARAM::bVehicleRenderMove );

	m_pMoveAnimText = CreateTextBox ( "CHARACTER_WINDOW_VEHICLE_ANIMATION_CHECKBOX_TEXT", pFont9 );
	m_pMoveAnimText->SetText( ID2GAMEINTEXT( "CHARACTER_WINDOW_VEHICLE_MOVING_ANIMATION" ) );
}

EMSUIT CCharacterWindowVehicle::IMAGE2EMSLOT ( UIGUID ControlID )
{
	switch ( ControlID )
	{	
	case SLOT_SKIN_IMAGE_TYPE0: return SUIT_VEHICLE_SKIN;
	case SLOT_PARTS_IMAGE_TYPE0: return SUIT_VEHICLE_PARTS_A;
	case SLOT_PARTS_IMAGE_TYPE1: return SUIT_VEHICLE_PARTS_B;
	case SLOT_PARTS_IMAGE_TYPE2: return SUIT_VEHICLE_PARTS_C;
	case SLOT_PARTS_IMAGE_TYPE3: return SUIT_VEHICLE_PARTS_D;
	case SLOT_PARTS_IMAGE_TYPE4: return SUIT_VEHICLE_PARTS_E;
	case SLOT_PARTS_IMAGE_TYPE5: return SUIT_VEHICLE_PARTS_F;
	}

	GASSERT ( 0 && "CVehicleWindow::IMAGE2EMSLOT(), 범위를 벗어납니다." );
	return SUIT_NSIZE;
}

void CCharacterWindowVehicle::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case SLOT_VEHICLE_ACTIVE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if( m_pActiveVehicle->GetItem().sNativeID != NATIVEID_NULL () )
				{
					if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
					{
						bOWnVehicle = TRUE;
					}

					CInnerInterface::GetInstance().SHOW_ITEM_INFO ( m_pActiveVehicle->GetItem(), FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
				}	
			}
		}break;

	case SLOT_VEHICLE_LIST0:
	case SLOT_VEHICLE_LIST1:
	case SLOT_VEHICLE_LIST2:
	case SLOT_VEHICLE_LIST3:
	case SLOT_VEHICLE_LIST4:
	case SLOT_VEHICLE_LIST5:
	case SLOT_VEHICLE_LIST6:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nSelect = ControlID - SLOT_VEHICLE_LIST0;

				if( m_pVehicleList[nSelect]->GetItem().sNativeID != NATIVEID_NULL () )
				{
					if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
					{
						bOWnVehicle = FALSE;
						LoadListVehicle( nSelect );
					}

					CInnerInterface::GetInstance().SHOW_ITEM_INFO ( m_pVehicleList[nSelect]->GetItem(), FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
				}	
			}
		}break;

	case SLOT_SKIN_IMAGE_TYPE0:
	case SLOT_PARTS_IMAGE_TYPE0:
	case SLOT_PARTS_IMAGE_TYPE1:
	case SLOT_PARTS_IMAGE_TYPE2:
	case SLOT_PARTS_IMAGE_TYPE3:
	case SLOT_PARTS_IMAGE_TYPE4:
	case SLOT_PARTS_IMAGE_TYPE5:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				int nIndex = ControlID - SLOT_SKIN_IMAGE_TYPE0;

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove가 널입니다." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pSlotImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_VEHICLE_NEWWEARSLOT | UIMSG_TOTOPPARENT );
				}				

				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pSlotImage[nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pSlotImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}

				if ( dwMsg & UIMSG_LB_UP && bOWnVehicle )
				{
					GLGaeaClient::GetInstance().GetCharacter()->ReqVehicleChangeAccessory( IMAGE2EMSLOT(ControlID) );
				}

				if ( dwMsg & UIMSG_RB_UP && bOWnVehicle )
				{
					GLGaeaClient::GetInstance().GetCharacter()->ReqVehicleRemoveSlotItem( IMAGE2EMSLOT(ControlID) );
				}

				if( m_pSlotImage[nIndex]->GetItem().sNativeID != NATIVEID_NULL () )
				{
					CInnerInterface::GetInstance().SHOW_ITEM_INFO ( m_pSlotImage[nIndex]->GetItem(), FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
				}
			}
		}
		break;

	case LIST_BUTTON_PREV:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
				{
					nCurrentPage --;
					if ( nCurrentPage < 1 )
						nCurrentPage = 1;
					LoadVehicleList( nCurrentPage );
				}
			}
		}break;

	case LIST_BUTTON_NEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
				{
					nCurrentPage ++;
					LoadVehicleList( nCurrentPage );
				}
			}
		}break;

	case LIST_POINTSHOP_BUTTON_PREV:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
				{
					nCurrentPageShop --;
					if ( nCurrentPageShop < 1 )
						nCurrentPageShop = 1;
					LoadListPointShop( nCurrentPageShop );
				}
			}
		}break;

	case LIST_POINTSHOP_BUTTON_NEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
				{
					nCurrentPageShop ++;
					LoadListPointShop( nCurrentPageShop );
				}
			}
		}break;

	case LIST_POINTSHOP_BUTTON_BOARD:
	case LIST_POINTSHOP_BUTTON_BIKE:
	case LIST_POINTSHOP_BUTTON_PARTS:
	case LIST_POINTSHOP_BUTTON_BATTERY:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )	
				{
					int nIndex = ControlID - LIST_POINTSHOP_BUTTON_BOARD;
					ChangePointShopCategory( nIndex );
				}
			}
		}break;

	case BOOSTER_ICON_ON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEINTEXT( "BIKE_BOOST_EXPLAIN_OVER_ON" ), NS_UITEXTCOLOR::DARKLBUE );
			}
		}break;
	case BOOSTER_ICON_OFF:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEINTEXT( "BIKE_BOOST_EXPLAIN_OVER_OFF" ), NS_UITEXTCOLOR::DARKLBUE );
			}
		}break;

	case MOVE_CHECKBOX:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				RANPARAM::bVehicleRenderMove = !RANPARAM::bVehicleRenderMove;
				m_pMoveAnim->SetFlip( RANPARAM::bVehicleRenderMove );
			}
		}break;
	}
}

void CCharacterWindowVehicle::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_pMouseOver->SetVisibleSingle ( FALSE );

	if ( bOWnVehicle )
		LoadOwnVehicle();
}

void CCharacterWindowVehicle::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		InitVehicle();
	}else{
		ClearRender();
	}
}

void CCharacterWindowVehicle::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_pSlotImage[nIndex]->SetItem ( ref_sItemCustom );
}

void CCharacterWindowVehicle::UnLoadItem ( int nIndex )
{
	m_pSlotImage[nIndex]->ResetItem ();
}

void CCharacterWindowVehicle::LoadActiveVehicle()
{
	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pChar ) return;

	SITEMCUSTOM& sItemCustom = pChar->m_PutOnItems[SLOT_VEHICLE];
	if ( sItemCustom.sNativeID == NATIVEID_NULL() ) return;

	SITEM* pMyVehicleItem = GLItemMan::GetInstance().GetItem( sItemCustom.sNativeID );
	if ( !pMyVehicleItem ) return;

	m_pActiveVehicle->SetItem ( sItemCustom );

	bOWnVehicle = TRUE;
}

void CCharacterWindowVehicle::UnLoadActiveVehicle()
{
	m_pActiveVehicle->ResetItem ();
}

void CCharacterWindowVehicle::LoadVehicleList( int nPage )
{
	UnLoadVehicleList ();

	int nEnd = nPage * SLOT_VEHICLE_LIST;
	int nStart = nEnd - SLOT_VEHICLE_LIST;

	int nSlot = 0;
	for ( int i = nStart; i < nEnd; ++ i )
	{
		if ( i >= m_vecID.size() )	continue;
		m_pVehicleList[nSlot]->SetItem ( m_vecID[i] );
		nSlot ++ ;
	}

	CString strText;
	strText.Format( "%d", nPage );
	m_pListNum->SetText( strText.GetString() );

	ResetVehicleInfo();
}

void CCharacterWindowVehicle::UnLoadVehicleList ()
{
	for ( int i = 0; i < SLOT_VEHICLE_LIST; i++ )
		m_pVehicleList[i]->ResetItem ();
}

void CCharacterWindowVehicle::InitVehicle()
{
	UnLoadActiveVehicle();
	UnLoadVehicleList();
	bOWnVehicle = FALSE;
	m_vecID.clear();

	GLInventory& ref_Inventory = GLGaeaClient::GetInstance().GetCharacterLogic ().m_cInventory;	
	GLInventory::CELL_MAP *pItemList = ref_Inventory.GetItemList();

	GLInventory::CELL_MAP_ITER iter = pItemList->begin();
	GLInventory::CELL_MAP_ITER iter_end = pItemList->end();

	for ( ; iter!=iter_end; ++iter )
	{
		SINVENITEM* pInvenItem = (*iter).second;
		if ( pInvenItem )
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem( pInvenItem->sItemCustom.sNativeID );
			if ( pItem && pItem->sBasicOp.emItemType == ITEM_VEHICLE )
			{
				m_vecID.push_back( pInvenItem->sItemCustom );
			}
		}
	}

	nCurrentPage = 1;
	LoadActiveVehicle();
	LoadVehicleList( nCurrentPage );

	ChangePointShopCategory( 0 );
}

void CCharacterWindowVehicle::ResetVehicleInfo()
{
	m_pVehicleName->ClearText();
	m_pVehicleSpeed->ClearText(); 
	m_pBatteryText->ClearText();
	m_pBoostText->ClearText();
	m_nBatteryBack = -1;

	for( int i=0; i<SLOT_IMAGE_SIZE; ++i )
	{
		UnLoadItem ( i );
	}

	m_pActiveVehicle->VisibleFlipImage( FALSE );

	for( int i=0; i<SLOT_VEHICLE_LIST; ++i )
	{
		m_pVehicleList[i]->VisibleFlipImage( FALSE );
	}

	if ( m_pRender )
	{
		m_pRender->bRenderVehicle = false;
	}
}

void CCharacterWindowVehicle::LoadOwnVehicle()
{
	if ( !bOWnVehicle )	return;
	ResetVehicleInfo();

	m_pActiveVehicle->VisibleFlipImage( TRUE );

	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pChar )	return;

	SITEMCUSTOM sItemSelected = m_pActiveVehicle->GetItem();
	SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemSelected.sNativeID );
	if ( !pItem )	return;

	for ( int i = 0; i < SLOT_IMAGE_SIZE; i++ )
		m_pSlotImage[i]->SetVisibleSingle ( TRUE );

	CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
	SNATIVEID sHOLD_ITEM_ID(false);
	if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

	for( int i=0; i<SLOT_IMAGE_SIZE; ++i )
	{
		SITEMCUSTOM & sItemCustomOld  = m_pSlotImage[i]->GetItem();
		SITEMCUSTOM & sItemCustom = pChar->m_sVehicle.m_PutOnItems[i];

		if ( sItemCustom != sItemCustomOld )
		{		
			if ( sItemCustom.sNativeID != NATIVEID_NULL() )
			{
				LoadItem ( i, sItemCustom );
			}else{
				UnLoadItem ( i );
			}
		}

		m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );

		if( sHOLD_ITEM_ID != NATIVEID_NULL() )
		{
			if( pChar->m_sVehicle.CheckSlotItem( sHOLD_ITEM_ID, IMAGE2EMSLOT( i + SLOT_SKIN_IMAGE_TYPE0 ) ) )
			{
				const UIRECT& rcImagePos = m_pSlotImage[i]->GetGlobalPos ();
				D3DXVECTOR2 vPos( rcImagePos.left, rcImagePos.top );
				m_pSlotDisplay[i]->SetVisibleSingle( TRUE );
			}
		}
	}

	VEHICLE_TYPE emTYPE = pItem->sVehicle.emVehicleType;

	float fVol = sItemSelected.GETMOVESPEED() + pChar->m_sVehicle.m_fSpeedVol;
	int nFull = GLGaeaClient::GetInstance().GetCharacter()->m_sVehicle.m_nFull;
	
	if ( m_pRender )
	{
		SVEHICLEITEMINFO sInfo;
		sInfo.m_emTYPE = emTYPE;
		sInfo.m_nFull = nFull;
		for( int i=0 ; i < ACCE_TYPE_SIZE ; i++ )
		{
			sInfo.m_PutOnItems[i] = pChar->m_sVehicle.m_PutOnItems[i];
		}
		
		m_pRender->RenderVehicle( pItem->sBasicOp.sNativeID, sInfo );
	}

	if ( m_pBatteryText )
	{
		if ( m_nBatteryBack != nFull )
		{
			m_nBatteryBack = nFull;
			CString strTemp;
			strTemp.Format( "%s %.2f%%",ID2GAMEWORD( "ITEM_VEHICLE_BATTERY", 0 ), nFull/10.0f );
			m_pBatteryText->SetOneLineText( strTemp, NS_UITEXTCOLOR::YELLOW );
		}
	}

	if ( m_pVehicleSpeed )
	{
		CString strTemp;
		strTemp.Format( "%s %.2f ", ID2GAMEWORD( "ITEM_ADVANCED_INFO_SPECIAL_ADD", 5 ), fVol );
		m_pVehicleSpeed->SetOneLineText( strTemp, NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pVehicleName )
	{
		CString strTemp;
		strTemp.Format( "%s %s", COMMENT::VEHICLE_TYPE[emTYPE].c_str(), pItem->GetName() );
		m_pVehicleName->SetOneLineText( strTemp, NS_UITEXTCOLOR::WHITE );
	}

	/*if ( emTYPE == VEHICLE_TYPE_BIKE || emTYPE == VEHICLE_TYPE_CAR || emTYPE == VEHICLE_TYPE_REARCAR )
	{
		if ( m_pBoostText )
		{
			std::string strBoost[2] = 
			{
				"CHARACTER_WINDOW_VEHICLE_BOOST_EMPTY",
				"CHARACTER_WINDOW_VEHICLE_BOOST_USING_EXPLAIN"
			};

			m_pBoostText->SetVisibleSingle( TRUE );
			m_pBoostText->SetOneLineText( ID2GAMEINTEXT( strBoost[bBooster].c_str() ), NS_UITEXTCOLOR::YELLOW );
		}	

		if ( m_pBoostIconOn )	m_pBoostIconOn->SetVisibleSingle( bBooster );
		if ( m_pBoostIconOff )	m_pBoostIconOff->SetVisibleSingle( !bBooster );
	}else*/{
		m_pBoostText->SetVisibleSingle( FALSE );
		m_pBoostIconOn->SetVisibleSingle( FALSE );
		m_pBoostIconOff->SetVisibleSingle( FALSE );
	}
}

void CCharacterWindowVehicle::LoadListVehicle( int nSelect )
{
	if ( bOWnVehicle )	return;
	if ( nSelect >= SLOT_VEHICLE_LIST )	return;

	ResetVehicleInfo();

	m_pVehicleList[nSelect]->VisibleFlipImage( TRUE );

	SITEMCUSTOM sItemSelected = m_pVehicleList[nSelect]->GetItem();
	SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemSelected.sNativeID );
	if ( !pItem )	return;

	DWORD dwVehicleID = sItemSelected.dwVehicleID;

	float fVol = 0;
	int nFull = 0;
	bool bBooster = false;

	VEHICLE_TYPE emTYPE = pItem->sVehicle.emVehicleType;
	
	bool bInfo = true;
	VEHICLEITEMINFO_MAP_ITER iter = GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfo.find ( dwVehicleID );
	if ( iter == GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfo.end() )
	{
		iter = GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfoTemp.find ( dwVehicleID );
		if ( iter == GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfoTemp.end() )	bInfo = false;
	}

	if ( bInfo )
	{
		SVEHICLEITEMINFO sVehicleItemInfo = (*iter).second;
		nFull = sVehicleItemInfo.m_nFull;
		fVol = sItemSelected.GETMOVESPEED();
		
		for ( int i = 0; i < SLOT_IMAGE_SIZE; i++ )
			m_pSlotImage[i]->SetVisibleSingle ( TRUE );

		for( int i=0; i<SLOT_IMAGE_SIZE; ++i )
		{
			SITEMCUSTOM & sItemCustom = sVehicleItemInfo.m_PutOnItems[i];

			if ( sItemCustom.sNativeID != NATIVEID_NULL() )
			{
				fVol += sItemCustom.GETMOVESPEED();
				LoadItem ( i, sItemCustom );
			}else{
				UnLoadItem ( i );
			}

			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );
		}

		if ( m_pRender )
		{
			m_pRender->RenderVehicle( pItem->sBasicOp.sNativeID, sVehicleItemInfo );
		}
	}

	if ( m_pBatteryText )
	{
		if ( m_nBatteryBack != nFull )
		{
			m_nBatteryBack = nFull;
			CString strTemp;
			strTemp.Format( "%s %.2f%%",ID2GAMEWORD( "ITEM_VEHICLE_BATTERY", 0 ), nFull/10.0f );
			m_pBatteryText->SetOneLineText( strTemp, NS_UITEXTCOLOR::YELLOW );
		}
	}

	if ( m_pVehicleSpeed )
	{
		CString strTemp;
		strTemp.Format( "%s %.2f ", ID2GAMEWORD( "ITEM_ADVANCED_INFO_SPECIAL_ADD", 5 ), fVol );
		m_pVehicleSpeed->SetOneLineText( strTemp, NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pVehicleName )
	{
		CString strTemp;
		strTemp.Format( "%s %s", COMMENT::VEHICLE_TYPE[emTYPE].c_str(), pItem->GetName() );
		m_pVehicleName->SetOneLineText( strTemp, NS_UITEXTCOLOR::WHITE );
	}

	/*if ( emTYPE == VEHICLE_TYPE_BIKE || emTYPE == VEHICLE_TYPE_CAR || emTYPE == VEHICLE_TYPE_REARCAR )
	{
		if ( m_pBoostText )
		{
			std::string strBoost[2] = 
			{
				"CHARACTER_WINDOW_VEHICLE_BOOST_EMPTY",
				"CHARACTER_WINDOW_VEHICLE_BOOST_USING_EXPLAIN"
			};

			m_pBoostText->SetVisibleSingle( TRUE );
			m_pBoostText->SetOneLineText( ID2GAMEINTEXT( strBoost[bBooster].c_str() ), NS_UITEXTCOLOR::YELLOW );
		}	

		if ( m_pBoostIconOn )	m_pBoostIconOn->SetVisibleSingle( bBooster );
		if ( m_pBoostIconOff )	m_pBoostIconOff->SetVisibleSingle( !bBooster );
	}else*/{
		m_pBoostText->SetVisibleSingle( FALSE );
		m_pBoostIconOn->SetVisibleSingle( FALSE );
		m_pBoostIconOff->SetVisibleSingle( FALSE );
	}
}

void CCharacterWindowVehicle::LoadListPointShop( int nSelect )
{
	//pending feature for vehicle page pointshop
	CString strText;
	strText.Format( "%d", nSelect );
	m_pListPointShopNum->SetText( strText.GetString() );
}

void CCharacterWindowVehicle::ChangePointShopCategory( int nSelect )
{
	m_pBoardButton->SetFlip( FALSE );
	m_pBikeButton->SetFlip( FALSE );
	m_pPartsButton->SetFlip( FALSE );
	m_pBatteryButton->SetFlip( FALSE );

	switch (nSelect)
	{
	case 0:
		{
			m_pBoardButton->SetFlip( TRUE );
		}break;
	case 1:
		{
			m_pBikeButton->SetFlip( TRUE );
		}break;
	case 2:
		{
			m_pPartsButton->SetFlip( TRUE );
		}break;
	case 3:
		{
			m_pBatteryButton->SetFlip( TRUE );
		}break;
	}

	//adjust category by selected

	LoadListPointShop( 1 );
}

void CCharacterWindowVehicle::ClearRender()
{
	if( m_pRender )
	{
		m_pRender->ClearRender();
	}
}