#include "StdAfx.h"
#include "RebuildInventoryWindow.h"

#include "D3DFont.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUIlib/GUInterface/BasicTextBox.h"
#include "../EngineUIlib/GUInterface/BasicButton.h"
#include "ModalCallerID.h"
#include "ModalWindow.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "UITextControl.h"
#include "BasicTextButton.h"
#include "GameTextControl.h"
#include "RebuildInventoryPage.h"
#include "InnerInterface.h"
#include "d3dfont.h"
#include "GLItemMan.h"
#include "GLGaeaClient.h"
#include "../EngineUiLib/GUInterface/BasicButtonText.h"
#include "BasicLineBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//--------------------------------------------------------------------
// RebuildInventoryWindow
//--------------------------------------------------------------------
CRebuildInventoryWindow::CRebuildInventoryWindow()	// ITEMREBUILD_MARK
	: m_pPage ( NULL ),
	m_pMoneyTextBox ( NULL ),
	m_pPointTextBox( NULL ),
	m_nONE_VIEW_SLOT ( 4 )
{
	memset ( m_pPageButton, 0, sizeof ( CBasicTextButton* ) * 1 );
}

CRebuildInventoryWindow::~CRebuildInventoryWindow()
{
}

VOID CRebuildInventoryWindow::CreateSubControl()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	const int nAlignCenterBoth = TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y;
	const int nAlignCenteredLeft = TEXT_ALIGN_LEFT;

	{
		m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "TRADEINVENTORY_BG_WHITE", UI_FLAG_DEFAULT);	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	}

	CString strButtonKeyword[1] = 
	{
		"INVENTORY_PAGE_INVEN"
	};

	for ( int i = 0; i < 1; i++ )
	{	
		m_pPageButton[i] = CreateTextButton ( strButtonKeyword[i].GetString (), INVENTORY_PAGE_BUTTON0 + i, (char*)ID2GAMEWORD ( "NEW_INVENTORY_BUTTON", i ) );
	}

	CUIControl* pControl = CreateControl( "REBUILDINVENTORY_MONEY_BACK" );
	pControl->SetAlignFlag( UI_FLAG_DEFAULT );

	CUIControl* pControl2 = CreateControl ( "REBUILDINVENTORY_POINT_BACK" );
	pControl2->SetAlignFlag ( UI_FLAG_DEFAULT );

	CUIControl* pControl3 = CreateControl ( "REBUILDINVENTORY_SLOT_BACK" );
	pControl3->SetAlignFlag ( UI_FLAG_DEFAULT );

	m_pPage = new CRebuildInventoryPage;
	m_pPage->CreateSub( this, "REBUILDINVENTORY_PAGE", UI_FLAG_YSIZE, REBUILDINVENTORY_PAGE );
	m_pPage->CreateSubControl();
	m_pPage->SetVisibleSingle(TRUE);
	RegisterControl( m_pPage );

	CBasicButton* pButtonPoint = NULL;
	pButtonPoint = CreateFlipButton ( "REBUILDINVENTORY_POINT_BUTTON", "REBUILDINVENTORY_POINT_BUTTON_F", REBUILDINVENTORY_POINT_BUTTON, CBasicButton::CLICK_FLIP );
	pButtonPoint->SetAlignFlag ( UI_FLAG_DEFAULT );
	pButtonPoint->SetUseDynamic ( TRUE );

	CBasicButton* pButton = NULL;
	pButton = CreateFlipButton ( "REBUILDINVENTORY_MONEY_BUTTON", "REBUILDINVENTORY_MONEY_BUTTON_F", REBUILDINVENTORY_MONEY_BUTTON, CBasicButton::CLICK_FLIP );
	pButton->CreateMouseOver ( "REBUILDINVENTORY_MONEY_BUTTON_F" );
	pButton->SetAlignFlag ( UI_FLAG_DEFAULT );
	pButton->SetUseDynamic ( TRUE );

	char* szButton[4] =
	{
		"INVENTORY_BUTTON00",
		"INVENTORY_BUTTON01",
		"INVENTORY_BUTTON02",
		"INVENTORY_BUTTON03",
	};

	for ( int i = 0; i < 4; i++)
	{
		m_pButton[i] = CreateButtonBlue ( szButton[i], szButton[i], pFont9, nAlignCenteredLeft, INVENTORY_LOCKER_BUTTON + i, "" );
	}

	CreateControl( "IVENTORY_ICON00" );
	CreateControl( "IVENTORY_ICON01" );
	CreateControl( "IVENTORY_ICON02" );
	CreateControl( "IVENTORY_ICON03" );



	
	m_pMoneyTextBox = CreateStaticControl ( "REBUILDINVENTORY_MONEY_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
	m_pMoneyTextBox->SetAlignFlag ( UI_FLAG_DEFAULT );

	m_pPointTextBox = CreateStaticControl ( "REBUILDINVENTORY_POINT_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
	m_pPointTextBox->SetAlignFlag ( UI_FLAG_DEFAULT );
	m_pPointTextBox->SetOneLineText ( "0" );
}

CBasicTextButton*  CRebuildInventoryWindow::CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButtonEx ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText, _DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicButtonText* CRebuildInventoryWindow::CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText )
{
	CBasicButtonText* pButton = new CBasicButtonText;
	pButton->CreateRanButtonBlue ( this, szButton, ControlID );
	pButton->CreateTextBox ( szTextBox, pFont, nAlign );
	pButton->SetOneLineText( strText.GetString() );
	RegisterControl ( pButton );

	return pButton;
}

