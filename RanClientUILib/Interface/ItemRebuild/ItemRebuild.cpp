#include "StdAfx.h"
#include "ItemRebuild.h"

#include "D3DFont.h"
#include "../ItemImage.h"
#include "../ItemMove.h"
#include "../BasicTextButton.h"
#include "../UITextControl.h"
#include "../GameTextControl.h"
#include "../InnerInterface.h"
#include "GLItemMan.h"
#include "GLGaeaClient.h"
#include "../EngineUIlib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../RanClientUILib/Interface/ModalWindow.h"
#include "../RanClientUILib/Interface/ModalCallerID.h"

#include "ItemRebuildOption.h"	//sealed card
#include "../BasicLineBox.h"

#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemRebuild::CItemRebuild()	
	: m_pItemImage( NULL )
	, m_pSealImage( NULL )
	, m_pCostTextBoxStatic( NULL )
	, m_pCostTextBox( NULL )
	, m_pMoneyTextBox( NULL )
	, m_pOkButton(NULL)
{
	//sealed card
	for ( int i = 0; i < 4; i++ )
		m_pOption[i] = NULL;	
	for ( int i = 0; i < 2; i++ ) 
		m_nSelOption[i] = -1;
}

CItemRebuild::~CItemRebuild()
{
}

CItemRebuildOption* CItemRebuild::CreateCheckBox ( CString strKeyword, UIGUID ControlID ) //sealed card
{
	CItemRebuildOption* pCheck = new CItemRebuildOption;
	pCheck->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pCheck->CreateSubControl();
	pCheck->SetVisibleSingle(FALSE);
	RegisterControl ( pCheck );

	return pCheck;
}

