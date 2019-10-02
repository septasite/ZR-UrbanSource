#include "StdAfx.h"
#include "ItemPreviewWindow.h"
#include "ItemPreviewWindowRender.h"
#include "../InnerInterface.h"
#include "../BasicLineBox.h"
#include "../ItemImage.h"
#include "../UITextControl.h"
#include "../GameTextControl.h"
#include "../EngineLib/DxCommon/d3dfont.h"
#include "../EngineUiLib/GUInterface/BasicTextBox.h"
#include "../EngineUiLib/GUInterface/BasicButton.h"
#include "GLItemMan.h"
#include "GLGaeaClient.h"
#include "DxGlobalStage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemPreviewWindow::CItemPreviewWindow () 
	: m_pRender( NULL )
	, m_pButtonLeft( NULL )
	, m_pButtonRight( NULL )
	, m_pAnimButton( NULL )
	, m_pAnimText( NULL )
{
	for( int i=0; i<SPREVIEWDATA::PREVIEW_SLOTS; ++ i )
	{
		m_pSlotItem[i] = NULL;
		m_pSlotText[i] = NULL;
	}
}

CItemPreviewWindow::~CItemPreviewWindow ()
{
}

void CItemPreviewWindow::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, _DEFAULT_FONT_SHADOW_FLAG );

	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBox
		( 
		"ITEMPREVIEW_WINDOW_BKLINE", 
		"BASIC_LINE_BOX_LEFT_QUEST_LIST", 
		"BASIC_LINE_BOX_RIGHT_QUEST_LIST", 
		"BASIC_LINE_BOX_TOP_QUEST_LIST", 
		"BASIC_LINE_BOX_BOTTOM_QUEST_LIST",
		"ITEMPREVIEW_WINDOW_BKLINE_TEXINFO"
		);	

	RegisterControl ( pBasicLineBox );

	std::string strSlot[SPREVIEWDATA::PREVIEW_SLOTS] =
	{
		"ITEMPREVIEW_SLOT_HEAD",
		"ITEMPREVIEW_SLOT_UPPER",
		"ITEMPREVIEW_SLOT_LOWER",
		"ITEMPREVIEW_SLOT_HAND",
		"ITEMPREVIEW_SLOT_FOOT",
		"ITEMPREVIEW_SLOT_WEAPON"
	};

	std::string strText[SPREVIEWDATA::PREVIEW_SLOTS] =
	{
		"ITEMPREVIEW_TEXTBOX_HEAD",
		"ITEMPREVIEW_TEXTBOX_UPPER",
		"ITEMPREVIEW_TEXTBOX_LOWER",
		"ITEMPREVIEW_TEXTBOX_HAND",
		"ITEMPREVIEW_TEXTBOX_FOOT",
		"ITEMPREVIEW_TEXTBOX_WEAPON"
	};

	m_pRender = new CItemPreviewWindowRender;
	m_pRender->CreateSub ( this, "ITEMPREVIEW_WINDOW_MESHRENDER" );
	m_pRender->CreateSubControl ();
	RegisterControl ( m_pRender );

	for( int i=0; i<SPREVIEWDATA::PREVIEW_SLOTS; ++ i )
	{
		m_pSlotItem[i] = new CItemImage;
		m_pSlotItem[i]->CreateSub ( this, strSlot[i].c_str(), UI_FLAG_DEFAULT, ITEMSLOT_HEAD + i );
		m_pSlotItem[i]->CreateSubControl ();
		RegisterControl ( m_pSlotItem[i] );

		m_pSlotText[i] = new CBasicTextBox;
		m_pSlotText[i]->CreateSub ( this, strText[i].c_str() );
		m_pSlotText[i]->SetFont ( pFont9 );
		m_pSlotText[i]->SetText( ID2GAMEWORD( "ITEMPREVIEW_TEXTBOX", i ), NS_UITEXTCOLOR::YELLOW );
		RegisterControl ( m_pSlotText[i] );
	}

	m_pButtonLeft = new CBasicButton;
	m_pButtonLeft->CreateSub ( this, "ITEMPREVIEW_WINDOW_ARROW_TURN_LEFT_DEFAULT", UI_FLAG_DEFAULT, BUTTON_LEFT );
	m_pButtonLeft->CreateFlip ( "ITEMPREVIEW_WINDOW_ARROW_TURN_LEFT_CLICK", CBasicButton::CLICK_FLIP );
	m_pButtonLeft->CreateMouseOver ( "ITEMPREVIEW_WINDOW_ARROW_TURN_LEFT_OVER" );
	m_pButtonLeft->SetVisibleSingle( TRUE );
	RegisterControl ( m_pButtonLeft );

	m_pButtonRight = new CBasicButton;
	m_pButtonRight->CreateSub ( this, "ITEMPREVIEW_WINDOW_ARROW_TURN_RIGHT_DEFAULT", UI_FLAG_DEFAULT, BUTTON_RIGHT );
	m_pButtonRight->CreateFlip ( "ITEMPREVIEW_WINDOW_ARROW_TURN_RIGHT_CLICK", CBasicButton::CLICK_FLIP );
	m_pButtonRight->CreateMouseOver ( "ITEMPREVIEW_WINDOW_ARROW_TURN_RIGHT_OVER" );
	m_pButtonRight->SetVisibleSingle( TRUE );
	RegisterControl ( m_pButtonRight );

	m_pAnimButton = new CBasicButton;
	m_pAnimButton->CreateSub ( this, "ITEMPREVIEW_WINDOW_ANIMATION_CHECKBOX", UI_FLAG_DEFAULT, ANI_CHECKBOX );
	m_pAnimButton->CreateFlip ( "ITEMPREVIEW_WINDOW_ANIMATION_CHECKBOX_ON", CBasicButton::RADIO_FLIP );
	m_pAnimButton->SetControlNameEx ( "ITEMPREVIEW_WINDOW_ANIMATION_CHECKBOX" );
	RegisterControl ( m_pAnimButton );
	m_pAnimButton->SetFlip( RANPARAM::bPreviewStay );

	m_pAnimText = new CBasicTextBox;
	m_pAnimText->CreateSub ( this, "ITEMPREVIEW_WINDOW_ANIMATION_CHECKBOX_TEXT" );
	m_pAnimText->SetFont ( pFont9 );
	RegisterControl ( m_pAnimText );

	m_pAnimText->SetText( ID2GAMEINTEXT( "ITEMPREVIEW_MOVING_ANIMATION" ) );
}

void CItemPreviewWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_pRender )
	{
		for( int i=0; i<SPREVIEWDATA::PREVIEW_SLOTS; ++ i )
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem( m_pRender->m_sPreviewData.sPutOn[i].sNativeID );
			if ( pItem )
			{
				m_pSlotItem[i]->SetItem( pItem->sBasicOp.sICONID, pItem->GetInventoryFile() );
			}else{
				m_pSlotItem[i]->ResetItem();
			}
		}
	}
}

void CItemPreviewWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch( ControlID )
	{
	case BUTTON_RIGHT:
		{
			if ( CHECK_MOUSE_IN_LBDOWNLIKE ( dwMsg ) )
			{
				if ( m_pRender )	m_pRender->m_vRot.x +=0.1f;
			}
		}break;
	case BUTTON_LEFT:
		{
			if ( CHECK_MOUSE_IN_LBDOWNLIKE ( dwMsg ) )
			{
				if ( m_pRender )	m_pRender->m_vRot.x -=0.1f;
			}
		}break;

	case ITEMSLOT_HEAD:
	case ITEMSLOT_UPPER:
	case ITEMSLOT_LOWER:
	case ITEMSLOT_HAND:
	case ITEMSLOT_FOOT:
	case ITEMSLOT_WEAPON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				int nIndex = ControlID - ITEMSLOT_HEAD;

				if ( nIndex < 0 || nIndex >= SPREVIEWDATA::PREVIEW_SLOTS )	return;

				if ( m_pRender )
				{
					SITEMCUSTOM sItem = m_pRender->m_sPreviewData.sPutOn[nIndex];

					if( sItem.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItem, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}
				}
			}
		}break;
	case ANI_CHECKBOX:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				RANPARAM::bPreviewStay = !RANPARAM::bPreviewStay;
				m_pAnimButton->SetFlip( RANPARAM::bPreviewStay );
			}
		}break;
	};

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}

void CItemPreviewWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle( bVisible );

	if( bVisible )
	{
	}else{
		ClearRender();
	}
}

void CItemPreviewWindow::ClearRender()
{
	if ( m_pRender )
		m_pRender->ClearRender();
}

void CItemPreviewWindow::StartPreview( SITEMCUSTOM sItem )
{
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pCharacter )		return;

	if ( !m_pRender )	return;

	m_pRender->m_sPreviewData.wFace = pCharacter->m_wFace;
	m_pRender->m_sPreviewData.wHair = pCharacter->m_wHair;
	m_pRender->m_sPreviewData.wHairColor = pCharacter->m_wHairColor;

	m_pRender->m_sPreviewData.sPutOn[0] = pCharacter->m_PutOnItems[SLOT_HEADGEAR]; //head
	m_pRender->m_sPreviewData.sPutOn[1] = pCharacter->m_PutOnItems[SLOT_UPPER]; //upper
	m_pRender->m_sPreviewData.sPutOn[2] = pCharacter->m_PutOnItems[SLOT_LOWER]; //lower
	m_pRender->m_sPreviewData.sPutOn[3] = pCharacter->m_PutOnItems[SLOT_HAND]; //hand
	m_pRender->m_sPreviewData.sPutOn[4] = pCharacter->m_PutOnItems[SLOT_FOOT]; //foot
	m_pRender->m_sPreviewData.sPutOn[5] = pCharacter->m_PutOnItems[ pCharacter->IsUseArmSub()? SLOT_RHAND_S : SLOT_RHAND ]; //weapon

	SITEM* pItemCheck = GLItemMan::GetInstance().GetItem( sItem.sNativeID );
	if ( !pItemCheck )	return;

	if ( pItemCheck->sBasicOp.emItemType ==  ITEM_SUIT )
	{
		bool bCan = CInnerInterface::GetInstance().PreviewCheckWear( pItemCheck->sBasicOp.sNativeID );
		if ( !bCan )	return;

		int nSlotNum = -1;
		switch ( pItemCheck->sSuitOp.emSuit )
		{
		case SUIT_HEADGEAR:		nSlotNum = 0;	break;
		case SUIT_UPPER:		nSlotNum = 1;	break;
		case SUIT_LOWER:		nSlotNum = 2;	break;
		case SUIT_HAND:			nSlotNum = 3;	break;
		case SUIT_FOOT:			nSlotNum = 4;	break;
		case SUIT_HANDHELD:		nSlotNum = 5;	break;
		}

		if ( nSlotNum >= 0 )	m_pRender->m_sPreviewData.sPutOn[nSlotNum] = sItem;
	}
	else if ( pItemCheck->sBasicOp.emItemType == ITEM_BOX )
	{
		for ( int i=0; i<ITEM::SBOX::ITEM_SIZE; ++i )
		{
			SITEMCUSTOM sItemCustomBox;
			sItemCustomBox.sNativeID = pItemCheck->sBox.sITEMS[i].nidITEM;

			SITEM* pItemBox = GLItemMan::GetInstance().GetItem( sItemCustomBox.sNativeID );
			if( pItemBox )
			{
				bool bCan = CInnerInterface::GetInstance().PreviewCheckWear( pItemBox->sBasicOp.sNativeID );
				if ( !bCan )	continue;

				int nSlotNum = -1;
				switch ( pItemBox->sSuitOp.emSuit )
				{
				case SUIT_HEADGEAR:		nSlotNum = 0;	break;
				case SUIT_UPPER:		nSlotNum = 1;	break;
				case SUIT_LOWER:		nSlotNum = 2;	break;
				case SUIT_HAND:			nSlotNum = 3;	break;
				case SUIT_FOOT:			nSlotNum = 4;	break;
				case SUIT_HANDHELD:		nSlotNum = 5;	break;
				}

				if ( nSlotNum >= 0 )	m_pRender->m_sPreviewData.sPutOn[nSlotNum] = sItemCustomBox;
			}
		}
	}

	ClearRender();
	m_pRender->m_bReady = true;
}