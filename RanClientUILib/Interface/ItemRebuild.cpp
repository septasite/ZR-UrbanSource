#include "StdAfx.h"
#include "ItemRebuild.h"

#include "D3DFont.h"
#include "ItemImage.h"
#include "ItemMove.h"
#include "BasicTextButton.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "GLItemMan.h"
#include "GLGaeaClient.h"
#include "BasicLineBox.h"

#include "../EngineUIlib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../RanClientUILib/Interface/ModalWindow.h"
#include "../RanClientUILib/Interface/ModalCallerID.h"

#include "ItemRebuildOption.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//--------------------------------------------------------------------
// ItemRebuild
//--------------------------------------------------------------------
CItemRebuild::CItemRebuild()	// ITEMREBUILD_MARK
	: m_pItemImage( NULL )
	, m_pCostTextBoxStatic( NULL )
	, m_pCostTextBox( NULL )
	, m_pMoneyTextBox( NULL )
	, m_pOkButton( NULL )
	, m_nOption( -2 )
	, m_bSEAL( false )
	, m_pWrap( NULL )
{
	for(int i = 0; i < 4; i++ )
	{
		m_pItemOption[i] = NULL;
	}
}

CItemRebuild::~CItemRebuild()
{
}

VOID CItemRebuild::CreateSubControl()
{
	CBasicLineBox* pLineBox = new CBasicLineBox;
	pLineBox->CreateSub ( this, "BASIC_LINE_BOX_WAITSERVER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxWaitServer ( "ITEM_REBUILD_LINE_BOX" );
	RegisterControl ( pLineBox );

	m_pItemImage = new CItemImage;
	m_pItemImage->CreateSub( this, "ITEM_REBUILD_ITEM_SLOT", UI_FLAG_DEFAULT, ITEM_REBUILD_ITEM_SLOT );
	m_pItemImage->CreateSubControl();
	RegisterControl( m_pItemImage );

	m_pSealedCardImage = new CItemImage;
	m_pSealedCardImage->CreateSub( this, "ITEM_REBUILD_SEALED_CARD_SLOT", UI_FLAG_DEFAULT, ITEM_REBUILD_SEALED_CARD_SLOT );
	m_pSealedCardImage->CreateSubControl();
	RegisterControl( m_pSealedCardImage );

	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT, 9 );
	m_pCostTextBoxStatic = CreateStaticControl( "ITEM_REBUILD_COAST_TEXT_STATIC", pFont, NS_UITEXTCOLOR::SILVER, TEXT_ALIGN_LEFT );
	m_pCostTextBoxStatic->AddText( ID2GAMEINTEXT( "ITEM_REBUILD_COST" ), NS_UITEXTCOLOR::SILVER );

	// 개조비용 : 0
	{
		m_pWrap = new CUIControl;
		m_pWrap->CreateSub( this, "ITEM_REBUILD_ITEM_WRAP" );
		m_pWrap->SetVisibleSingle( FALSE );
		RegisterControl( m_pWrap );
	}
	{
		CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT, 9 );
		m_pCostTextBoxStatic = CreateStaticControl( "ITEM_REBUILD_COAST_TEXT_STATIC", pFont, NS_UITEXTCOLOR::SILVER, TEXT_ALIGN_LEFT );
		m_pCostTextBoxStatic->AddText( ID2GAMEINTEXT( "ITEM_REBUILD_COST" ), NS_UITEXTCOLOR::SILVER );

			m_pCostTextBox = CreateStaticControl( "ITEM_REBUILD_COAST_TEXT", pFont, NS_UITEXTCOLOR::SILVER, TEXT_ALIGN_LEFT );
	}

	{
		CUIControl* pControl = CreateControl( "ITEM_REBUILD_MONEY_BACK" );
		pControl->SetAlignFlag( UI_FLAG_BOTTOM );

		pControl = CreateControl( "ITEM_REBUILD_MONEY_IMAGE" );
		pControl->SetAlignFlag( UI_FLAG_BOTTOM );

		CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );
		m_pMoneyTextBox = CreateStaticControl( "ITEM_REBUILD_MONEY_TEXT", pFont, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
		m_pMoneyTextBox->SetAlignFlag( UI_FLAG_BOTTOM );
	}

	m_pOkButton = new CBasicTextButton;
	m_pOkButton->CreateSub( this, "BASIC_TEXT_BUTTON14", UI_FLAG_DEFAULT, ITEM_REBUILD_OK_BUTTON );
	m_pOkButton->CreateBaseButton( "ITEM_REBUILD_OK_BUTTON", CBasicTextButton::SIZE14,
								CBasicButton::CLICK_FLIP, ID2GAMEINTEXT( "ITEM_REBUILD_OK" ) );
	m_pOkButton->SetShortcutKey( DIK_RETURN, DIK_NUMPADENTER );
	m_pOkButton->SetVisibleSingle( FALSE );
	RegisterControl( m_pOkButton );

	CBasicTextButton * pButton = new CBasicTextButton;
	pButton->CreateSub( this, "BASIC_TEXT_BUTTON14", UI_FLAG_DEFAULT, ITEM_REBUILD_CANCEL_BUTTON );
	pButton->CreateBaseButton( "ITEM_REBUILD_CANCEL_BUTTON", CBasicTextButton::SIZE14,
								CBasicButton::CLICK_FLIP, ID2GAMEINTEXT( "ITEM_REBUILD_CANCEL" ) );
	pButton->SetShortcutKey( DIK_ESCAPE );
	RegisterControl( pButton );

	CString strKeyword[4] = 
	{
		"ITEM_REBUILD_ITEM_OPTION00",
		"ITEM_REBUILD_ITEM_OPTION01",
		"ITEM_REBUILD_ITEM_OPTION02",
		"ITEM_REBUILD_ITEM_OPTION03"
	};

	for(int i = 0; i < 4; i++ )
	{
		m_pItemOption[i] = CreateCheckBox( strKeyword[i].GetString(), ITEM_REBUILD_ITEM_OPTION00 + i );
	}
}

