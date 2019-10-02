#include "StdAfx.h"
#include "./InventoryPageWearEx.h"
#include "ItemImage.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "InnerInterface.h"
#include "ItemMove.h"
#include "BasicTextButton.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "./BasicVarTextBox.h"
#include "GameTextControl.h"
#include "d3dfont.h"
#include "UITextControl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInventoryPageWearEx::nOUTOFRANGE = -1;

CInventoryPageWearEx::CInventoryPageWearEx () 
	: m_pMouseOver(NULL)
	, m_pAButton(NULL)
	, m_pBButton(NULL)
	, m_pARHandSlot(NULL)
	, m_pALHandSlot(NULL)
	, m_pBRHandSlot(NULL)
	, m_pBLHandSlot(NULL)
{
	memset ( m_Button, 0, sizeof ( CUIControl* ) * 2 );	
	memset ( m_ButtonSet, 0, sizeof ( CUIControl* ) * 2 );
}

CInventoryPageWearEx::~CInventoryPageWearEx ()
{
}

void CInventoryPageWearEx::CreateSubControl ( int nClassType )
{
	{	//	아이템 이미지 ( 0 - 11 )
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD",
			"CHARACTER_WINDOW_WEAR_SLOT_NECK",
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_LEFT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_BRACELET",
			"CHARACTER_WINDOW_WEAR_SLOT_HAND",
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER",
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_RING",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_RIGHT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT",
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_RING",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_RIGHT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_LEFT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE",
			"CHARACTER_WINDOW_WEAR_SLOT_WING",
			"CHARACTER_WINDOW_WEAR_SLOT_BELT",
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_EARRING",
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_EARRING",
			"CHARACTER_WINDOW_WEAR_SLOT_ACCESSORY",
		};

		CString strInvenWearOver[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_NECK_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_LEFT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_BRACELET_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_HAND_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_RING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_FIRST_RIGHT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_RING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_RIGHT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_EX_SECOND_LEFT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_WING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_BELT_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_EARRING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_EARRING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOT_ACCESSORY_OVER",
		};


		CString InventoryText[ITEM_IMAGE_SIZE] = 
		{
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_HEAD",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_NECK",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_UPPER",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_FIRST_LEFT_WEAPON",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_BRACELET",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_HAND",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_LOWER",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_LEFT_RING",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_FIRST_RIGHT_WEAPON",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_FOOT",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_RIGHT_RING",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_SECOND_RIGHT_WEAPON",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_SECOND_LEFT_WEAPON",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_VEHICLE",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_WING",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_BELT",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_LEFT_EARRING",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_RIGHT_EARRING",
			"INVENTORY_WEAR_OVER_TEXT_UPS_IMAGE_ACCESSORY",
		};

		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pItemImage[i] = CreateItemImage ( strInvenWearItem[i].GetString (), ITEM_IMAGE0 + i );
			m_pSlotDisplay[i] = CreateControl ( strInvenWearOver[i].GetString () );
			m_pNumberBoxArray[i] = CreateNumberBox ( InventoryText[i].GetString () );
			m_pNumberBoxArray2[i] = CreateNumberBox ( InventoryText[i].GetString () );
			m_pNumberBoxArray[i]->SetOneLineText ( "",0 );
            m_pNumberBoxArray2[i]->SetOneLineText ( "",0 );  
			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );
		}
	}

	m_pMouseOver = CreateControl ( "ITEM_MOUSE_OVER" );

	CString strButton[2] =
	{
		"SWITCH_BUTTONA",
		"SWITCH_BUTTONB"
	};

	CString strButtonSet[2] =
	{
		"SWITCH_BUTTONA_F",
		"SWITCH_BUTTONB_F"
	};

	for ( int i = 0; i < 2 ; i++ )
	{
		m_Button[i] = new CUIControl;
		m_Button[i]->CreateSub ( this, strButton[i].GetString (), UI_FLAG_DEFAULT, SWITCH_BUTTONA + i );
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_Button[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_Button[i] );

		m_ButtonSet[i] = new CUIControl;
		m_ButtonSet[i]->CreateSub ( this, strButtonSet[i].GetString (), UI_FLAG_DEFAULT );	
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
		m_ButtonSet[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_ButtonSet[i] );
	}

	/*m_pAButton = new CBasicTextButton;
	m_pAButton->CreateSub ( this, "BASIC_TEXT_BUTTON161", UI_FLAG_XSIZE, SWITCH_BUTTONA );
	m_pAButton->CreateBaseButton(	"SWITCH_BUTTONA_F",
									CBasicTextButton::SIZE16s, 
									CBasicButton::RADIO_FLIP, 
									(char*)ID2GAMEWORD("INVEN_TAB_BUTTON",0) );
	m_pAButton->SetFlip ( TRUE );
	RegisterControl ( m_pAButton );

	m_pBButton = new CBasicTextButton;
	m_pBButton->CreateSub ( this, "BASIC_TEXT_BUTTON161", UI_FLAG_XSIZE, SWITCH_BUTTONB );
	m_pBButton->CreateBaseButton(	"SWITCH_BUTTONB_F",
									CBasicTextButton::SIZE16s, 
									CBasicButton::RADIO_FLIP,
									(char*)ID2GAMEWORD("INVEN_TAB_BUTTON",1) );
	m_pBButton->SetFlip ( TRUE );
	RegisterControl ( m_pBButton );*/

	m_pARHandSlot = CreateControl("INVENTORY_USE_SLOT_RHAND_A");
	m_pALHandSlot = CreateControl("INVENTORY_USE_SLOT_LHAND_A");
	m_pBRHandSlot = CreateControl("INVENTORY_USE_SLOT_RHAND_B");
	m_pBLHandSlot = CreateControl("INVENTORY_USE_SLOT_LHAND_B");
}

