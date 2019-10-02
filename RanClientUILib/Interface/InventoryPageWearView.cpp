#include "StdAfx.h"
#include "InventoryPageWearView.h"
#include "../CharacterViewPropertiesWindow.h"
#include "ItemImage.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "InnerInterface.h"
#include "d3dfont.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "CharacterWindowCharRenderView.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInventoryPageWearView::nOUTOFRANGE = -1;

CInventoryPageWearView::CInventoryPageWearView () 
{
}

CInventoryPageWearView::~CInventoryPageWearView ()
{
}

void CInventoryPageWearView::CreateSubControl ( int nClassType )
{
	{	//	æ∆¿Ã≈€ ¿ÃπÃ¡ˆ ( 0 - 11 )
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_HEAD",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_UPPER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LOWER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_HAND",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_FIRST_RIGHT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_SECOND_RIGHT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_WRIST",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_NECK",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_FINGER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_FINGER",	
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_FIRST_LEFT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_SECOND_LEFT_WEAPON",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_VEHICLE",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_ACCESSORY",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_WAIST",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_EARRING",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_EARRING",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_ACCESSORY",
		};

		CString strInvenWearOver[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_HEAD_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_NECK_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_UPPER_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_SECOND_LEFT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_WRIST_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_HAND_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LOWER_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_EARRING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_FIRST_LEFT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_EARRING_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_FIRST_RIGHT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_EX_SECOND_RIGHT_WEAPON_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_VEHICLE_OVER",		//√∂
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_ACCESSORY_OVER",//ª’°
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_WAIST_OVER",		//ÕÕ√Ë“
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_ACCESSORY_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_FINGER_OVER",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_FINGER_OVER",
		};

		CString strViewItem[10] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER1",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER2",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER3",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER4",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER5",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER6",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER7",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER8",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER9",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_OVER10",
		};

		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pItemImage[i] = CreateItemImage ( strInvenWearItem[i].GetString (), ITEM_IMAGE0 + i );
			m_pSlotDisplay[i] = CreateControl ( strInvenWearOver[i].GetString () );
			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );
		}

		for ( int i = 0; i < 10; i++ )
		{
			m_pSlotDisplayDummy[i] = CreateControl ( strViewItem[i].GetString () );
		}
	}

	m_pMouseOver = CreateControl ( "ITEM_MOUSE_OVER" );

	CreateNumberBox ();
}

CUIControl*	CInventoryPageWearView::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CInventoryPageWearView::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}
EMSLOT CInventoryPageWearView::IMAGE2EMSLOT ( int nIndex )
{
	switch ( nIndex )
	{	
	case ITEM_IMAGE0:	return SLOT_HEADGEAR;	//	∏”∏Æ
	case ITEM_IMAGE1:	return SLOT_UPPER;		//	∏Ò∞…¿Ã
	case ITEM_IMAGE2:	return SLOT_LOWER;	//	ªÛ¿«
	case ITEM_IMAGE3:	return SLOT_HAND;		//	øﬁº’µµ±∏
	case ITEM_IMAGE4:	return SLOT_FOOT;		//	º’∏Ò
	case ITEM_IMAGE5:	return SLOT_NECK;		//	¿Â∞©
	case ITEM_IMAGE6:	return SLOT_WRIST;		//	«œ¿«
	case ITEM_IMAGE7:	return SLOT_RFINGER;	//	øﬁº’ º’∞°∂Ù
	case ITEM_IMAGE8:	return SLOT_LFINGER;		//	ø¿∏•º’µµ±∏
	case ITEM_IMAGE9:	return SLOT_RHAND;		//	Ω≈πﬂ
	case ITEM_IMAGE10:	return SLOT_LHAND;	//	ø¿∏•º’ º’∞°∂Ù	
	case ITEM_IMAGE11:	return SLOT_RHAND_S;	//	ø¿∏•º’µµ±∏, ±ÿ∞≠∫Œ
	case ITEM_IMAGE12:	return SLOT_LHAND_S;	//	øﬁº’µµ±∏, ±ÿ∞≠∫Œ
	case ITEM_IMAGE13:	return SLOT_VEHICLE;	//  ≈ª∞Õ
	case ITEM_IMAGE14:	return SLOT_WING;
//	case ITEM_IMAGE15:	return SLOT_AURA;
	case ITEM_IMAGE16:	return SLOT_BELT;
//	case ITEM_IMAGE17:	return SLOT_EARRING;
	case ITEM_IMAGE18:	return SLOT_ACCESSORY;
	}

	GASSERT ( 0 && "π¸¿ß∏¶ π˛æÓ≥≥¥œ¥Ÿ." );
	return SLOT_TSIZE;
}

void CInventoryPageWearView::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE );
	if ( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	
}

void CInventoryPageWearView::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
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

				if ( dwMsg & UIMSG_RB_UP )
				{
				}
			}
		}
		break;
	}
}