CBasicTextButton*  CRebuildInventoryWindow::CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE24;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;
}

VOID CRebuildInventoryWindow::Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	GLCHARLOGIC& ref_CharData = GLGaeaClient::GetInstance().GetCharacterLogic();

	if( ref_CharData.m_sRebuildItem.VALID() )
		m_pPage->UpdateFlipItem( ref_CharData.m_sRebuildItem );
	else
		m_pPage->ResetAllFlipItem();

	{
		CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT( ref_CharData.m_lnMoney, 3, "," );
		m_pMoneyTextBox->SetOneLineText( strTemp );
	}

	{
		GLInventory& ref_Inventory = ref_CharData.m_cInventory;
		m_pPage->LoadItemPage( ref_Inventory );
	}
}

VOID CRebuildInventoryWindow::TranslateUIMessage( UIGUID ControlID, DWORD dwMsg )
{
	switch( ControlID )
	{
	case REBUILDINVENTORY_PAGE:
		if( CHECK_MOUSE_IN( dwMsg ) )
		{
			INT nPosX, nPosY;
			m_pPage->GetItemIndex( &nPosX, &nPosY );

			CDebugSet::ToView( 1, 1, "¿Œ∫• : %d %d", nPosX, nPosY );

			if( nPosX < 0 || nPosY < 0 )
				return;

			SINVENITEM& sInvenItem = m_pPage->GetItem( nPosX, nPosY );
			if( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL() )
				CInnerInterface::GetInstance().SHOW_ITEM_INFO( sInvenItem.sItemCustom, FALSE, FALSE, FALSE, sInvenItem.wPosX, sInvenItem.wPosY );

			if( dwMsg & UIMSG_LB_UP )
				GLGaeaClient::GetInstance().GetCharacter()->ReqInvenTo( nPosX, nPosY );
				//m_pItemRebuildWindow->SetOption ( FALSE );
		}
		break;

	//case REBUILDINVENTORY_MONEY_BUTTON:
	//	if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
	//	{
	//		if( GLGaeaClient::GetInstance().GetCharacter()->ValidRebuildOpen() )
	//			DoModal( ID2GAMEINTEXT("REBUILD_MONEY_INPUT"), MODAL_INPUT, EDITBOX_MONEY, MODAL_ITEMREBUILD_MONEY );
	//	}
	//	break;

	case INVENTORY_PAGE_BUTTON0:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				INVENTORY();
			}
		}
		break;

	case ET_CONTROL_BUTTON:
		if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
		{
			//SetOption( FALSE );
			CInnerInterface::GetInstance().CloseItemRebuildWindow();
		}
		break;
	}	

	CUIWindowEx::TranslateUIMessage( ControlID, dwMsg );
}