CUIControl*	CInventoryPageWearEx::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CInventoryPageWearEx::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}

EMSLOT CInventoryPageWearEx::IMAGE2EMSLOT ( int nIndex )
{
	switch ( nIndex )
	{	
	case ITEM_IMAGE0:	return SLOT_HEADGEAR;	//	머리
	case ITEM_IMAGE1:	return SLOT_NECK;		//	목걸이
	case ITEM_IMAGE2:	return SLOT_UPPER;		//	상의
	case ITEM_IMAGE3:	return SLOT_LHAND;		//	왼손도구
	case ITEM_IMAGE4:	return SLOT_WRIST;		//	손목
	case ITEM_IMAGE5:	return SLOT_HAND;		//	장갑
	case ITEM_IMAGE6:	return SLOT_LOWER;		//	하의
	case ITEM_IMAGE7:	return SLOT_LFINGER;	//	왼손 손가락
	case ITEM_IMAGE8:	return SLOT_RHAND;		//	오른손도구
	case ITEM_IMAGE9:	return SLOT_FOOT;		//	신발
	case ITEM_IMAGE10:	return SLOT_RFINGER;	//	오른손 손가락	
	case ITEM_IMAGE11:	return SLOT_RHAND_S;	//	오른손도구, 극강부
	case ITEM_IMAGE12:	return SLOT_LHAND_S;	//	왼손도구, 극강부
	case ITEM_IMAGE13:	return SLOT_VEHICLE;	//  탈것
	case ITEM_IMAGE14:	return SLOT_WING;
	case ITEM_IMAGE15:	return SLOT_BELT;
	case ITEM_IMAGE16:	return SLOT_LEARRING;
	case ITEM_IMAGE17:	return SLOT_REARRING;
	case ITEM_IMAGE18:	return SLOT_ACCESSORY;

	}

	GASSERT ( 0 && "범위를 벗어납니다." );
	return SLOT_TSIZE;
}

