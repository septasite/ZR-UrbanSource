#include "StdAfx.h"

#include "ItemShopWindow.h"
#include "ItemShopPage.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "InnerInterface.h"
#include "ModalCallerID.h"
#include "BasicLineBox.h"
#include "BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "ModalWindow.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "BasicTextButton.h"
#include "ItemShopWindowMenu.h"
#include "d3dfont.h"
#include "OuterInterface.h"

#include "BasicComboBox.h"
#include "BasicComboBoxRollOver.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
const	int	CItemShopWindow::nOUTOFRANGE = -1;
CItemShopWindow::CItemShopWindow () :
	  m_pPage ( NULL )
	, m_pMenu( NULL )
	, m_RollOverID ( NO_ID )
	, m_pComboBoxOpen ( NULL )
	, m_pComboRollOver( NULL )
	, m_nPageIndex ( nOUTOFRANGE )
{
}

CItemShopWindow::~CItemShopWindow ()
{
}
CBasicTextButton*  CItemShopWindow::CreateTextButton ( char* szButton, UIGUID ControlID, char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE22;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON22", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText );
	RegisterControl ( pTextButton );

	return pTextButton;
}
CBasicTextBox* CItemShopWindow::CreateStaticControl ( const char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}
void CItemShopWindow::CreateSubControl ()
{	
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	{
		CBasicLineBoxEx* m_pLineBoxBottomWhite1 = new CBasicLineBoxEx;
		m_pLineBoxBottomWhite1->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBoxBottomWhite1->CreateBaseBoxDialogueBlackBack ( "ITEMSHOP_LINEBOX_01_W" );
		m_pLineBoxBottomWhite1->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBoxBottomWhite1 );
			
		CBasicLineBoxEx* m_pLineBoxBottomWhite3 = new CBasicLineBoxEx;
		m_pLineBoxBottomWhite3->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBoxBottomWhite3->CreateBaseBoxDialogueBlackBack ( "ITEMSHOP_LINEBOX_03_W" );
		m_pLineBoxBottomWhite3->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBoxBottomWhite3 );
	}
		m_pPPoints = CreateStaticControl ( "ITEMSHOP_WINDOW_PPOINTS", pFont, TEXT_ALIGN_LEFT );
		m_pVPoints = CreateStaticControl ( "ITEMSHOP_WINDOW_VPOINTS", pFont, TEXT_ALIGN_LEFT );
	{
		CItemShopWindowMenu* pMenu = new CItemShopWindowMenu;
		pMenu->CreateSub ( this, "ITEMSHOP_MENU" );
		pMenu->CreateSubControl();
		pMenu->SetVisibleSingle(TRUE);
		RegisterControl ( pMenu );
		m_pMenu = pMenu;
	}

	{
		CItemShopPage* pItemShopPage = new CItemShopPage;
		pItemShopPage->CreateSub ( this, "ITEMSHOP_PAGE", UI_FLAG_DEFAULT, ITEMSHOP_PAGE );
		pItemShopPage->CreateSubControl ();	
		RegisterControl ( pItemShopPage );
		m_pPage = pItemShopPage;
	}

	{
		CBasicComboBox *pComboBox = new CBasicComboBox;
		pComboBox->CreateSub ( this, "BASIC_COMBOBOX", UI_FLAG_XSIZE, ITEMSHOPCURRENCY_COMBO_OPEN );
		pComboBox->CreateBaseComboBox ( "ITEMSHOPCURRENCY_COMBO_OPEN" );			
		RegisterControl ( pComboBox );
		m_pComboBoxOpen = pComboBox;
	}

	{
		CBasicComboBoxRollOver *pComboBoxRollOver = new CBasicComboBoxRollOver;
		pComboBoxRollOver->CreateSub ( this, "BASIC_COMBOBOX_ROLLOVER", UI_FLAG_XSIZE | UI_FLAG_YSIZE, ITEMSHOPCURRENCY_COMBO_ROLLOVER );
		pComboBoxRollOver->CreateBaseComboBoxRollOver ( "ITEMSHOPCURRENCY_COMBO_ROLLOVER", FALSE );			
		pComboBoxRollOver->SetVisibleSingle ( FALSE );
		RegisterControl ( pComboBoxRollOver );
		m_pComboRollOver = pComboBoxRollOver;
	}

	//InitItemShop (0,0);
}


void CItemShopWindow::InitItemShop ( WORD wType , WORD wCurrency )
{
	m_pPage->UnLoadItemPage ();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	m_pPage->LoadItemPage ( wType , wCurrency );
	m_pMenu->SetButtonOn( wType );

}