VOID CItemRebuild::Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_pWrap->SetVisibleSingle( FALSE );

	SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_ITEM();
	if( m_pItemImage )
	{
		if( sItemCustom.sNativeID == NATIVEID_NULL() )
		{
			m_pItemImage->ResetItem();

			for(int i = 0; i < 4; i++)
			{
				m_pItemOption[i]->ClearText();
				m_pItemOption[i]->SetVisibleSingle(FALSE);
			}
		}
		else
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemCustom.sNativeID );
			if( pItem )
				m_pItemImage->SetItem( pItem->sBasicOp.sICONID, pItem->GetInventoryFile() );
			else
				m_pItemImage->ResetItem();
			if ( sItemCustom.IsWrap() && sItemCustom.sNativeID.IsValidNativeID() )
				m_pWrap->SetVisibleSingle( TRUE );

			for(int i = 0; i < 4; i++)
			{
				if ( !sItemCustom.IsSetRandOpt() ) break;

				CString strDescText;
				EMRANDOM_OPT emOpt[4] = 
				{
					  sItemCustom.GETOptTYPE1()
					, sItemCustom.GETOptTYPE2()
					, sItemCustom.GETOptTYPE3()
					, sItemCustom.GETOptTYPE4()
				};

				INT nRandOptType = emOpt[i];
				if( (EMR_OPT_NULL < nRandOptType) && (nRandOptType < EMR_OPT_SIZE) )
				{
					float fVal[4] =
					{
						  sItemCustom.GETOptVALUE1()
						, sItemCustom.GETOptVALUE2()
						, sItemCustom.GETOptVALUE3()
						, sItemCustom.GETOptVALUE4()
					};

					strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType ) );
					if( fVal[i] != 0.0f )
					{
						if( fVal[i] > 0.0f) strDescText += _T('+');

						strDescText.AppendFormat( "%2.2f", fVal[i] );
						if( sItemCustom.IsPerRandOpt( nRandOptType ) ) strDescText += _T('%');

						m_pItemOption[i]->ClearText();
						m_pItemOption[i]->SetTextTitle( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
						m_pItemOption[i]->SetVisibleSingle( TRUE );
					}
				}
				else
				{
					m_pItemOption[i]->ClearText();
					m_pItemOption[i]->SetVisibleSingle( FALSE );
				}
			}
		}
	}

	//Sealed Card
	SITEMCUSTOM sItemCustom_Seal = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_SEALED_CARD();
	if ( m_pSealedCardImage )
	{
		if ( sItemCustom_Seal.sNativeID == NATIVEID_NULL() )
		{
			m_pSealedCardImage->ResetItem();

			for(int i = 0; i < 4; i++)
			{
				if ( !m_pItemOption[i]->IsVisible() ) continue;
				m_pItemOption[i]->HideCheckOption();
			}
		}
		else
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemCustom_Seal.sNativeID );
			if( pItem )
				m_pSealedCardImage->SetItem( pItem->sBasicOp.sICONID, pItem->GetInventoryFile() );
			else
				m_pSealedCardImage->ResetItem();

			if ( m_bSEAL )
			{
				for(int i = 0; i < 4; i++)
				{
					if ( !m_pItemOption[i]->IsVisible() ) continue;
					m_pItemOption[i]->ShowCheckOption();
				}
				m_bSEAL = false;
			}
		}
	}

	LONGLONG i64RebuildCost = GLGaeaClient::GetInstance().GetCharacter()->GetRebuildInput();

	if( i64RebuildCost > 0 || sItemCustom.sNativeID != NATIVEID_NULL() ) 
	{
		if ( sItemCustom_Seal.sNativeID != NATIVEID_NULL())
		{
			if ( m_nOption != -2 )
				m_pOkButton->SetVisibleSingle( TRUE );
			else
				m_pOkButton->SetVisibleSingle( FALSE );
		}
		else
		{
			m_pOkButton->SetVisibleSingle( TRUE );
		}
	}
	else
		m_pOkButton->SetVisibleSingle( FALSE );

	if( m_pCostTextBox && m_pMoneyTextBox )
	{
		CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT( i64RebuildCost, 3, "," );
		m_pCostTextBox->SetOneLineText( strTemp );
		m_pMoneyTextBox->SetOneLineText( strTemp );
	}
	
}