void CInventoryPageWearEx::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE );
	if ( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );

	//	스냅, 스킬 이미지 붙이기
	CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
	SNATIVEID sHOLD_ITEM_ID(false);
	if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

	for ( int i = 0; i < SLOT_NSIZE_S_2; i++ )
	{
		const SITEMCUSTOM& sItemCustomOld = GetItem ( i );

		EMSLOT emSlot = IMAGE2EMSLOT ( i + ITEM_IMAGE0 );
		SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_SLOT_ITEM ( emSlot );

		//	NOTE
		//		이전 프레임과 비교하여,
		//		데이타가 달라진 경우에만,
		//		로드/언로드 작업을 진행한다.
		if ( sItemCustom != sItemCustomOld )
		{		
			if ( sItemCustom.sNativeID != NATIVEID_NULL () )
			{
				LoadItem ( i, sItemCustom );
			}
			else
			{
				UnLoadItem ( i );
			}
		}

		m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );

		//	NOTE
		//		장착될 위치 표시
		if ( sHOLD_ITEM_ID != NATIVEID_NULL () /*&& !bFOUND_TOWEAR*/ )
		{
			if ( GLGaeaClient::GetInstance().GetCharacter()->CHECKSLOT_ITEM ( sHOLD_ITEM_ID, emSlot ) )
			{
				const UIRECT& rcImagePos = m_pItemImage[i]->GetGlobalPos ();
				D3DXVECTOR2 vPos ( rcImagePos.left, rcImagePos.top );

				if ( GLGaeaClient::GetInstance().GetCharacter()->ACCEPT_ITEM ( sHOLD_ITEM_ID ) )
				{
					m_pSlotDisplay[i]->SetVisibleSingle ( TRUE );
				}

//				bFOUND_TOWEAR = true;
			}
		}
	}

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CInventoryPageWearEx::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ITEM_IMAGE0:
	case ITEM_IMAGE1:
	case ITEM_IMAGE2:
	case ITEM_IMAGE3:
	case ITEM_IMAGE4:
	case ITEM_IMAGE5:
	case ITEM_IMAGE6:
	case ITEM_IMAGE7:
	case ITEM_IMAGE8:
	case ITEM_IMAGE9:
	case ITEM_IMAGE10:	
	case ITEM_IMAGE11:	
	case ITEM_IMAGE12:	
	case ITEM_IMAGE13:
	case ITEM_IMAGE14:
	case ITEM_IMAGE15:
	case ITEM_IMAGE16:
	case ITEM_IMAGE17:
	case ITEM_IMAGE18:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = ControlID - ITEM_IMAGE0;
				SetItemIndex ( nIndex );

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				//	스냅, 스킬 이미지 붙이기
				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove가 널입니다." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pItemImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_WEARSLOTEX | UIMSG_TOTOPPARENT );
				}				

				//	마우스 표시 테두리
				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pItemImage[m_nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pItemImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}


				if ( dwMsg & UIMSG_RB_UP )
				{
				//int nPosX, nPosY;
				//m_pPage->GetItemIndex ( &nPosX, &nPosY );
				//if ( nPosX < 0 || nPosY < 0 ) return;
//				WORD wPosX, wPosY;
				EMSLOT J;
				SITEM* pItemData = GLItemMan::GetInstance().GetItem ( m_ItemCustomArray[nIndex].sNativeID );
					if ( !pItemData  ) return;
		
				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
					if ( !pCharacter ) return;	

				EMITEM_TYPE emItemType = pItemData->sBasicOp.emItemType;

				//pInvenItem = pCharacter->m_cInventory.FindPosItem ( pInvenItem->wPosX, pInvenItem->wPosY );
					//if ( !pInvenItem ) return;
				if (pItemData)
						{
							switch ( pItemData->sSuitOp.emSuit )
							{
							case SUIT_HEADGEAR:		J = SLOT_HEADGEAR;break;
							case SUIT_UPPER:		J = SLOT_UPPER;break;
							case SUIT_LOWER:		J = SLOT_LOWER;break;
							case SUIT_HAND:			J = SLOT_HAND;break;
							case SUIT_FOOT:			J = SLOT_FOOT;break;
							case SUIT_NECK:			J = SLOT_NECK;break;
							case SUIT_WRIST:		J = SLOT_WRIST;break;
							case SUIT_VEHICLE:		J = SLOT_VEHICLE;break;
							case SUIT_WING:			J = SLOT_WING;break;
							case SUIT_BELT:			J = SLOT_BELT;break;
							case SUIT_ACCESSORY:	J = SLOT_ACCESSORY;break;
							case SUIT_HANDHELD:	
								if ( emItemType == ITEM_ARROW || emItemType == ITEM_CHARM || emItemType == ITEM_BULLET )
								{
									if(GLGaeaClient::GetInstance().GetCharacter()->IsUseArmSub())
									{
										J = SLOT_LHAND_S;
									}
									else{
										J = SLOT_LHAND;
									}
								}
								else
								{
									if(GLGaeaClient::GetInstance().GetCharacter()->IsUseArmSub())
									{
										J = SLOT_RHAND_S;
									}
									else{
										J = SLOT_RHAND;
									}
								}
								break;
							case SUIT_FINGER:	
								{
									
									if ( m_bRingSwap )
									{
										m_bRingSwap = FALSE;
										J = SLOT_RFINGER;
									}
									else
									{
										J = SLOT_LFINGER;
										m_bRingSwap = TRUE;
									}
								}
								break;
							case SUIT_EARRING:	
								{
									
									if ( m_bEarringSwap )
									{
										m_bEarringSwap = FALSE;
										J = SLOT_REARRING;
									}
									else
									{
										J = SLOT_LEARRING;
										m_bEarringSwap = TRUE;
									}
								}
								break;
							};
							GLGaeaClient::GetInstance().GetCharacter()->ReqUnEquipItem ( J );
						}
				
				return ;
				}
			}
		}
		break;

	case SWITCH_BUTTONA:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				SWITCH1();
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}
		break;
	case SWITCH_BUTTONB:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				SWITCH2();
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}
		break;

	/*case TEXT_A_BUTTON:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}
		break;

	case TEXT_B_BUTTON:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				GLGaeaClient::GetInstance().GetCharacter()->ReqSlotChange();
			}
		}
		break;*/
	}
}

