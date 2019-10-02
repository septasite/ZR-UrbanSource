#include "StdAfx.h"
#include "InventoryPageWear.h"
#include "ItemImage.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "InnerInterface.h"
#include "ItemMove.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInventoryPageWear::nOUTOFRANGE = -1;

CInventoryPageWear::CInventoryPageWear () 
	: m_pMouseOver ( NULL )
{
}

CInventoryPageWear::~CInventoryPageWear ()
{
}

void CInventoryPageWear::CreateSubControl ( int nClassType )
{
	{	//	?????? ?????? ( 0 - 11 )
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD",			//หัว
			"CHARACTER_WINDOW_WEAR_SLOT_NECK",			//สร้อย
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER",			//เสื้อ
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_WEAPON",	//ยัน กระสุน
			"CHARACTER_WINDOW_WEAR_SLOT_WRIST",			//ต่างหู
			"CHARACTER_WINDOW_WEAR_SLOT_HAND",			//ถุงมือ
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER",			//กางเกง
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_EARRING",	//แหวน1
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_WEAPON",	//อาวุธ
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT",			//รองเท้า
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_EARRING",//แหวน2
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE",		//รถ
			"CHARACTER_WINDOW_WEAR_SLOT_WING",//ปีก
		};

		CString strInvenWearOver[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOT_HEAD_OVER",			//หัว
			"CHARACTER_WINDOW_WEAR_SLOT_NECK_OVER",			//สร้อย
			"CHARACTER_WINDOW_WEAR_SLOT_UPPER_OVER",		//เสื้อ
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_WEAPON_OVER",	//ยัน กระสุน
			"CHARACTER_WINDOW_WEAR_SLOT_WRIST_OVER",		//ต่างหู
			"CHARACTER_WINDOW_WEAR_SLOT_HAND_OVER",			//ถุงมือ
			"CHARACTER_WINDOW_WEAR_SLOT_LOWER_OVER",		//กางเกง
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_EARRING_OVER",	//แหวน1
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_WEAPON_OVER",	//อาวุธ
			"CHARACTER_WINDOW_WEAR_SLOT_FOOT_OVER",			//รองเท้า
			"CHARACTER_WINDOW_WEAR_SLOT_RIGHT_EARRING_OVER",//แหวน2
			"CHARACTER_WINDOW_WEAR_SLOT_VEHICLE_OVER",		//รถ
			"CHARACTER_WINDOW_WEAR_SLOT_LEFT_ACCESSORY_OVER",//ปีก
		};

		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pItemImage[i] = CreateItemImage ( strInvenWearItem[i].GetString (), ITEM_IMAGE0 + i );
			m_pSlotDisplay[i] = CreateControl ( strInvenWearOver[i].GetString () );
			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );
		}
	}

	m_pMouseOver = CreateControl ( "ITEM_MOUSE_OVER" );
//	m_pSlotDisplay = CreateControl ( "TRADE_INVENTORY_OVER_0" );
//	m_pSlotBlockDisplay = CreateControl ( "TRADE_OVER_0" );
}

CUIControl*	CInventoryPageWear::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CInventoryPageWear::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}

EMSLOT CInventoryPageWear::IMAGE2EMSLOT ( int nIndex )
{
	switch ( nIndex )
	{	
	case ITEM_IMAGE0:	return SLOT_HEADGEAR;	//	????
	case ITEM_IMAGE1:	return SLOT_NECK;		//	??????
	case ITEM_IMAGE2:	return SLOT_UPPER;		//	????
	case ITEM_IMAGE3:	return SLOT_LHAND;		//	????????
	case ITEM_IMAGE4:	return SLOT_WRIST;		//	????
	case ITEM_IMAGE5:	return SLOT_HAND;		//	????
	case ITEM_IMAGE6:	return SLOT_LOWER;		//	????
	case ITEM_IMAGE7:	return SLOT_LFINGER;	//	???? ?????
	case ITEM_IMAGE8:	return SLOT_RHAND;		//	??????????
	case ITEM_IMAGE9:	return SLOT_FOOT;		//	????
	case ITEM_IMAGE10:	return SLOT_RFINGER;	//	?????? ?????	
	case ITEM_IMAGE11:	return SLOT_VEHICLE;	
	case ITEM_IMAGE12:	return SLOT_WING;	

	}

	GASSERT ( 0 && "????? ??????????." );
	return SLOT_TSIZE;
}

void CInventoryPageWear::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE );
	if ( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );
//	if ( m_pSlotDisplay ) m_pSlotDisplay->SetVisibleSingle ( FALSE );
//	if ( m_pSlotBlockDisplay ) m_pSlotBlockDisplay->SetVisibleSingle ( FALSE );

	//	????, ???? ?????? ??????
	CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
	SNATIVEID sHOLD_ITEM_ID(false);
//	bool bFOUND_TOWEAR = false;
	if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

	for ( int i = 0; i < SLOT_NSIZE_2; i++ )
	{
		const SITEMCUSTOM& sItemCustomOld = GetItem ( i );

		EMSLOT emSlot = IMAGE2EMSLOT ( i + ITEM_IMAGE0 );
		SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_SLOT_ITEM ( emSlot );

		//	NOTE
		//		???? ???????? ????????,
		//		???????? ????? ????????,
		//		????/?????? ?????? ????????.
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
		//		?????? ??? ????
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

void CInventoryPageWear::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
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
	case ITEM_IMAGE12: 	//add wing
	
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = ControlID - ITEM_IMAGE0;
				SetItemIndex ( nIndex );

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				//	????, ???? ?????? ??????
				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove?? ????????." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pItemImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_WEARSLOT | UIMSG_TOTOPPARENT );
				}				

				//	????? ???? ??????
				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pItemImage[m_nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pItemImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}
			}
		}
		break;
	}
}

EMSLOT CInventoryPageWear::GetItemSlot ()
{
	return IMAGE2EMSLOT ( GetItemIndex () + ITEM_IMAGE0 );
}

void CInventoryPageWear::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	m_pItemImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), pItemData->sBasicOp.sNativeID );
}

SITEMCUSTOM& CInventoryPageWear::GetItem ( int nIndex )
{
	return m_ItemCustomArray[nIndex];
}

void CInventoryPageWear::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pItemImage[nIndex]->ResetItem ();
}