VOID CItemRebuild::TranslateUIMessage( UIGUID ControlID, DWORD dwMsg )
{
	switch( ControlID )
	{
	case ITEM_REBUILD_ITEM_SLOT:
		if( CHECK_MOUSE_IN( dwMsg ) )
		{
			CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove();
			if( !pItemMove ) break;

			SNATIVEID sItem = pItemMove->GetItem();
			if( sItem != NATIVEID_NULL() )
			{
				const UIRECT& rcSlotPos = m_pItemImage->GetGlobalPos();
				pItemMove->SetGlobalPos( rcSlotPos );
				CInnerInterface::GetInstance().SetSnapItem();
			}

			if( dwMsg & UIMSG_LB_UP )
			{
				SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_SEALED_CARD(); 
				if( sItemCustom.sNativeID.IsValidNativeID() ) 
				{
					CInnerInterface::GetInstance().PrintConsoleText( "Close the window first before changing the item." );
					return;
				}
				//SetOption( FALSE );
				GLGaeaClient::GetInstance().GetCharacter()->ReqRebuildMoveItem();
				SetOption( FALSE );
			}

			SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_ITEM();
			if( sItemCustom.sNativeID != NATIVEID_NULL() )
			{
				CInnerInterface::GetInstance().SHOW_ITEM_INFO( sItemCustom, FALSE, FALSE, FALSE, 0, 0 );

				if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
				{
					if ( dwMsg & UIMSG_LB_UP )
					{
						CInnerInterface::GetInstance().PreviewItem( sItemCustom );
						return;
					}
				}
			}
		}
		break;

	case ITEM_REBUILD_OK_BUTTON:
		if( CHECK_KEYFOCUSED( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
		{
			DoModal( ID2GAMEINTEXT("ITEM_REBUILD_OKQUESTION"), MODAL_QUESTION, YESNO, MODAL_ITEMREBUILD_OKQUESTION );
			SetMessageEx( dwMsg &= ~UIMSG_KEY_FOCUSED ); 
		}
		break;

	case ITEM_REBUILD_CANCEL_BUTTON:
		if( CHECK_KEYFOCUSED( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
		{
			CInnerInterface::GetInstance().CloseItemRebuildWindow();
			m_nOption = -2;
			ResetOption();
		}
		break;

	case ET_CONTROL_BUTTON:
		if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
		{
			CInnerInterface::GetInstance().CloseItemRebuildWindow();
			m_nOption = -2;
			ResetOption();
		}
		break;

	case ITEM_REBUILD_SEALED_CARD_SLOT:
		if( CHECK_MOUSE_IN( dwMsg ) )
		{
			CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove();
			if( !pItemMove ) break;

			SNATIVEID sItem = pItemMove->GetItem();
			if( sItem != NATIVEID_NULL() )
			{
				const UIRECT& rcSlotPos = m_pSealedCardImage->GetGlobalPos();
				pItemMove->SetGlobalPos( rcSlotPos );
				CInnerInterface::GetInstance().SetSnapItem();
			}

			if( dwMsg & UIMSG_LB_UP )
			{
				GLGaeaClient::GetInstance().GetCharacter()->ReqRebuildMoveSealedCard();
				m_bSEAL = true;
			}

			SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_SEALED_CARD();
			if( sItemCustom.sNativeID != NATIVEID_NULL() )
			{
				CInnerInterface::GetInstance().SHOW_ITEM_INFO( sItemCustom, FALSE, FALSE, FALSE, 0, 0 );
			}
		}
		break;
	case ITEM_REBUILD_ITEM_OPTION00:
	case ITEM_REBUILD_ITEM_OPTION01:
	case ITEM_REBUILD_ITEM_OPTION02:
	case ITEM_REBUILD_ITEM_OPTION03:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
			{
				int nIndex = ControlID - ITEM_REBUILD_ITEM_OPTION00;
				m_pItemOption[nIndex]->SetCheck();
				m_nOption = nIndex;
				
				for(int i = 0; i < 4; i++)
				{
					if ( !m_pItemOption[i]->IsVisible() ) continue;
					if ( i == m_nOption ) continue;
					m_pItemOption[i]->HideCheckOption();
				}

				if ( m_nOption != -2 )
				{
					GLGaeaClient::GetInstance().GetCharacter()->ReqRebuildSetOption( m_nOption );
				}
			}
		}
		break;
	}

	CUIWindowEx::TranslateUIMessage( ControlID, dwMsg );
}

CItemRebuildOption* CItemRebuild::CreateCheckBox ( CString strKeyword, UIGUID ControlID )
{
	CItemRebuildOption* pCheck = new CItemRebuildOption;
	pCheck->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pCheck->CreateSubControl();
	pCheck->SetVisibleSingle(FALSE);
	RegisterControl ( pCheck );

	return pCheck;
}

void CItemRebuild::ResetOption()
{
	for(int i = 0; i < 4; i++)
	{
		if ( !m_pItemOption[i]->IsVisible() ) 
			continue;

		m_pItemOption[i]->HideCheckOption();
	}
}