EMSLOT CInventoryPageWearView::GetItemSlot ()
{
	return IMAGE2EMSLOT ( GetItemIndex () + ITEM_IMAGE0 );
}

void CInventoryPageWearView::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	//m_pItemImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), pItemData->sBasicOp.sNativeID );
	//m_pItemImage[nIndex]->SetItem2 ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), ref_sItemCustom.GETGRADE( EMGRINDING_NUNE ), pItemData->sBasicOp.sNativeID );
	
	const WORD wAttackNum =  ref_sItemCustom.grade_damage();
	const WORD wDefenseNum = ref_sItemCustom.grade_defense();
	int nNumber;
	if( wAttackNum > wDefenseNum ) 
		 nNumber  = wAttackNum;
	else
		 nNumber  = wDefenseNum;

	//if( wAttackNum > 0 || wDefenseNum > 0 )
	{
		/*CString strNumber;
		strNumber.Format ( "+%d", nNumber );
		DWORD dwColor = NS_UITEXTCOLOR::LIGHTSKYBLUE;
		m_pNumberBoxArray[nIndex]->SetOneLineText ( strNumber, dwColor );
		m_pNumberBoxArray[nIndex]->SetVisibleSingle ( TRUE );*/
		m_pItemImage[nIndex]->SetItem2 ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), ref_sItemCustom.GETGRADE( EMGRINDING_NUNE ), pItemData->sBasicOp.sNativeID );
	}
	
}

SITEMCUSTOM& CInventoryPageWearView::GetItem ( int nIndex )
{
	return m_ItemCustomArray[nIndex];
}

void CInventoryPageWearView::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pItemImage[nIndex]->ResetItem ();
	//m_pNumberBoxArray[nIndex]->ClearText ();
	//m_pNumberBoxArray[nIndex]->SetVisibleSingle ( FALSE );
}
void CInventoryPageWearView::ReSetAllItemEx()
{
	for ( int i = 0; i < SLOT_NSIZE_S_2; i++ )
	{
		UnLoadItem ( i );
	}
}

void CInventoryPageWearView::SetItemInInventoryEx(int m_nIndex, SITEMCUSTOM& sItemCustom)
{
	if ( sItemCustom.sNativeID != NATIVEID_NULL() )
	{
		LoadItem ( m_nIndex, sItemCustom );
	}
	else
	{
		UnLoadItem ( m_nIndex );
		//m_pNumberBoxArray[m_nIndex]->ClearText ();
		//m_pNumberBoxArray[m_nIndex]->SetVisibleSingle ( FALSE );
	}
}



CBasicTextBox* CInventoryPageWearView::CreateNumberBox ( const char* szControl )
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, szControl );
    pTextBox->SetFont ( pFont8 );
	pTextBox->SetTextAlign ( TEXT_ALIGN_RIGHT );
	RegisterControl ( pTextBox );

	return pTextBox;
}

void CInventoryPageWearView::SetNumber ( int nIndex, int nNumber, int nMaxNumber )
{
	CString strNumber;
	strNumber.Format ( "%d", nNumber );
	DWORD dwColor = NS_UITEXTCOLOR::GREENYELLOW;
	if ( nNumber == nMaxNumber ) dwColor = NS_UITEXTCOLOR::ORANGE;
	m_pNumberBoxArray[nIndex]->SetOneLineText ( strNumber, dwColor );
	m_pNumberBoxArray[nIndex]->SetVisibleSingle ( TRUE );
}

void CInventoryPageWearView::SetNumber2 ( int nIndex, int nNumber )
{
	CString strNumber;
	strNumber.Format ( "+%d", nNumber );
	DWORD dwColor = NS_UITEXTCOLOR::LIGHTSKYBLUE;
	m_pNumberBoxArray[nIndex]->SetOneLineText ( strNumber, dwColor );
	m_pNumberBoxArray[nIndex]->SetVisibleSingle ( TRUE );
}


void CInventoryPageWearView::ResetNumber ( int nIndex )
{
	m_pNumberBoxArray[nIndex]->ClearText ();
	m_pNumberBoxArray[nIndex]->SetVisibleSingle ( FALSE );
}

void CInventoryPageWearView::CreateNumberBox ()
{
	{	//	πÿπŸ¥⁄ πË∞Ê
		CString strInvenWearItem[ITEM_IMAGE_SIZE] = 
		{
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_HEAD_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_UPPER_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LOWER_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_HAND_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_WRIST_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_NECK_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_FINGER_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_FINGER_TEXT",	
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_FOOT_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_ACCESSORY_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_WAIST_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_EARRING_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_RIGHT_EARRING_TEXT",
			"CHARACTER_WINDOW_WEAR_SLOTVIEW_LEFT_ACCESSORY_TEXT",
		};

		for ( int i = 0; i < ITEM_IMAGE_SIZE; i++ )
		{
			m_pNumberBoxArray[i] = CreateNumberBox ( strInvenWearItem[i].GetString () );			
		}
	}
}