void CItemShopWindow::ClearItemShop()
{ 
	m_pPage->UnLoadItemPage ();
}
void CItemShopWindow::Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl )
{

	const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();	
	SetData ( sCharData );
	
	WORD wType = m_pMenu->GetType();
	WORD wCurrency = GetPageCurrency();
	if ( wType != m_wType )
	{
		InitItemShop( wType , wCurrency );
		m_wType = wType;
		m_nPageCurrency = wCurrency;
		m_pMenu->SetButtonOn( wType );
	}

	if ( m_RollOverID == NO_ID )
	{
		CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	}else{
		ResetMessageEx ();

		CUIControl::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		CUIControl* pControl = m_ControlContainer.FindControl ( m_RollOverID );
		if ( !pControl )
		{
			GASSERT ( 0 && "심각한 오류, 노드가 널입니다." );
			return ;
		}

		pControl->Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		DWORD dwControlMsg = pControl->GetMessageEx ();
		NS_UIDEBUGSET::BlockBegin ();
		if ( dwControlMsg ) TranslateUIMessage ( m_RollOverID, dwControlMsg );
		NS_UIDEBUGSET::BlockEnd ();

		//	스크롤바에 관계된 메시지가 아니고		
		if ( !(dwControlMsg & UI_MSG_COMBOBOX_ROLLOVER_SCROLL) )
		{
			DWORD dwMsg = GetMessageEx ();
			if ( dwMsg & UIMSG_LB_UP )
			{
				if ( !m_bFirstLBUP )
				{
					m_RollOverID = NO_ID;
					pControl->SetVisibleSingle ( FALSE );					
				}
				m_bFirstLBUP = FALSE;
			}
		}
	}

}
void CItemShopWindow::SetData( const GLCHARLOGIC& sCharData )
{
	m_pPPoints->ClearText();
	m_pVPoints->ClearText();

	CString strText1;
	CString strText2;
	strText1.Format("Prem. Points: (%d) | GT Points: (%d)",sCharData.m_dwPPoints, sCharData.m_dwVPoints);
	m_pPPoints->SetText(strText1);
	//strText2.Format("GT. Points (%d)",sCharData.m_dwVPoints);
	//m_pVPoints->SetText(strText2);
}
void CItemShopWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle ( bVisible );

	if ( bVisible )
	{
		m_pComboRollOver->ClearText();


		CString strTemp1, strTemp2, strTemp3;

		strTemp1 = ID2GAMEWORD( "ITEM_SHOP_CURRENCY_ALL" );
		m_pComboRollOver->AddText( strTemp1 );

		m_pComboBoxOpen->SetText ( strTemp1 );

		for( int i = 0; i < 2; i++ )
		{
			strTemp2 = ID2GAMEWORD ( "ITEM_SHOP_CURRENCY_TYPE", i );
			m_pComboRollOver->AddText ( strTemp2 );	
		}
	}
}
void CItemShopWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	
	if ( ET_CONTROL_TITLE == ControlID || ET_CONTROL_TITLE_F == ControlID ) 
	{
		if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
		{
			CInnerInterface::GetInstance().SetDefaultPosInterface( ITEMSHOP_WINDOW );
			return;
		}		
	}
	else if ( ITEMSHOP_PAGE == ControlID )
	{
		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{
			int nPosX, nPosY;
			m_pPage->GetItemIndex ( &nPosX, &nPosY );
			if ( nPosX < 0 || nPosY < 0 ) return ;
			SINVENITEM sInvenItem = m_pPage->GetItem ( nPosX, nPosY );
			if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
			{
				CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItem.sItemCustom, FALSE, FALSE, FALSE, sInvenItem.wPosX, sInvenItem.wPosY );
			}
		}
	}else if ( ITEMSHOPCURRENCY_COMBO_OPEN == ControlID )
	{
		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{
			if ( dwMsg & UIMSG_LB_DOWN )
			{
				m_pComboRollOver->SetVisibleSingle(TRUE);
				m_RollOverID = ControlID + 1;
				m_bFirstLBUP = TRUE;
			}
		}
	}else if ( ITEMSHOPCURRENCY_COMBO_ROLLOVER == ControlID )
	{
		if ( dwMsg & UI_MSG_COMBOBOX_ROLLOVER_SCROLL )
		{				
			DWORD dwMsg = GetMessageEx ();
			dwMsg &= ~UI_MSG_COMBOBOX_ROLLOVER_SCROLL;
			ResetMessageEx ();
			AddMessageEx ( dwMsg );
		}

		if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
		{		
			int nIndex = m_pComboRollOver->GetSelectIndex ();
			if ( nIndex < 0 ) return ;
			m_nPageCurrency = nIndex;
			CString strText;
			CString strTemp =  m_pComboRollOver->GetSelectText ( nIndex );	
			m_pComboBoxOpen->SetText( strTemp );
			WORD wType = m_pMenu->GetType();
			WORD wCurrency = GetPageCurrency();
			InitItemShop( wType , wCurrency );
		}
	}
}
void CItemShopWindow::GetPosItem ( int* pnPosX, int* pnPosY )
{
	*pnPosX = m_nPosX;
	*pnPosY = m_nPosY;
}
SINVENITEM& CItemShopWindow::GetItem ( int nPosX, int nPosY )
{
	return m_pPage->GetItem ( nPosX, nPosY );
}
void CItemShopWindow::SetPosItem ( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}
int	 CItemShopWindow::GetPageIndex ()
{
	m_nPageIndex = m_wType;
	return m_nPageIndex;
}
int	 CItemShopWindow::GetPageCurrency ()
{
	m_nPageCurrency = m_nPageCurrency;
	return m_nPageCurrency;
}