EMSLOT CInventoryPageWearEx::GetItemSlot ()
{
	return IMAGE2EMSLOT ( GetItemIndex () + ITEM_IMAGE0 );
}
void CInventoryPageWearEx::UpgradeColorAddon ( BYTE AddonUpsColor )
	{
		if ( !AddonUpsColor ) return ;

		CString strGRADE;
		strGRADE.Format ( "[+%d]", AddonUpsColor );
		
	}
void CInventoryPageWearEx::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	if ( pItemData )
	{
		const WORD wPileNum = pItemData->sDrugOp.wPileNum;
		const WORD wTurnNum = ref_sItemCustom.wTurnNum;
		if ( wPileNum>1 || wTurnNum>1 )
		{
			CString strNumber;
			strNumber.Format ( "%d", wTurnNum );
			DWORD dwColor = NS_UITEXTCOLOR::GREENYELLOW;
			if ( wTurnNum == wPileNum ) dwColor = NS_UITEXTCOLOR::ORANGE;
			m_pNumberBoxArray[nIndex]->SetOneLineText ( strNumber.GetString(), dwColor );
			m_pNumberBoxArray[nIndex]->SetVisibleSingle ( TRUE );
		
		}
		else
		{
			CString Upgrade="";
			BYTE AddonUpsColor = ref_sItemCustom.GETGRADE(EMGRINDING_NUNE);
			if ( AddonUpsColor !=0 ) Upgrade.Format("+%d",AddonUpsColor );
			UpgradeColorAddon (  AddonUpsColor );
            m_pNumberBoxArray2[nIndex]->SetVisibleSingle ( TRUE );
		
		
		DWORD dwColorUpgrade[GRADE_LIMIT_MAX+1] = 
		{			
			NS_UITEXTCOLOR::WHITE,//0
			NS_UITEXTCOLOR::DARKGRAY,//1
			NS_UITEXTCOLOR::DARKGRAY,//2
			NS_UITEXTCOLOR::DARKGRAY,//3
			NS_UITEXTCOLOR::SILVER,//4
			NS_UITEXTCOLOR::SILVER,//5
			NS_UITEXTCOLOR::SILVER,//6
			NS_UITEXTCOLOR::ORANGE,//7 
			NS_UITEXTCOLOR::ORANGE,//8
			NS_UITEXTCOLOR::GOLD,//9
			NS_UITEXTCOLOR::AQUA,//10
			NS_UITEXTCOLOR::VIOLET,//11
			NS_UITEXTCOLOR::GREEN,//12
			NS_UITEXTCOLOR::RED,//13
			NS_UITEXTCOLOR::FUCHSIA,//14
			NS_UITEXTCOLOR::YELLOW,//15
			NS_UITEXTCOLOR::WHITE,//16
			NS_UITEXTCOLOR::LIGHTORANGE,//17
			NS_UITEXTCOLOR::PURPLEXD,//18
		};

		    int ColorGrade;
			if ( AddonUpsColor > 18 ) { ColorGrade = 0; }
			else { ColorGrade = AddonUpsColor; }
			m_pNumberBoxArray2[nIndex]->SetOneLineText ( Upgrade, dwColorUpgrade[ColorGrade] );
            if ( AddonUpsColor == 0 ){
			m_pNumberBoxArray2[nIndex]->SetOneLineText ( "+0", dwColorUpgrade[ColorGrade] );}
		}
	}
	m_pItemImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), pItemData->sBasicOp.sNativeID );
}