void CRebuildInventoryWindow::INVENTORY()
{
	for ( int i = 0; i < 1 ; i++ )
	{
		m_pPageButton[i]->SetFlip ( FALSE );
		m_pPageButton[i]->SetOneLineText( (char*)ID2GAMEWORD ( "NEW_INVENTORY_BUTTON", i ));
	}
	m_pPageButton[0]->SetOneLineText( (char*)ID2GAMEWORD ( "NEW_INVENTORY_BUTTON", 0 ) , NS_UITEXTCOLOR::BLACK );
	m_pPageButton[0]->SetFlip ( TRUE );
	m_pPage->SetVisibleSingle(TRUE);
	//m_pPage2->SetVisibleSingle(FALSE);

	CInnerInterface::GetInstance().Setstate(0);
}

HRESULT CRebuildInventoryWindow::RestoreDeviceObjects( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = CUIWindowEx::RestoreDeviceObjects( pd3dDevice );
	if( FAILED( hr ) )
		return hr;

	const LONG lResolution = CInnerInterface::GetInstance().GetResolution();
	WORD X_RES = HIWORD( lResolution );
	WORD Y_RES = LOWORD( lResolution );

	const UIRECT& rcWindow = GetGlobalPos();

	D3DXVECTOR2 vPos;
	vPos.x = ( (X_RES) / 2.0f );
	vPos.y = ( Y_RES - rcWindow.sizeY ) / 2.0f;
	SetGlobalPos( vPos );

	return S_OK;
}

VOID CRebuildInventoryWindow::SetOneViewSlot( const INT& nONE_VIEW_SLOT )
{
	CUIControl TempControl;
	TempControl.Create( 1, "REBUILDINVENTORYSLOT_ITEM_SLOT0" );

	CUIControl TempControl2;
	TempControl2.Create( 2, "REBUILDINVENTORYSLOT_ITEM_SLOT1" );

	const UIRECT& rcTempGlobalPos = TempControl.GetGlobalPos();
	D3DXVECTOR2 vONE_SLOT_SIZE( rcTempGlobalPos.sizeX, rcTempGlobalPos.sizeY );

	const UIRECT& rcTempGlobalPos2 = TempControl2.GetGlobalPos();

	const FLOAT fSlotGap = rcTempGlobalPos2.top - rcTempGlobalPos.bottom;

	const FLOAT fOldSizeY = ( vONE_SLOT_SIZE.y + fSlotGap ) * m_nONE_VIEW_SLOT;
	const FLOAT fNewSizeY = ( vONE_SLOT_SIZE.y + fSlotGap ) * nONE_VIEW_SLOT;
    const FLOAT fDIFF_SIZE_Y = fNewSizeY - fOldSizeY;

	const UIRECT& rcGlobalPos = GetGlobalPos();
	UIRECT rcNewGlobalPos( rcGlobalPos.left, rcGlobalPos.top, rcGlobalPos.sizeX, rcGlobalPos.sizeY + fDIFF_SIZE_Y );

	WORD wFlagAlignBACK = GetAlignFlag ();
	SetAlignFlag ( UI_FLAG_YSIZE );
	
	//AlignSubControl ( rcGlobalPos, rcNewGlobalPos );
	//SetGlobalPos ( rcNewGlobalPos );
	
	SetAlignFlag ( wFlagAlignBACK );

	m_pPage->SetOneViewSlot( nONE_VIEW_SLOT );
	m_nONE_VIEW_SLOT = nONE_VIEW_SLOT;

}