VOID CItemRebuild::CreateSubControl()
{
	//sealed card
	CBasicLineBox* pLineBox = new CBasicLineBox;
	pLineBox->CreateSub ( this, "BASIC_LINE_BOX_WAITSERVER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxWaitServer ( "ITEM_REBUILD_LINE_BOX" );
	RegisterControl ( pLineBox );

	{
		m_pItemImage = new CItemImage;
		m_pItemImage->CreateSub( this, "ITEM_REBUILD_ITEM_SLOT", UI_FLAG_DEFAULT, ITEM_REBUILD_ITEM_SLOT );
		m_pItemImage->CreateSubControl();
		RegisterControl( m_pItemImage );
	}
	
	{
		m_pSealImage = new CItemImage;
		m_pSealImage->CreateSub( this, "ITEM_REBUILD_SEALED_CARD_SLOT", UI_FLAG_DEFAULT, ITEM_REBUILD_SEALED_CARD_SLOT );
		m_pSealImage->CreateSubControl();
		RegisterControl( m_pSealImage );
	}

	{
		CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
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

	{
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
	}

	CString strKeyword[4] = //sealed card
	{
		"ITEM_REBUILD_ITEM_OPTION00",
		"ITEM_REBUILD_ITEM_OPTION01",
		"ITEM_REBUILD_ITEM_OPTION02",
		"ITEM_REBUILD_ITEM_OPTION03"
	};

	for(int i = 0; i < 4; i++ )
	{
		m_pOption[i] = CreateCheckBox(  strKeyword[i].GetString(), 
										ITEM_REBUILD_ITEM_OPTION00 + i
									 );
	}
}

VOID CItemRebuild::Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_ITEM();
	if( m_pItemImage )
	{
		if( sItemCustom.sNativeID == NATIVEID_NULL() )
		{
			m_pItemImage->ResetItem();

			for(int i = 0; i < 4; i++)
			{
				m_pOption[i]->ClearText();
				m_pOption[i]->SetVisibleSingle(FALSE);
			}
		}
		else
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemCustom.sNativeID );
			if( pItem )
				m_pItemImage->SetItem( pItem->sBasicOp.sICONID, pItem->GetInventoryFile() );
			else
				m_pItemImage->ResetItem();

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

				bool bSkip(false);
				if ( i != 0 )
				{
					for(int j = 0; j < i; j++ )
					{
						if ( emOpt[i] == emOpt[j] )
						{
							bSkip = true;
							break;
						}
					}
				}

				if ( bSkip )
				{
					m_pOption[i]->ClearText();
					m_pOption[i]->SetVisibleSingle( FALSE );
					continue;
				}
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
						if ( nRandOptType == EMR_OPT_HMS_INC || 
							 nRandOptType == EMR_OPT_HP_INC  || 
							 nRandOptType == EMR_OPT_MP_INC  || 
							 nRandOptType == EMR_OPT_SP_INC	 )
						{
							fVal[i] = (fVal[i]*100.0f);
						}

						if( fVal[i] > 0.0f) 
							strDescText += _T('+');

						if( sItemCustom.IsPerRandOpt( nRandOptType ) )
						{
							strDescText.AppendFormat( "%.2f", fVal[i] );
							strDescText += _T('%');
						}
						else
							strDescText.AppendFormat( "%d", int(fVal[i] ));

						m_pOption[i]->ClearText();
						m_pOption[i]->SetTextTitle( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
						m_pOption[i]->SetVisibleSingle( TRUE );
					}
				}
				else
				{
					m_pOption[i]->ClearText();
					m_pOption[i]->SetVisibleSingle( FALSE );
				}
			}
		}
	}

	SITEMCUSTOM sItemCustom2 = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_SEAL();
	if( m_pSealImage )
	{
		if( sItemCustom2.sNativeID == NATIVEID_NULL() )
			m_pSealImage->ResetItem();
		else
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem( sItemCustom2.sNativeID );
			if( pItem )
				m_pSealImage->SetItem( pItem->sBasicOp.sICONID, pItem->GetInventoryFile() );
			else
				m_pSealImage->ResetItem();
		}
	}

	LONGLONG i64RebuildCost = GLGaeaClient::GetInstance().GetCharacter()->GetRebuildInput();

	if( i64RebuildCost > 0 || sItemCustom.sNativeID != NATIVEID_NULL() ) 
		m_pOkButton->SetVisibleSingle( TRUE );
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
			if( !pItemMove )
			{
				GASSERT( 0 && "CItemRebuild::TranslateUIMessage, pItemMove == NULL" );
				break;
			}

			SNATIVEID sItem = pItemMove->GetItem();
			if( sItem != NATIVEID_NULL() )
			{
				const UIRECT& rcSlotPos = m_pItemImage->GetGlobalPos();
				pItemMove->SetGlobalPos( rcSlotPos );
				CInnerInterface::GetInstance().SetSnapItem();
				// refresh option seal card
				SetOption( FALSE );
			}

			if( dwMsg & UIMSG_LB_UP )
				GLGaeaClient::GetInstance().GetCharacter()->ReqRebuildMoveItem();

			SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_ITEM();
			if( sItemCustom.sNativeID != NATIVEID_NULL() )
				CInnerInterface::GetInstance().SHOW_ITEM_INFO( sItemCustom, FALSE, FALSE, FALSE, 0, 0 );
		}
		break;

	case ITEM_REBUILD_SEALED_CARD_SLOT:
		if( CHECK_MOUSE_IN( dwMsg ) )
		{
			CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove();
			if( !pItemMove )
			{
				GASSERT( 0 && "CItemRebuild::TranslateUIMessage, pItemMove == NULL" );
				break;
			}

			SNATIVEID sItem = pItemMove->GetItem();
			if( sItem != NATIVEID_NULL() )
			{
				const UIRECT& rcSlotPos = m_pSealImage->GetGlobalPos();
				pItemMove->SetGlobalPos( rcSlotPos );
				CInnerInterface::GetInstance().SetSnapItem();
			}
			
			if( dwMsg & UIMSG_LB_UP )
				GLGaeaClient::GetInstance().GetCharacter()->ReqRebuildMoveSeal();

			SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_SEAL();
			if( sItemCustom.sNativeID != NATIVEID_NULL() )
				CInnerInterface::GetInstance().SHOW_ITEM_INFO( sItemCustom, FALSE, FALSE, FALSE, 0, 0 );
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

				SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_SEAL();
				if( !sItemCustom.sNativeID.IsValidNativeID() ) 
					break;

				if ( !m_pOption[nIndex]->IsVisible() ) 
					break;

				if ( m_pOption[nIndex]->IsChecked() )
					break;

				WORD wType = GLGaeaClient::GetInstance().GetCharacter()->GET_SEAL_TYE();
				for( int i = 0; i < wType; i++ )
				{
					if ( m_nSelOption[i] != -1 )
						continue;

					m_pOption[nIndex]->SetCheck();
					m_nSelOption[i] = nIndex;

					break;
				}

				bool bOk(false);
				if ( wType == 1 ) {
					if ( m_nSelOption[0] != -1 )
						bOk = true;
				} else if ( wType == 2 ) {
					if ( m_nSelOption[0] != -1 && m_nSelOption[1] != -1 )
						bOk = true;
				}
				
				SITEMCUSTOM sItemCustom2 = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_ITEM();
				EMRANDOM_OPT emOpt[4] = 
				{
					sItemCustom2.GETOptTYPE1()
					, sItemCustom2.GETOptTYPE2()
					, sItemCustom2.GETOptTYPE3()
					, sItemCustom2.GETOptTYPE4()
				};

				/*float fVal[4] =
				{
					sItemCustom2.GETOptVALUE1()
					, sItemCustom2.GETOptVALUE2()
					, sItemCustom2.GETOptVALUE3()
					, sItemCustom2.GETOptVALUE4()
				};*/

				short cval[4] = 
				{
					sItemCustom2.nOptVALUE1
					, sItemCustom2.nOptVALUE2
					, sItemCustom2.nOptVALUE3
					, sItemCustom2.nOptVALUE4
				};

				if ( wType == 1 )
				{
					m_SealData01.emOpt = emOpt[m_nSelOption[0]];
					//m_SealData01.fValue = fVal[m_nSelOption[0]];
					m_SealData01.cDataValue = cval[m_nSelOption[0]];
					m_SealData01.nOption = 0;
				}

				if ( wType == 2 )
				{
					m_SealData01.emOpt = emOpt[m_nSelOption[0]];
					//m_SealData01.fValue = fVal[m_nSelOption[0]];
					m_SealData01.cDataValue = cval[m_nSelOption[0]];
					m_SealData01.nOption = 0;

					m_SealData02.emOpt = emOpt[m_nSelOption[1]];
					//m_SealData02.fValue = fVal[m_nSelOption[1]];
					m_SealData02.cDataValue = cval[m_nSelOption[1]];
					m_SealData02.nOption = 1;
				}

				if ( bOk )
				{
					for( int i = 0; i < 4; i++ )
					{
						if ( m_pOption[i]->IsChecked() )
							continue;

						m_pOption[i]->ManageOption( FALSE );
					}
				}
			}
		}
		break;

	case ITEM_REBUILD_OK_BUTTON:
		if( CHECK_KEYFOCUSED( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
		{
			SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_REBUILD_SEAL();
			if( sItemCustom.sNativeID.IsValidNativeID() ) 
			{
				bool bOk(false);
				WORD wType = GLGaeaClient::GetInstance().GetCharacter()->GET_SEAL_TYE();
				if ( wType == 1 )
				{
					if ( m_nSelOption[0] == -1 ) {
						CInnerInterface::GetInstance().PrintConsoleText( "Select one option first then Try again." );
						bOk = true;
					}
				} else if ( wType == 2 ) {
					int nSelect = 0;
					if ( m_nSelOption[0] == -1 )
						nSelect++;
					if ( m_nSelOption[1] == -1 )
						nSelect++;

					if ( nSelect == 1 ) {
						CInnerInterface::GetInstance().PrintConsoleText( "Select one option first then Try again." );
						bOk = true;
					} else if ( nSelect ==2 ) {
						CInnerInterface::GetInstance().PrintConsoleText( "Select two option first then Try again." );
						bOk = true;
					}
				}

				if ( bOk ) break;
			}

			DoModal( ID2GAMEINTEXT("ITEM_REBUILD_OKQUESTION"), MODAL_QUESTION, YESNO, MODAL_ITEMREBUILD_OKQUESTION );
			SetMessageEx( dwMsg &= ~UIMSG_KEY_FOCUSED ); 
		}
		break;

	case ITEM_REBUILD_CANCEL_BUTTON:
		if( CHECK_KEYFOCUSED( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
		{
			SetOption( FALSE );
			CInnerInterface::GetInstance().CloseItemRebuildWindow();
		}
		break;

	case ET_CONTROL_BUTTON:
		if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
		{
			SetOption( FALSE );
			CInnerInterface::GetInstance().CloseItemRebuildWindow();
		}
		break;
	}

	CUIWindowEx::TranslateUIMessage( ControlID, dwMsg );
}

void CItemRebuild::SetOption( BOOL bOPT )
{
	for(int i = 0; i < 4; i++ )
	{
		if ( m_pOption[i] )
			m_pOption[i]->ManageOption( bOPT );
	}

	for(int i = 0; i < 2; i++ )
	{
		if ( m_nSelOption[i] > -1 && m_nSelOption[i] < 4 )
			m_nSelOption[i] = -1;
	}

	m_SealData01.RESET();
	m_SealData02.RESET();

}