SITEMCUSTOM& CInventoryPageWearEx::GetItem ( int nIndex )
{

	return m_ItemCustomArray[nIndex];
}

void CInventoryPageWearEx::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pItemImage[nIndex]->ResetItem ();
	m_pNumberBoxArray[nIndex]->ClearText ();
	m_pNumberBoxArray2[nIndex]->ClearText ();
}
CBasicTextBox* CInventoryPageWearEx::CreateNumberBox ( const char* szControl )
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, szControl );
    pTextBox->SetFont ( pFont8 );
	pTextBox->SetTextAlign ( TEXT_ALIGN_RIGHT );
	RegisterControl ( pTextBox );

	return pTextBox;
}

void CInventoryPageWearEx::SWITCH1()
{
	for ( int i = 0; i < 2; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[0]->SetVisibleSingle ( TRUE );
	m_Button[0]->SetVisibleSingle ( FALSE );

	m_pARHandSlot->SetVisibleSingle( FALSE );
	m_pALHandSlot->SetVisibleSingle( FALSE );
	m_pBRHandSlot->SetVisibleSingle( TRUE );
	m_pBLHandSlot->SetVisibleSingle( TRUE );
}
void CInventoryPageWearEx::SWITCH2()
{
	for ( int i = 0; i < 2; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[1]->SetVisibleSingle ( TRUE );
	m_Button[1]->SetVisibleSingle ( FALSE );

	m_pARHandSlot->SetVisibleSingle( TRUE );
	m_pALHandSlot->SetVisibleSingle( TRUE );
	m_pBRHandSlot->SetVisibleSingle( FALSE );
	m_pBLHandSlot->SetVisibleSingle( FALSE );
}

void CInventoryPageWearEx::SetTabButton( BOOL bMain )
{
	if( bMain )
	{
		for ( int i = 0; i < 2; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[0]->SetVisibleSingle ( TRUE );
	m_Button[0]->SetVisibleSingle ( FALSE );

		m_pARHandSlot->SetVisibleSingle( FALSE );
		m_pALHandSlot->SetVisibleSingle( FALSE );
		m_pBRHandSlot->SetVisibleSingle( TRUE );
		m_pBLHandSlot->SetVisibleSingle( TRUE );
	}
	else
	{
		for ( int i = 0; i < 2; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[1]->SetVisibleSingle ( TRUE );
	m_Button[1]->SetVisibleSingle ( FALSE );

		m_pARHandSlot->SetVisibleSingle( TRUE );
		m_pALHandSlot->SetVisibleSingle( TRUE );
		m_pBRHandSlot->SetVisibleSingle( FALSE );
		m_pBLHandSlot->SetVisibleSingle( FALSE );
	}
}