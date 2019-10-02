#include "StdAfx.h"
#include "DialogueWindow.h"

#include "BasicLineBox.h"
#include "BasicLineBoxEx.h"
#include "BasicTextBoxEx.h"
#include "BasicScrollBarEx.h"
#include "BasicTextButton.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"
#include "InnerInterface.h"
#include "ModalWindow.h"
#include "GLQuestMan.h"
#include "GLQuest.h"
#include "GameTextControl.h"
#include "GLItemMan.h"
#include "ModalCallerID.h"
#include "InventoryWindow.h"
#include "MarketWindow.h"
#include "MarketPage.h"
#include "NewBuyItem.h"
#include "InterestItem.h"
#include "d3dfont.h"
#include "../EngineUiLib/GUInterface/BasicButtonText.h"

#include "../RanClientLib/NpcTalk/NpcDialogue.h"
#include "../RanClientLib/NpcTalk/NpcDialogueCase.h"
#include "../RanClientLib/NpcTalk/NpcTalkControl.h"
#include "../RanClientLib/NpcTalk/NpcTalk.h"
#include "../RanClientLib/NpcTalk/NpcTalkCondition.h"

#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUIlib/GUInterface/BasicScrollThumbFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const	int		CDialogueWindow::nSTARTLINE = 0;
const	int		CDialogueWindow::nSTARTINDEX = 1;
const	float	CDialogueWindow::fANSWER_PART_INTERVAL = 13.1f;
const	int		CDialogueWindow::nOUTOFRANGE = -1;

CDialogueWindow::CDialogueWindow ()
: m_dwRandomTime ( 0 )
, m_fRandomTime(0.0f)
, m_nPageIndex ( nOUTOFRANGE )
, m_pMoney ( NULL )
, m_pBuyButton ( NULL )
, m_pCloseButton ( NULL )
, m_pMoneyItem ( NULL )
, m_pHaveItem ( FALSE )
, MoneyTotal ( 0 )
, m_pCountSlot ( 0 )
, IsUse ( FALSE )
, IsBuy ( FALSE )
{
	memset ( m_pPageButton, 0, sizeof ( CBasicTextButton* ) * nMAXPAGENEW );
	memset ( m_pButtonImage, 0, sizeof ( CUIControl* ) * 2 );	
	memset ( m_pButtonImageSet, 0, sizeof ( CUIControl* ) * 2 );	
}

CDialogueWindow::~CDialogueWindow ()
{
}

void CDialogueWindow::CreateSubControl ()
{
	CD3DFontPar* pFont12 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 12, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont9Shadow = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII);
	const int nAlignCenterBoth = TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y ;
	
	{
		m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "RNDIALOGUE_WINDOW_WHITE", UI_FLAG_DEFAULT);	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	}

	{
		m_pBasicLineBox = new CBasicLineBoxEx;
		m_pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox->CreateBaseBoxDialogue ( "DIALOGUE_BACK_BOX" );
		m_pBasicLineBox->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox );
	}

	{
		m_pBasicLineBox1 = new CBasicLineBoxEx;
		m_pBasicLineBox1->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox1->CreateBaseBoxDialogue ( "DIALOGUE_ANSWER_BACK_BOX1" );
		m_pBasicLineBox1->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox1 );

		m_pBasicLineBox2 = new CBasicLineBoxEx;
		m_pBasicLineBox2->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox2->CreateBaseBoxDialogue ( "DIALOGUE_ANSWER_BACK_BOX2" );
		m_pBasicLineBox2->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox2 );

		m_pBasicLineBox3 = new CBasicLineBoxEx;
		m_pBasicLineBox3->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox3->CreateBaseBoxDialogue ( "DIALOGUE_ANSWER_BACK_BOX3" );
		m_pBasicLineBox3->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox3 );

		m_pBasicLineBox4 = new CBasicLineBoxEx;
		m_pBasicLineBox4->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox4->CreateBaseBoxDialogue ( "DIALOGUE_ANSWER_BACK_BOX4" );
		m_pBasicLineBox4->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox4 );

		m_pBasicLineBox5 = new CBasicLineBoxEx;
		m_pBasicLineBox5->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox5->CreateBaseBoxDialogue ( "DIALOGUE_ANSWER_BACK_BOX5" );
		m_pBasicLineBox5->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox5 );

		m_pBasicLineBox6 = new CBasicLineBoxEx;
		m_pBasicLineBox6->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox6->CreateBaseBoxDialogue ( "DIALOGUE_ANSWER_BACK_BOX6" );
		m_pBasicLineBox6->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox6 );

		m_pBasicLineBox7 = new CBasicLineBoxEx;
		m_pBasicLineBox7->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox7->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX1" );
		m_pBasicLineBox7->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox7 );

		m_pBasicLineBox8 = new CBasicLineBoxEx;
		m_pBasicLineBox8->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox8->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX2" );
		m_pBasicLineBox8->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox8 );

		m_pBasicLineBox9 = new CBasicLineBoxEx;
		m_pBasicLineBox9->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox9->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX3" );
		m_pBasicLineBox9->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox9 );

		m_pBasicLineBox10 = new CBasicLineBoxEx;
		m_pBasicLineBox10->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox10->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX4" );
		m_pBasicLineBox10->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox10 );

		m_pBasicLineBox11 = new CBasicLineBoxEx;
		m_pBasicLineBox11->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox11->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX5" );
		m_pBasicLineBox11->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox11 );

		m_pBasicLineBox12 = new CBasicLineBoxEx;
		m_pBasicLineBox12->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox12->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX6" );
		m_pBasicLineBox12->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox12 );

		m_pBasicLineBox13 = new CBasicLineBoxEx;
		m_pBasicLineBox13->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox13->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX7" );
		m_pBasicLineBox13->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox13 );

		m_pBasicLineBox14 = new CBasicLineBoxEx;
		m_pBasicLineBox14->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox14->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX8" );
		m_pBasicLineBox14->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox14 );

		m_pBasicLineBox15 = new CBasicLineBoxEx;
		m_pBasicLineBox15->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox15->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX9" );
		m_pBasicLineBox15->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox15 );

		m_pBasicLineBox16 = new CBasicLineBoxEx;
		m_pBasicLineBox16->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox16->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX10" );
		m_pBasicLineBox16->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox16 );

		m_pBasicLineBox17 = new CBasicLineBoxEx;
		m_pBasicLineBox17->CreateSub ( this, "BASIC_LINE_BOX_DIALOGUE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBasicLineBox17->CreateBaseBoxDialogue ( "NEW_MARKET_BACK_BOX11" );
		m_pBasicLineBox17->SetVisibleSingle( FALSE );
		RegisterControl ( m_pBasicLineBox17 );

		m_pPurchaseImage = new CUIControl;
		m_pPurchaseImage->CreateSub ( this, "NEW_PURCHASE_IMAGE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pPurchaseImage->SetVisibleSingle( FALSE );
		RegisterControl ( m_pPurchaseImage );


		m_pButtonImage[0] = new CUIControl;
		m_pButtonImage[0]->CreateSub ( this, "BUTTON_USE", UI_FLAG_XSIZE | UI_FLAG_YSIZE ,BUTTON_CAN_USE);
		m_pButtonImage[0]->SetTransparentOption( TRUE );
		m_pButtonImage[0]->SetVisibleSingle( FALSE );
		RegisterControl ( m_pButtonImage[0] );

		m_pButtonImageSet[0] = new CUIControl;
		m_pButtonImageSet[0]->CreateSub ( this, "BUTTON_USE_SET", UI_FLAG_XSIZE | UI_FLAG_YSIZE , BUTTON_CAN_USE_SET);
		m_pButtonImageSet[0]->SetTransparentOption( TRUE );
		m_pButtonImageSet[0]->SetVisibleSingle( FALSE );
		RegisterControl ( m_pButtonImageSet[0] );

		m_pButtonImage[1] = new CUIControl;
		m_pButtonImage[1]->CreateSub ( this, "BUTTON_BUY", UI_FLAG_XSIZE | UI_FLAG_YSIZE ,BUTTON_CAN_BUY );
		m_pButtonImage[1]->SetTransparentOption( TRUE );
		m_pButtonImage[1]->SetVisibleSingle( FALSE );
		RegisterControl ( m_pButtonImage[1] );

		m_pButtonImageSet[1] = new CUIControl;
		m_pButtonImageSet[1]->CreateSub ( this, "BUTTON_BUY_SET", UI_FLAG_XSIZE | UI_FLAG_YSIZE , BUTTON_CAN_BUY_SET);
		m_pButtonImageSet[1]->SetTransparentOption( TRUE );
		m_pButtonImageSet[1]->SetVisibleSingle( FALSE );
		RegisterControl ( m_pButtonImageSet[1] );

	}

	CString strButtonKeyword[nMAXPAGENEW] = 
	{
		"DIALOGUE_WINDOW_PAGE_BUTTON1",
		"DIALOGUE_WINDOW_PAGE_BUTTON2",
		"DIALOGUE_WINDOW_PAGE_BUTTON3",
		"DIALOGUE_WINDOW_PAGE_BUTTON0",
		"DIALOGUE_WINDOW_PAGE_BUTTON4"
	};

	for ( int i = 0; i < nMAXPAGENEW; i++ )
	{	
		m_pPageButton[i] = CreateTextButton ( strButtonKeyword[i].GetString (), DIALOGUE_WINDOW_PAGE_BUTTON0 + i, (char*)ID2GAMEWORD ( "DIALOGUE_WINDOW_PAGE_BUTTON", i ) );
	}

	CString strItemNameKeyword[nMAXPAGENEW] = 
	{
		"ITEM_NAME_TEXT0",
		"ITEM_NAME_TEXT1",
		"ITEM_NAME_TEXT2",
		"ITEM_NAME_TEXT3",
		"ITEM_NAME_TEXT4"
	};

	CString strItemPriceKeyword[nMAXPAGENEW] = 
	{
		"ITEM_PRICE_TEXT0",
		"ITEM_PRICE_TEXT1",
		"ITEM_PRICE_TEXT2",
		"ITEM_PRICE_TEXT3",
		"ITEM_PRICE_TEXT4"
	};

	//	ÅØ½ºÆ® ¹Ú½º
	{
		m_pQuestionBox = new CBasicTextBox;
		m_pQuestionBox->CreateSub ( this, "DIALOGUE_QUESTION_TEXTBOX" );
		m_pQuestionBox->SetFont ( pFont12 );		
		m_pQuestionBox->SetTextAlign ( TEXT_ALIGN_BOTH_X );
		m_pQuestionBox->SetVisibleSingle( FALSE );
		RegisterControl ( m_pQuestionBox );


		int nTotalLine = m_pQuestionBox->GetVisibleLine ();

		//	½ºÅ©·Ñ¹Ù
		m_pScrollBar = new CBasicScrollBarEx;
		m_pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, BASIC_DIALOGUE_SCROLLBAR );
		m_pScrollBar->CreateBaseScrollBar ( "BASIC_DIALOGUE_SCROLLBAR" );
		m_pScrollBar->GetThumbFrame()->SetState ( 1, nTotalLine );
		m_pScrollBar->SetVisibleSingle( FALSE );
		RegisterControl ( m_pScrollBar );
	}

	{
		//	ÅØ½ºÆ® ¹Ú½º
		m_pAnswerBox = new CBasicTextBoxEx;
		m_pAnswerBox->CreateSub ( this, "DIALOGUE_ANSWER_TEXTBOX", UI_FLAG_DEFAULT, DIALOGUE_ANSWER_TEXTBOX );
		m_pAnswerBox->SetFont ( pFont9Shadow );
		m_pAnswerBox->SetPartInterval ( fANSWER_PART_INTERVAL );
		m_pAnswerBox->SetSensitive ( true );
		m_pAnswerBox->SetVisibleSingle( FALSE );
		RegisterControl ( m_pAnswerBox );

		int nVisibleLine = m_pAnswerBox->GetVisibleLine ();
		int nTotalLine = m_pAnswerBox->GetTotalLine ();

		//	½ºÅ©·Ñ¹Ù
		m_pAnswerScrollBar = new CBasicScrollBarEx;
		m_pAnswerScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, BASIC_DIALOGUE_ANSWER_SCROLLBAR );
		m_pAnswerScrollBar->CreateBaseScrollBar ( "BASIC_DIALOGUE_ANSWER_SCROLLBAR" );
		m_pAnswerScrollBar->GetThumbFrame()->SetState ( nTotalLine, nVisibleLine );
		m_pAnswerScrollBar->SetVisibleSingle( FALSE );
		RegisterControl ( m_pAnswerScrollBar );
	}


		// RandomTime
	{
		const int nBUTTONSIZE = CBasicTextButton::SIZE23_NEW;
		m_pRandomTimeButton = new CBasicTextButton;
		m_pRandomTimeButton->CreateSub ( this, "BASIC_TEXT_BUTTON18", UI_FLAG_XSIZE, RANDOM_TIME_BUTTON );
		m_pRandomTimeButton->CreateBaseButton ( "RANDOM_TIME_BUTTON", nBUTTONSIZE, CBasicButton::RADIO_FLIP, ID2GAMEWORD( "RANDOM_TIME_BUTTON",0));
		m_pRandomTimeButton->SetFlip ( FALSE );
		//m_pRandomTimeButton->SetVisibleSingle( FALSE );
		RegisterControl ( m_pRandomTimeButton );

		m_pRandomTimeBack = new CBasicLineBox;
		m_pRandomTimeBack->CreateSub ( this, "BASIC_LINE_BOX_EDIT", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pRandomTimeBack->CreateBaseBoxEditBox ( "RANDOM_TIME_BACK" );
		//m_pRandomTimeBack->SetVisibleSingle( FALSE );
		RegisterControl ( m_pRandomTimeBack );    


		m_pRandomTimeText = new CBasicTextBox;
		m_pRandomTimeText->CreateSub ( this, "RANDOM_TIME_TEXT", UI_FLAG_DEFAULT, RANDOM_TIME_TEXT );
		m_pRandomTimeText->SetFont ( pFont9 );
		m_pRandomTimeText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
		//m_pRandomTimeText->SetVisibleSingle( FALSE );
		RegisterControl ( m_pRandomTimeText );
	}

	{
		m_pPageItem = new CNewBuyItem;
		m_pPageItem->CreateSub ( this, "NEW_BUY_ITEM_WINDOW",  UI_FLAG_XSIZE | UI_FLAG_YSIZE ,NEW_BUY_ITEM_WINDOW );
		m_pPageItem->CreateSubControl ();
		m_pPageItem->SetVisibleSingle( FALSE );
		RegisterControl ( m_pPageItem );

	}

	{
		m_pMoney = new CBasicTextBox;
		m_pMoney->CreateSub ( this, "NEW_MONEY_TEXT" , UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pMoney->SetFont ( pFont9 );
		m_pMoney->SetTextAlign ( TEXT_ALIGN_LEFT );
		m_pMoney->SetVisibleSingle( FALSE );
		RegisterControl ( m_pMoney );
	}

	{
		//m_pCloseButton = new CBasicTextButton;
		//m_pCloseButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE | UI_FLAG_YSIZE ,CLOSE_BUTTON );
		//m_pCloseButton->CreateBaseButton ( "CLOSE_BUTTON", CBasicTextButton::SIZE24, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD( "DIALOGUE_BUTTON", 0 ) );
		//m_pCloseButton->SetShortcutKey ( DIK_ESCAPE );
		//m_pCloseButton->SetVisibleSingle( FALSE );
		//RegisterControl ( m_pCloseButton );

		//m_pBuyButton = new CBasicTextButton;
		//m_pBuyButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		//m_pBuyButton->CreateBaseButton ( "BUY_BUTTON", CBasicTextButton::SIZE24, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD( "DIALOGUE_BUTTON", 1 ) );
		//m_pBuyButton->SetVisibleSingle( FALSE );
		//RegisterControl ( m_pBuyButton );

		m_pCloseButton = CreateButtonBlue ( "CLOSE_BUTTON", "CLOSE_BUTTON_TEXT_POS", pFont9, nAlignCenterBoth, CLOSE_BUTTON, "Close" );
		m_pBuyButton = CreateButtonBlue ( "BUY_BUTTON", "BUY_BUTTON_TEXT_POS", pFont9, nAlignCenterBoth, BUY_BUTTON, "Buy" );

		m_pMoneyItem =  new CBasicTextBox;
		m_pMoneyItem->CreateSub ( this, "NEW_MONEY_TOTAL_TEXT" , UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pMoneyItem->SetFont ( pFont9 );
		m_pMoneyItem->SetTextAlign ( TEXT_ALIGN_RIGHT );
		m_pMoneyItem->SetVisibleSingle( FALSE );
		RegisterControl ( m_pMoneyItem );	

		for ( int i = 0; i < nMAXPAGENEW; i++ )
		{
			m_pNameItem[i] =  new CBasicTextBox;
			m_pNameItem[i]->CreateSub ( this, strItemNameKeyword[i].GetString (), UI_FLAG_XSIZE | UI_FLAG_YSIZE );
			m_pNameItem[i]->SetFont ( pFont9 );
			m_pNameItem[i]->SetTextAlign ( TEXT_ALIGN_LEFT );
			m_pNameItem[i]->SetVisibleSingle( FALSE );
			RegisterControl ( m_pNameItem[i] );

			m_pPriceItem[i] =  new CBasicTextBox;
			m_pPriceItem[i]->CreateSub ( this, strItemPriceKeyword[i].GetString (), UI_FLAG_XSIZE | UI_FLAG_YSIZE );
			m_pPriceItem[i]->SetFont ( pFont9 );
			m_pPriceItem[i]->SetTextAlign ( TEXT_ALIGN_LEFT );
			m_pPriceItem[i]->SetVisibleSingle( FALSE );
			RegisterControl ( m_pPriceItem[i] );
		}

	}

	CString strNewTextKeyword[nMAXPAGE] = 
	{
		"NEW_TEXT0",
		"NEW_TEXT1",
		"NEW_TEXT2"
	};

	for ( int i = 0; i < nMAXPAGE; i++ )
	{
		m_pText[i] =  new CBasicTextBox;
		m_pText[i]->CreateSub ( this, strNewTextKeyword[i].GetString () , UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pText[i]->SetFont ( pFont9 );
		m_pText[i]->SetTextAlign ( TEXT_ALIGN_LEFT );
		m_pText[i]->SetVisibleSingle( FALSE );
		RegisterControl ( m_pText[i] );
	}

	for ( int i = 0; i < nMAXPAGE; i++ )
	{
		m_pPage[i] = CreateMarketPage ( NEW_MARKET_PAGE0 + i );	
		m_pInterestItemPage[i] = CreateInterestItemPage ( INTEREST_ITEM_PAGE0 + i );
	}

	SetVisible ( 3 );
}
CBasicTextButton*  CDialogueWindow::CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButtonEx ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText, _DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicTextButton*  CDialogueWindow::CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE24;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText, D3DFONT_SHADOW );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicButtonText* CDialogueWindow::CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText )
{
	CBasicButtonText* pButton = new CBasicButtonText;
	pButton->CreateRanButtonBlue ( this, szButton, ControlID );
	pButton->CreateTextBox ( szTextBox, pFont, nAlign );
	pButton->SetOneLineText( strText.GetString() );
	RegisterControl ( pButton );

	return pButton;
}

CMarketPage* CDialogueWindow::CreateMarketPage ( UIGUID ControlID )
{
	CMarketPage* pPage = new CMarketPage;
	pPage->CreateSub ( this, "NEW_MARKET_PAGE", UI_FLAG_DEFAULT, ControlID );
	pPage->CreateSubControl ();
	RegisterControl ( pPage );
	return pPage;
}
CInterestItem* CDialogueWindow::CreateInterestItemPage ( UIGUID ControlID )
{
	CInterestItem* m_pInterestItemPage = new CInterestItem;
	m_pInterestItemPage->CreateSub ( this, "INTEREST_ITEM_WINDOW", UI_FLAG_DEFAULT, ControlID );
	m_pInterestItemPage->CreateSubControl ();
	RegisterControl ( m_pInterestItemPage );
	return m_pInterestItemPage;
}
void CDialogueWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{

	m_pAnswerBox->SetUseOverColor ( FALSE );
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );	
	
	m_pAnswerBox->SetGlobalPos ( m_pAnswerBox->GetGlobalPos () );

	CString strCombine;
	LONGLONG lnMoney = GLGaeaClient::GetInstance().GetCharacter ()->m_lnMoney;
	CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( lnMoney, 3, "," );
	strCombine.Format ( "%s %s", ID2GAMEWORD ( "DIALOGUE_WINDOW_PAGE_BUTTON", 5 ), strTemp );
	m_pMoney->AddText( strCombine , NS_UITEXTCOLOR::WHITE);


	if ( m_pHaveItem )
	{
		if ( (DWORD)lnMoney < MoneyTotal )
		{
			CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( (LONGLONG)MoneyTotal, 3, "," );
			m_pMoneyItem->ClearText();
			m_pMoneyItem->AddText( strTemp , NS_UITEXTCOLOR::WHITE);
		}
		else
		{
			CString strTemp = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( (LONGLONG)MoneyTotal, 3, "," );
			m_pMoneyItem->ClearText();
			m_pMoneyItem->AddText( strTemp , NS_UITEXTCOLOR::WHITE);
		}

		if ( MoneyTotal == 0 )
		{
			m_pMoneyItem->ClearText();
		}
		m_pHaveItem = FALSE;
	}

	if ( m_dwRandomTime > 0 )
	{
		m_fRandomTime += fElapsedTime;

		CString strTime;
		strTime.Format( "%d", (int) (m_dwRandomTime - m_fRandomTime) );

		m_pRandomTimeText->SetText( strTime, NS_UITEXTUTIL::WHITE );

		// ½Ã°£ ¿À¹ö 
		if ( m_dwRandomTime < m_fRandomTime )
		{
			CInnerInterface::GetInstance().PrintMsgTextDlg( NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT( "NPCTALK_RANDOM_TIME_OVER" ) ); 
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
		}
	}

	if ( bFirstControl )
	{
		{
			CBasicScrollThumbFrame* const pThumbFrame = m_pScrollBar->GetThumbFrame ();		
			m_pQuestionBox->SetCurLine ( 0 );
			const int nTotalLine = m_pQuestionBox->GetTotalLine ();
			const int nLinePerOneView = m_pQuestionBox->GetVisibleLine ();
			if ( nLinePerOneView < nTotalLine )
			{
				const int nMovableLine = nTotalLine - nLinePerOneView;
				float fPercent = pThumbFrame->GetPercent ();
				int nPos = (int)floor(fPercent * nMovableLine);
				if ( nPos < nSTARTLINE ) nPos = nSTARTLINE;
				m_pQuestionBox->SetCurLine ( nPos );			
			}
		}
		{
			CBasicScrollThumbFrame* const pThumbFrame = m_pAnswerScrollBar->GetThumbFrame ();		
			m_pAnswerBox->SetCurLine ( 0 );
			const int nTotalLine = m_pAnswerBox->GetTotalLine ();
			const int nLinePerOneView = m_pAnswerBox->GetVisibleLine ();
			if ( nLinePerOneView < nTotalLine )
			{
				const int nMovableLine = nTotalLine - nLinePerOneView;
				float fPercent = pThumbFrame->GetPercent ();
				int nPos = (int)floor(fPercent * nMovableLine);
				if ( nPos < nSTARTLINE ) nPos = nSTARTLINE;
				m_pAnswerBox->SetCurLine ( nPos );			
			}
		}
	}

	BOOL Page0 = m_pPage[0]->IsVisible();
	BOOL Page1 = m_pPage[1]->IsVisible();
	BOOL Page2 = m_pPage[2]->IsVisible();
	if ( Page0 )
	{
		for ( int j = 0; j < nMAXPAGENEW; j++ )
		{
			DWORD PriceItem = m_pInterestItemPage[0]->GetPriceItem(j);
			CString NameItem = m_pInterestItemPage[0]->GetNameItem(j);
			CString strTemp0 = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( (LONGLONG)PriceItem, 3, "," );
			if ( PriceItem == 0 )
				strTemp0 = "";
			m_pNameItem[j]->ClearText();
			m_pNameItem[j]->SetText( NameItem , NS_UITEXTCOLOR::SILVER);
			m_pPriceItem[j]->ClearText();
			m_pPriceItem[j]->SetText( strTemp0 , NS_UITEXTCOLOR::SILVER);
		}
	}
	else if ( Page1 )
	{
		for ( int j = 0; j < nMAXPAGENEW; j++ )
		{
			DWORD PriceItem = m_pInterestItemPage[1]->GetPriceItem(j);
			CString NameItem = m_pInterestItemPage[1]->GetNameItem(j);
			CString strTemp1 = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( (LONGLONG)PriceItem, 3, "," );
			if ( PriceItem == 0  )
				strTemp1 = "";
			m_pNameItem[j]->ClearText();
			m_pNameItem[j]->SetText( NameItem , NS_UITEXTCOLOR::SILVER);
			m_pPriceItem[j]->ClearText();
			m_pPriceItem[j]->SetText( strTemp1 , NS_UITEXTCOLOR::SILVER);
		}
	}
	else if ( Page2 )
	{
		for ( int j = 0; j < nMAXPAGENEW; j++ )
		{
			DWORD PriceItem = m_pInterestItemPage[2]->GetPriceItem(j);
			CString NameItem = m_pInterestItemPage[2]->GetNameItem(j);
			CString strTemp2 = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( (LONGLONG)PriceItem, 3, "," );
			if ( PriceItem == 0  )
				strTemp2 = "";
			m_pNameItem[j]->ClearText();
			m_pNameItem[j]->SetText( NameItem , NS_UITEXTCOLOR::SILVER);
			m_pPriceItem[j]->ClearText();
			m_pPriceItem[j]->SetText( strTemp2 , NS_UITEXTCOLOR::SILVER);
		}
	}

	if ( Page0 || Page1 || Page2 )
	{
		m_pText[0]->AddText( ID2GAMEWORD ( "NEW_TEXT_DIALOGUE_WINDOW_PAGE", 0 ) , NS_UITEXTCOLOR::WHITE);
		m_pText[1]->AddText( ID2GAMEWORD ( "NEW_TEXT_DIALOGUE_WINDOW_PAGE", 1 ) , NS_UITEXTCOLOR::WHITE);
		m_pText[2]->AddText( ID2GAMEWORD ( "NEW_TEXT_DIALOGUE_WINDOW_PAGE", 2 ) , NS_UITEXTCOLOR::WHITE);


		if ( IsUse && IsBuy ) // ¡´·Ñé§ «×éÍä´éáÅÐãªéä´é
		{
			InitMarket();

			m_pButtonImageSet[0]->SetVisibleSingle( TRUE );
			m_pButtonImage[0]->SetVisibleSingle( FALSE );
			m_pPage[0]->SetUnUse();
			m_pPage[1]->SetUnUse();
			m_pPage[2]->SetUnUse();
			m_pInterestItemPage[0]->SetUnUse();
			m_pInterestItemPage[1]->SetUnUse();
			m_pInterestItemPage[2]->SetUnUse();

			m_pButtonImageSet[1]->SetVisibleSingle( TRUE );
			m_pButtonImage[1]->SetVisibleSingle( FALSE );
			m_pPage[0]->SetUnBuy();
			m_pPage[1]->SetUnBuy();
			m_pPage[2]->SetUnBuy();
			m_pInterestItemPage[0]->SetUnBuy();
			m_pInterestItemPage[1]->SetUnBuy();
			m_pInterestItemPage[2]->SetUnBuy();
		}
		else if ( IsUse && !IsBuy ) // ¡´á¤èÊÒÁÒÃ¶ãªéä´é
		{
			InitMarket();

			m_pButtonImageSet[0]->SetVisibleSingle( TRUE );
			m_pButtonImage[0]->SetVisibleSingle( FALSE );
			m_pPage[0]->SetUnUse();
			m_pPage[1]->SetUnUse();
			m_pPage[2]->SetUnUse();
			m_pInterestItemPage[0]->SetUnUse();
			m_pInterestItemPage[1]->SetUnUse();
			m_pInterestItemPage[2]->SetUnUse();

			m_pButtonImageSet[1]->SetVisibleSingle( FALSE );
			m_pButtonImage[1]->SetVisibleSingle( TRUE );

		}
		else if ( IsBuy && !IsUse )
		{
			InitMarket();

			m_pButtonImageSet[1]->SetVisibleSingle( TRUE );
			m_pButtonImage[1]->SetVisibleSingle( FALSE );
			m_pPage[0]->SetUnBuy();
			m_pPage[1]->SetUnBuy();
			m_pPage[2]->SetUnBuy();
			m_pInterestItemPage[0]->SetUnBuy();
			m_pInterestItemPage[1]->SetUnBuy();
			m_pInterestItemPage[2]->SetUnBuy();

			m_pButtonImageSet[0]->SetVisibleSingle( FALSE );
			m_pButtonImage[0]->SetVisibleSingle( TRUE );
		}
		else
		{
			InitMarket();

			m_pButtonImageSet[0]->SetVisibleSingle( FALSE );
			m_pButtonImage[0]->SetVisibleSingle( TRUE );
			m_pButtonImageSet[1]->SetVisibleSingle( FALSE );
			m_pButtonImage[1]->SetVisibleSingle( TRUE );
		}
	}
}

void CDialogueWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case DIALOGUE_ANSWER_TEXTBOX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pAnswerBox->GetSelectPos ();
				if ( nIndex < 0 ) return ;

				m_pAnswerBox->SetUseOverColor ( TRUE );		
				m_pAnswerBox->SetOverColor ( nIndex, NS_UITEXTCOLOR::DARKGRAY); // HOVER COLOR ON DIALOGUE WINDOW

				const DWORD NID = m_pAnswerBox->GetTextData ( nIndex );				
				if ( !m_pDialogueCase ) return ;
				CNpcTalkControl* pNpcTalkControl = m_pDialogueCase->GetTalkControl();
				if ( !pNpcTalkControl ) return ;

				SNpcTalk* pNpcTalk = pNpcTalkControl->GetTalk ( NID );
				if ( !pNpcTalk ) return ;

				if ( dwMsg & UIMSG_LB_UP )
				{	
					TranslateTalkMessage ( pNpcTalk );
				}
				else
				{
					//	Äù½ºÆ® º¸»óÄ¡ Ç¥Çö
					if ( pNpcTalk->m_nACTION == SNpcTalk::EM_QUEST_START )
					{						
						DWORD dwQuestID = pNpcTalk->m_dwQuestStartID[0];
						GLQUEST* pQuest = GLQuestMan::GetInstance().Find ( dwQuestID );
						if ( !pQuest )
						{
							CDebugSet::ToLogFile ( "quest id = %d ÀÇ Á¤º¸¸¦ °¡Á®¿ÀÁö ¸øÇÏ¿´½À´Ï´Ù.", dwQuestID );
							return;
						}

						//	º¸»óÄ¡°¡ ¾øÀ¸¸é ¾Æ¹«°Íµµ Ç¥½ÃÇÏÁö ¾ÊÀ½
						if ( !(pQuest->m_dwGiftEXP || pQuest->m_dwGiftMONEY ||
							 pQuest->m_dwGiftELEMENT || pQuest->m_dwGiftLIFEPOINT ||
							 pQuest->m_dwGiftSKILLPOINT || pQuest->m_dwGiftSTATSPOINT ||
							 pQuest->m_vecGiftITEM.size () || pQuest->m_vecGiftSKILL.size ()) )
						{
							return ;
						}

						if ( CInnerInterface::GetInstance().BEGIN_COMMON_LINEINFO_MULTI () )
						{
							CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( ID2GAMEWORD("QUEST_GIFT",9), NS_UITEXTCOLOR::GREENYELLOW );

							CString strCombine;

							if ( pQuest->m_dwGiftEXP )
							{
								strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",0), pQuest->m_dwGiftEXP );
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine, NS_UITEXTCOLOR::WHITE );
							}
							if ( pQuest->m_dwGiftMONEY )
							{
								strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",1), pQuest->m_dwGiftMONEY );
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine, NS_UITEXTCOLOR::WHITE );
							}
							if ( pQuest->m_dwGiftELEMENT )
							{
								strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",2), pQuest->m_dwGiftELEMENT );
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine, NS_UITEXTCOLOR::WHITE );
							}
							if ( pQuest->m_dwGiftLIFEPOINT )
							{
								strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",3), pQuest->m_dwGiftLIFEPOINT );
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine, NS_UITEXTCOLOR::WHITE );
							}
							//if ( pQuest->m_dwGiftDisPK )
							//{
							//	strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",4), pQuest->m_dwGiftDisPK );
							//	CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine, NS_UITEXTCOLOR::WHITE );
							//}
							if ( pQuest->m_dwGiftSKILLPOINT )
							{
								strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",5), pQuest->m_dwGiftSKILLPOINT );
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine, NS_UITEXTCOLOR::WHITE );
							}
							if ( pQuest->m_dwGiftSTATSPOINT )
							{
								strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",6), pQuest->m_dwGiftSTATSPOINT );
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine, NS_UITEXTCOLOR::WHITE );
							}

							if ( pQuest->m_vecGiftITEM.size () )
							{
								CString strItem = ID2GAMEWORD("QUEST_GIFT",7);
								strItem += " : ";
								INVENQARRAY_ITER iter = pQuest->m_vecGiftITEM.begin ();
								INVENQARRAY_ITER iter_end = pQuest->m_vecGiftITEM.end ();
								for ( ; iter != iter_end; )
								{
									SITEMCUSTOM& sItemCustom = (*iter);
									SITEM* pItem = GLItemMan::GetInstance().GetItem ( sItemCustom.sNativeID );
									if ( !pItem ) continue;
									strItem += pItem->GetName ();

									++iter;
									if ( iter == iter_end ) break;
									strItem += ", ";
								}
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strItem, NS_UITEXTCOLOR::WHITE );
							}

							if ( pQuest->m_vecGiftSKILL.size () )
							{
								CString strSkill = ID2GAMEWORD("QUEST_GIFT",8);
								strSkill += " : ";
								DWQARRAY_ITER iter = pQuest->m_vecGiftSKILL.begin ();
								DWQARRAY_ITER iter_end = pQuest->m_vecGiftSKILL.end ();
								for ( ; iter != iter_end; )
								{
									DWORD dwID = (*iter);									
									PGLSKILL pSKILL = GLSkillMan::GetInstance().GetData ( SNATIVEID(dwID) );
									if ( !pSKILL ) continue;
									strSkill += pSKILL->GetName();

									++iter;
									if ( iter == iter_end ) break;
									strSkill += ", ";
								}
								CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strSkill, NS_UITEXTCOLOR::WHITE );
							}

							CInnerInterface::GetInstance().END_COMMON_LINEINFO_MULTI ();
						}
					}
				}
			}
		}
		break;
	case DIALOGUE_WINDOW_PAGE_BUTTON0:
	case DIALOGUE_WINDOW_PAGE_BUTTON1:
	case DIALOGUE_WINDOW_PAGE_BUTTON2:
	case DIALOGUE_WINDOW_PAGE_BUTTON3:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = ControlID - DIALOGUE_WINDOW_PAGE_BUTTON0;

				if ( dwMsg & UIMSG_LB_DOWN )
				{
					SetVisible ( nIndex );
				}
			}
		}
		break;

	case DIALOGUE_WINDOW_PAGE_BUTTON4:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("FUNCTION_DISABLED") );
				return;
			}
		}
		break;

	case NEW_MARKET_PAGE0:
	case NEW_MARKET_PAGE1:
	case NEW_MARKET_PAGE2:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPageIndex = ControlID - NEW_MARKET_PAGE0;

				//	NOTE
				//		¼Õ¿¡ µé°í ÀÖ´Â ¾ÆÀÌÅÛ Ã³¸®
				if ( dwMsg & UIMSG_LB_UP || dwMsg & UIMSG_RB_UP )
				{
					SNATIVEID sNativeID = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					if ( sNativeID != NATIVEID_NULL () )
					{
						//	NOTE
						//		¹°°Ç ÆÈ±â
						SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sNativeID );
						if ( pItemData )
						{
							const std::string& strItemName = pItemData->GetName();
							CString strCombine = CInnerInterface::GetInstance().MakeString ( ID2GAMEINTEXT("SELL_ITEM_CONFIRM"), strItemName.c_str() );
							DoModal ( strCombine, MODAL_QUESTION, YESNO, MODAL_SELL_ITEM );
						}
						else
						{
							GASSERT ( 0 && "¾ÆÀÌÅÛÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù." );
						}

						return ;
					}
				}


				if ( CHECK_RB_UP_LIKE ( dwMsg ))
				{
					int nPosXNew, nPosYNew;
					m_pPage[nPageIndex]->GetItemIndex ( &nPosXNew, &nPosYNew );
					if ( nPosXNew < 0 || nPosYNew < 0 ) return ;

					SINVENITEM sInvenItem = m_pPage[nPageIndex]->GetItem ( nPosXNew, nPosYNew );
					SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sInvenItem.sItemCustom.sNativeID );
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						m_pPageItem->LoadItem( sInvenItem );
						if ( m_pCountSlot < 10 )
						{
							float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetBuyRate();
							float fSHOP_RATE_C = fSHOP_RATE * 0.01f;
							DWORD dwPrice = static_cast<DWORD>( pITEM->sBasicOp.dwBuyPrice * fSHOP_RATE_C );
							AddPrice ( dwPrice );
							m_pCountSlot++;
						}
					}

				}
				int nPosX, nPosY;
				m_pPage[nPageIndex]->GetItemIndex ( &nPosX, &nPosY );			
				SetItemIndex ( nPosX, nPosY );
				if ( nPosX < 0 || nPosY < 0 ) return ;

	//			if ( CUIMan::GetFocusControl () == this )
				SINVENITEM sInvenItem = m_pPage[nPageIndex]->GetItem ( nPosX, nPosY );
				{				
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItem.sItemCustom, TRUE, TRUE, FALSE, sInvenItem.wPosX, sInvenItem.wPosY, m_sMarketID );

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							if ( dwMsg & UIMSG_LB_UP )
							{
								CInnerInterface::GetInstance().PreviewItem( sInvenItem.sItemCustom );
								return;
							}
						}
					}
				}


				//	NOTE
				//		¾ÆÀÌÅÛ ¹Ù·Î »ç±â
				if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LCONTROL ) & DXKEY_PRESSED )
				{
					if ( dwMsg & UIMSG_LB_UP )
					{
						SNATIVEID sNativeID = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
						if ( sNativeID != NATIVEID_NULL () ) return ;

						GLGaeaClient::GetInstance().GetCharacter()->ReqNpcTo ( m_sMarketID, m_nPageIndex, nPosX, nPosY );
						return ;
					}
				}


				if ( dwMsg & UIMSG_LB_UP )
				{
					SNATIVEID sNativeID = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					if ( sNativeID != NATIVEID_NULL () ) return ;

					SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sInvenItem.sItemCustom.sNativeID );
					if ( pITEM )
					{
						// Note : °ãÄ§ÀÌ °¡´ÉÇÏ°í ÇÑ°³¾¿ ÆÄ´Â ¾ÆÀÌÅÛÀÇ °æ¿ì ±¸ÀÔ ¼ö·® ÀÔ·Â. ( È­»ì¹­À½, ºÎÀû¹­À½. )
						if( pITEM->ISPILE() && (pITEM->GETAPPLYNUM()==1) )
						{
							DoModal ( ID2GAMEINTEXT ( "BUY_PILE_ITEM" ), MODAL_INPUT, EDITBOX_NUMBER, MODAL_PILE_ITEM );
							return ;
						}
						else
						{
							//	NOTE
							//		¹°°Ç »ç±â							
							const std::string& strItemName = pITEM->GetName();
							CString strCombine = CInnerInterface::GetInstance().MakeString ( ID2GAMEINTEXT("BUY_ITEM_CONFIRM"), strItemName.c_str() );
							DoModal ( strCombine, MODAL_QUESTION, YESNO, MODAL_BUY_ITEM );							
							return ;
						}
					}
				}
			}
		}
		break;
	case NEW_BUY_ITEM_WINDOW:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPosX, nPosY;
				m_pPageItem->GetItemIndex ( &nPosX, &nPosY );			
				m_pPageItem->SetItemIndex ( nPosX, nPosY );
				if ( nPosX < 0 || nPosY < 0 ) return ;

				SINVENITEM sInvenItemNew = m_pPageItem->GetItem ( nPosX, nPosY );
				{				
					if ( sInvenItemNew.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItemNew.sItemCustom, TRUE, TRUE, FALSE, sInvenItemNew.wPosX, sInvenItemNew.wPosY, m_sMarketID );
					}
				}

				if ( CHECK_RB_UP_LIKE ( dwMsg ))
				{
					int nPosXNew, nPosYNew;
					m_pPageItem->GetItemIndex ( &nPosXNew, &nPosYNew );
					if ( nPosXNew < 0 || nPosYNew < 0 ) return ;

					SINVENITEM sInvenItem = m_pPageItem->GetItem ( nPosXNew, nPosYNew );
					SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sInvenItem.sItemCustom.sNativeID );
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						ReItemPosition(nPosXNew,nPosYNew);
						if ( m_pCountSlot > 0 )
						{
							float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetBuyRate();
							float fSHOP_RATE_C = fSHOP_RATE * 0.01f;
							DWORD dwPrice = static_cast<DWORD>( pITEM->sBasicOp.dwBuyPrice * fSHOP_RATE_C );
							DelPrice ( dwPrice );
							m_pCountSlot--;
						}
					}
				}
			}
		}
		break;
	case INTEREST_ITEM_PAGE0:
	case INTEREST_ITEM_PAGE1:
	case INTEREST_ITEM_PAGE2:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPageIndex = ControlID - INTEREST_ITEM_PAGE0;

				if ( CHECK_RB_UP_LIKE ( dwMsg ))
				{
					int nPosXNew, nPosYNew;
					m_pInterestItemPage[nPageIndex]->GetItemIndex ( &nPosXNew, &nPosYNew );
					if ( nPosXNew < 0 || nPosYNew < 0 ) return ;

					SINVENITEM sInvenItem = m_pInterestItemPage[nPageIndex]->GetItem ( nPosXNew, nPosYNew );
					SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sInvenItem.sItemCustom.sNativeID );
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						m_pPageItem->LoadItem( sInvenItem );
						if ( m_pCountSlot < 10 )
						{
							float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetBuyRate();
							float fSHOP_RATE_C = fSHOP_RATE * 0.01f;
							DWORD dwPrice = static_cast<DWORD>( pITEM->sBasicOp.dwBuyPrice * fSHOP_RATE_C );
							AddPrice ( dwPrice );
							m_pCountSlot++;
						}
					}
				}

				int nPosX, nPosY;
				m_pInterestItemPage[nPageIndex]->GetItemIndex ( &nPosX, &nPosY );			
				SetItemIndex ( nPosX, nPosY );
				if ( nPosX < 0 || nPosY < 0 ) return ;

				SINVENITEM sInvenItem = m_pInterestItemPage[nPageIndex]->GetItem ( nPosX, nPosY );
				{				
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItem.sItemCustom, TRUE, TRUE, FALSE, sInvenItem.wPosX, sInvenItem.wPosY, m_sMarketID );
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					SNATIVEID sNativeID = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM().sNativeID;
					if ( sNativeID != NATIVEID_NULL () ) return ;

					SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sInvenItem.sItemCustom.sNativeID );
					if ( pITEM )
					{
						// Note : °ãÄ§ÀÌ °¡´ÉÇÏ°í ÇÑ°³¾¿ ÆÄ´Â ¾ÆÀÌÅÛÀÇ °æ¿ì ±¸ÀÔ ¼ö·® ÀÔ·Â. ( È­»ì¹­À½, ºÎÀû¹­À½. )
						if( pITEM->ISPILE() && (pITEM->GETAPPLYNUM()==1) )
						{
							DoModal ( ID2GAMEINTEXT ( "BUY_PILE_ITEM" ), MODAL_INPUT, EDITBOX_NUMBER, MODAL_PILE_ITEM );
							return ;
						}
						else
						{
							//	NOTE
							//		¹°°Ç »ç±â							
							const std::string& strItemName = pITEM->GetName();
							CString strCombine = CInnerInterface::GetInstance().MakeString ( ID2GAMEINTEXT("BUY_ITEM_CONFIRM"), strItemName.c_str() );
							DoModal ( strCombine, MODAL_QUESTION, YESNO, MODAL_BUY_ITEM );							
							return ;
						}
					}
				}
			}
		}
		break;
	case CLOSE_BUTTON:
		{	
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_UP )
				{
					CInnerInterface::GetInstance().HideGroup ( GetWndID () );
				}
			}
		}
		break;

	case BUY_BUTTON:
	{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPosX, nPosY;
				m_pPageItem->GetItemIndex ( &nPosX, &nPosY );			
				m_pPageItem->SetItemIndex ( nPosX, nPosY );
				if ( nPosX < 0 || nPosY < 0 ) return ;

				SINVENITEM sInvenItemNew = m_pPageItem->GetItem ( nPosX, nPosY );
				{				
					if ( sInvenItemNew.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sInvenItemNew.sItemCustom, TRUE, TRUE, FALSE, sInvenItemNew.wPosX, sInvenItemNew.wPosY, m_sMarketID );

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							if ( dwMsg & UIMSG_LB_UP )
							{
								CInnerInterface::GetInstance().PreviewItem( sInvenItemNew.sItemCustom );
								return;
							}
						}
					}
				}

				if ( CHECK_RB_UP_LIKE ( dwMsg ))
				{
					int nPosXNew, nPosYNew;
					m_pPageItem->GetItemIndex ( &nPosXNew, &nPosYNew );
					if ( nPosXNew < 0 || nPosYNew < 0 ) return ;

					SINVENITEM sInvenItem = m_pPageItem->GetItem ( nPosXNew, nPosYNew );
					SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sInvenItem.sItemCustom.sNativeID );
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						ReItemPosition(nPosXNew,nPosYNew);
						if ( m_pCountSlot > 0 )
						{
							float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetBuyRate();
							float fSHOP_RATE_C = fSHOP_RATE * 0.01f;
							DWORD dwPrice = static_cast<DWORD>( pITEM->sBasicOp.dwBuyPrice * fSHOP_RATE_C );
							DelPrice ( dwPrice );
							m_pCountSlot--;
						}
					}
				}
			}
		}
		break;
	case BUTTON_CAN_USE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_UP )
				{
					IsUse = TRUE;
				}
			}
		}
		break;
	case BUTTON_CAN_BUY:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_UP )
				{
					IsBuy = TRUE;
				}
			}
		}
		break;
	case BUTTON_CAN_USE_SET:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_UP )
				{
					IsUse = FALSE;
				}
			}
		}
		break;
	case BUTTON_CAN_BUY_SET:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_UP )
				{
					IsBuy = FALSE;
				}
			}
		}
		break;
	}
}
void CDialogueWindow::AddPrice (  DWORD price )
{
	m_pHaveItem = TRUE;
	MoneyTotal += price;
}
void CDialogueWindow::DelPrice (  DWORD price )
{
	m_pHaveItem = TRUE;
	MoneyTotal -= price;
}
void CDialogueWindow::ReItemPosition( int x , int y)
{
	if( x == 9 )
	{
		m_pPageItem->UnLoadItem(x,y);
	}
	else
	{
		int j = x + 1;
		SINVENITEM sInvenItem = m_pPageItem->GetItem ( j, y );

		if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
		{
			ReItemPosition(j,y);
			m_pPageItem->LoadItemNew(x,y,sInvenItem);
		}
		else
		{
			m_pPageItem->UnLoadItem(x,y);
		}
	}
}
void CDialogueWindow::ClearItem()
{
	m_pPageItem->UnLoadItemPage();
}
void CDialogueWindow::SetPageFalse( int nPage )
{
	if ( nPage == 0)
	{
		m_pPage[0]->SetVisibleSingle ( FALSE );
		m_pPageButton[0]->SetFlipYellow ( FALSE );
		m_pInterestItemPage[0]->SetVisibleSingle( FALSE );

		m_pBasicLineBox7->SetVisibleSingle( FALSE );
		m_pBasicLineBox8->SetVisibleSingle( FALSE );
		m_pBasicLineBox9->SetVisibleSingle( FALSE );
		m_pBasicLineBox10->SetVisibleSingle( FALSE );
		m_pBasicLineBox11->SetVisibleSingle( FALSE );
		m_pBasicLineBox12->SetVisibleSingle( FALSE );
		m_pBasicLineBox13->SetVisibleSingle( FALSE );
		m_pBasicLineBox14->SetVisibleSingle( FALSE );
		m_pBasicLineBox15->SetVisibleSingle( FALSE );
		m_pBasicLineBox16->SetVisibleSingle( FALSE );
		m_pBasicLineBox17->SetVisibleSingle( FALSE );
		m_pPurchaseImage->SetVisibleSingle( FALSE );
		m_pPageItem->SetVisibleSingle( FALSE );
		m_pMoney->SetVisibleSingle( FALSE );
		m_pBuyButton->SetVisibleSingle( FALSE );
		m_pCloseButton->SetVisibleSingle( FALSE );
		m_pMoneyItem->SetVisibleSingle( FALSE );

		for ( int i = 0; i < nMAXPAGENEW; i++ )
		{
			m_pNameItem[i]->SetVisibleSingle( FALSE );
			m_pPriceItem[i]->SetVisibleSingle( FALSE );
		}

		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			m_pText[i]->SetVisibleSingle( FALSE );
		}

		for ( int i = 0; i < 2; i++ )
		{
			m_pButtonImage[i]->SetVisibleSingle( FALSE );
			m_pButtonImageSet[i]->SetVisibleSingle( FALSE );
		}
	}
	else if ( nPage == 1 )
	{
		m_pPage[1]->SetVisibleSingle ( FALSE );
		m_pPageButton[1]->SetFlipYellow ( FALSE );
		m_pInterestItemPage[1]->SetVisibleSingle( FALSE );

		m_pBasicLineBox7->SetVisibleSingle( FALSE );
		m_pBasicLineBox8->SetVisibleSingle( FALSE );
		m_pBasicLineBox9->SetVisibleSingle( FALSE );
		m_pBasicLineBox10->SetVisibleSingle( FALSE );
		m_pBasicLineBox11->SetVisibleSingle( FALSE );
		m_pBasicLineBox12->SetVisibleSingle( FALSE );
		m_pBasicLineBox13->SetVisibleSingle( FALSE );
		m_pBasicLineBox14->SetVisibleSingle( FALSE );
		m_pBasicLineBox15->SetVisibleSingle( FALSE );
		m_pBasicLineBox16->SetVisibleSingle( FALSE );
		m_pBasicLineBox17->SetVisibleSingle( FALSE );
		m_pPurchaseImage->SetVisibleSingle( FALSE );
		m_pPageItem->SetVisibleSingle( FALSE );
		m_pMoney->SetVisibleSingle( FALSE );
		m_pBuyButton->SetVisibleSingle( FALSE );
		m_pCloseButton->SetVisibleSingle( FALSE );
		m_pMoneyItem->SetVisibleSingle( FALSE );

		for ( int i = 0; i < nMAXPAGENEW; i++ )
		{
			m_pNameItem[i]->SetVisibleSingle( FALSE );
			m_pPriceItem[i]->SetVisibleSingle( FALSE );
		}

		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			m_pText[i]->SetVisibleSingle( FALSE );
		}

		for ( int i = 0; i < 2; i++ )
		{
			m_pButtonImage[i]->SetVisibleSingle( FALSE );
			m_pButtonImageSet[i]->SetVisibleSingle( FALSE );
		}
	}
	else if ( nPage == 2 )
	{
		m_pPage[2]->SetVisibleSingle ( FALSE );
		m_pPageButton[2]->SetFlipYellow ( FALSE );
		m_pInterestItemPage[2]->SetVisibleSingle( FALSE );

		m_pBasicLineBox7->SetVisibleSingle( FALSE );
		m_pBasicLineBox8->SetVisibleSingle( FALSE );
		m_pBasicLineBox9->SetVisibleSingle( FALSE );
		m_pBasicLineBox10->SetVisibleSingle( FALSE );
		m_pBasicLineBox11->SetVisibleSingle( FALSE );
		m_pBasicLineBox12->SetVisibleSingle( FALSE );
		m_pBasicLineBox13->SetVisibleSingle( FALSE );
		m_pBasicLineBox14->SetVisibleSingle( FALSE );
		m_pBasicLineBox15->SetVisibleSingle( FALSE );
		m_pBasicLineBox16->SetVisibleSingle( FALSE );
		m_pBasicLineBox17->SetVisibleSingle( FALSE );
		m_pPurchaseImage->SetVisibleSingle( FALSE );
		m_pPageItem->SetVisibleSingle( FALSE );
		m_pMoney->SetVisibleSingle( FALSE );
		m_pBuyButton->SetVisibleSingle( FALSE );
		m_pCloseButton->SetVisibleSingle( FALSE );
		m_pMoneyItem->SetVisibleSingle( FALSE );

		for ( int i = 0; i < nMAXPAGENEW; i++ )
		{
			m_pNameItem[i]->SetVisibleSingle( FALSE );
			m_pPriceItem[i]->SetVisibleSingle( FALSE );
		}

		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			m_pText[i]->SetVisibleSingle( FALSE );
		}

		for ( int i = 0; i < 2; i++ )
		{
			m_pButtonImage[i]->SetVisibleSingle( FALSE );	
			m_pButtonImageSet[i]->SetVisibleSingle( FALSE );
		}
	}
	else if ( nPage == 3 )
	{
		m_pBasicLineBox->SetVisibleSingle( FALSE );
		m_pBasicLineBox1->SetVisibleSingle( FALSE );
		m_pBasicLineBox2->SetVisibleSingle( FALSE );
		m_pBasicLineBox3->SetVisibleSingle( FALSE );
		m_pBasicLineBox4->SetVisibleSingle( FALSE );
		m_pBasicLineBox5->SetVisibleSingle( FALSE );
		m_pBasicLineBox6->SetVisibleSingle( FALSE );
		m_pQuestionBox->SetVisibleSingle( FALSE );
		m_pScrollBar->SetVisibleSingle( FALSE );
		m_pAnswerBox->SetVisibleSingle( FALSE );
		m_pAnswerScrollBar->SetVisibleSingle( FALSE );

		m_pPageButton[3]->SetFlipYellow ( FALSE );
	}
	else if ( nPage == 4 )
	{
	}
}
void CDialogueWindow::SetVisible( int nPage )
{
	for ( int i = 0; i < nMAXPAGENEW; i++ )
	{
		m_pPageButton[i]->SetFlipYellow ( FALSE );
	}

	if ( nPage == 0 )
	{
		SetPageFalse(1);
		SetPageFalse(2);
		SetPageFalse(3);
		SetPageFalse(4);

		m_nPageIndex = 0;
		m_pPage[m_nPageIndex]->SetVisibleSingle ( TRUE );
		m_pPageButton[m_nPageIndex]->SetFlipYellow ( TRUE );
		m_pPage[m_nPageIndex]->m_pScrollBar->SetVisibleSingle ( FALSE );
		m_pPageItem->SetVisibleSingle( TRUE );
		m_pMoney->SetVisibleSingle( TRUE );
		m_pInterestItemPage[m_nPageIndex]->SetVisibleSingle( TRUE );
		m_pBuyButton->SetVisibleSingle( TRUE );
		m_pCloseButton->SetVisibleSingle( TRUE );
		m_pMoneyItem->SetVisibleSingle( TRUE );

		m_pBasicLineBox7->SetVisibleSingle( TRUE );
		m_pBasicLineBox8->SetVisibleSingle( TRUE );
		m_pBasicLineBox9->SetVisibleSingle( TRUE );
		m_pBasicLineBox10->SetVisibleSingle( TRUE );
		m_pBasicLineBox11->SetVisibleSingle( TRUE );
		m_pBasicLineBox12->SetVisibleSingle( TRUE );
		m_pBasicLineBox13->SetVisibleSingle( TRUE );
		m_pBasicLineBox14->SetVisibleSingle( TRUE );
		m_pBasicLineBox15->SetVisibleSingle( TRUE );
		m_pBasicLineBox16->SetVisibleSingle( TRUE );
		m_pBasicLineBox17->SetVisibleSingle( TRUE );
		m_pPurchaseImage->SetVisibleSingle( TRUE );

		for ( int i = 0; i < nMAXPAGENEW; i++ )
		{
			m_pNameItem[i]->SetVisibleSingle( TRUE );
			m_pPriceItem[i]->SetVisibleSingle( TRUE );
		}

		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			m_pText[i]->SetVisibleSingle( TRUE );
		}

		for ( int i = 0; i < 2; i++ )
		{
			m_pButtonImage[i]->SetVisibleSingle( TRUE );
			m_pButtonImageSet[i]->SetVisibleSingle( TRUE );
		}

	}
	else if ( nPage == 1 )
	{
		SetPageFalse(0);
		SetPageFalse(2);
		SetPageFalse(3);
		SetPageFalse(4);

		m_nPageIndex = 1;
		m_pPage[m_nPageIndex]->SetVisibleSingle ( TRUE );
		m_pPageButton[m_nPageIndex]->SetFlipYellow ( TRUE );
		m_pPage[m_nPageIndex]->m_pScrollBar->SetVisibleSingle ( FALSE );
		m_pPageItem->SetVisibleSingle( TRUE );
		m_pMoney->SetVisibleSingle( TRUE );
		m_pInterestItemPage[m_nPageIndex]->SetVisibleSingle( TRUE );
		m_pBuyButton->SetVisibleSingle( TRUE );
		m_pCloseButton->SetVisibleSingle( TRUE );
		m_pMoneyItem->SetVisibleSingle( TRUE );

		m_pBasicLineBox7->SetVisibleSingle( TRUE );
		m_pBasicLineBox8->SetVisibleSingle( TRUE );
		m_pBasicLineBox9->SetVisibleSingle( TRUE );
		m_pBasicLineBox10->SetVisibleSingle( TRUE );
		m_pBasicLineBox11->SetVisibleSingle( TRUE );
		m_pBasicLineBox12->SetVisibleSingle( TRUE );
		m_pBasicLineBox13->SetVisibleSingle( TRUE );
		m_pBasicLineBox14->SetVisibleSingle( TRUE );
		m_pBasicLineBox15->SetVisibleSingle( TRUE );
		m_pBasicLineBox16->SetVisibleSingle( TRUE );
		m_pBasicLineBox17->SetVisibleSingle( TRUE );
		m_pPurchaseImage->SetVisibleSingle( TRUE );

		for ( int i = 0; i < nMAXPAGENEW; i++ )
		{
			m_pNameItem[i]->SetVisibleSingle( TRUE );
			m_pPriceItem[i]->SetVisibleSingle( TRUE );
		}

		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			m_pText[i]->SetVisibleSingle( TRUE );
		}

		for ( int i = 0; i < 2; i++ )
		{
			m_pButtonImage[i]->SetVisibleSingle( TRUE );
			m_pButtonImageSet[i]->SetVisibleSingle( TRUE );
		}
	}
	else if ( nPage == 2 )
	{
		SetPageFalse(0);
		SetPageFalse(1);
		SetPageFalse(3);
		SetPageFalse(4);

		m_nPageIndex = 2;
		m_pPage[m_nPageIndex]->SetVisibleSingle ( TRUE );
		m_pPageButton[m_nPageIndex]->SetFlipYellow ( TRUE );
		m_pPage[m_nPageIndex]->m_pScrollBar->SetVisibleSingle ( FALSE );
		m_pPageItem->SetVisibleSingle( TRUE );
		m_pMoney->SetVisibleSingle( TRUE );
		m_pInterestItemPage[m_nPageIndex]->SetVisibleSingle( TRUE );
		m_pBuyButton->SetVisibleSingle( TRUE );
		m_pCloseButton->SetVisibleSingle( TRUE );
		m_pMoneyItem->SetVisibleSingle( TRUE );

		m_pBasicLineBox7->SetVisibleSingle( TRUE );
		m_pBasicLineBox8->SetVisibleSingle( TRUE );
		m_pBasicLineBox9->SetVisibleSingle( TRUE );
		m_pBasicLineBox10->SetVisibleSingle( TRUE );
		m_pBasicLineBox11->SetVisibleSingle( TRUE );
		m_pBasicLineBox12->SetVisibleSingle( TRUE );
		m_pBasicLineBox13->SetVisibleSingle( TRUE );
		m_pBasicLineBox14->SetVisibleSingle( TRUE );
		m_pBasicLineBox15->SetVisibleSingle( TRUE );
		m_pBasicLineBox16->SetVisibleSingle( TRUE );
		m_pBasicLineBox17->SetVisibleSingle( TRUE );
		m_pPurchaseImage->SetVisibleSingle( TRUE );

		for ( int i = 0; i < nMAXPAGENEW; i++ )
		{
			m_pNameItem[i]->SetVisibleSingle( TRUE );
			m_pPriceItem[i]->SetVisibleSingle( TRUE );
		}

		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			m_pText[i]->SetVisibleSingle( TRUE );
		}

		for ( int i = 0; i < 2; i++ )
		{
			m_pButtonImage[i]->SetVisibleSingle( TRUE );
			m_pButtonImageSet[i]->SetVisibleSingle( TRUE );
		}
	}
	else if ( nPage == 3 )
	{
		SetPageFalse(0);
		SetPageFalse(1);
		SetPageFalse(2);
		SetPageFalse(4);

		m_pBasicLineBox->SetVisibleSingle( TRUE );
		m_pBasicLineBox1->SetVisibleSingle( TRUE );
		m_pBasicLineBox2->SetVisibleSingle( TRUE );
		m_pBasicLineBox3->SetVisibleSingle( TRUE );
		m_pBasicLineBox4->SetVisibleSingle( TRUE );
		m_pBasicLineBox5->SetVisibleSingle( TRUE );
		m_pBasicLineBox6->SetVisibleSingle( TRUE );
		m_pQuestionBox->SetVisibleSingle( TRUE );
		m_pScrollBar->SetVisibleSingle( TRUE );
		m_pAnswerBox->SetVisibleSingle( TRUE );
		m_pAnswerScrollBar->SetVisibleSingle( TRUE );

		m_pPageButton[3]->SetFlipYellow ( TRUE );
	}
	else if ( nPage == 4 )
	{
		SetPageFalse(0);
		SetPageFalse(1);
		SetPageFalse(3);
		SetPageFalse(2);
	}

}
void CDialogueWindow::TranslateTalkMessage ( SNpcTalk* pNpcTalk )
{
	switch ( pNpcTalk->m_nACTION )
	{
	case SNpcTalk::EM_DO_NOTHING:
		{
		}
		break;
	case SNpcTalk::EM_PAGE_MOVE:
		{
			LoadNode ( pNpcTalk->m_dwACTION_NO );
		}
		break;
	case SNpcTalk::EM_BASIC:
		{
			TranslateBasicMessage ( pNpcTalk );
		}
		break;
	case SNpcTalk::EM_QUEST_START:
		{
			LoadNode ( pNpcTalk->m_dwACTION_NO );

			TranslateQuestStartMessage ( pNpcTalk );
		}
		break;
	case SNpcTalk::EM_QUEST_STEP:
		{
			LoadNode ( pNpcTalk->m_dwACTION_NO );

			TranslateQuestStepMessage ( pNpcTalk );
		}
		break;
	};
}

void CDialogueWindow::TranslateBasicMessage ( SNpcTalk* pNpcTalk )
{

	// Need Add New Item Con.
	DWORD dwMsg = pNpcTalk->m_dwACTION_NO;
	DWORD dwGlobalID = pNpcTalk->m_dwGLOB_ID;
	DWORD *pParamA = pNpcTalk->m_dwNeedItem;
	DWORD paramB = pNpcTalk->m_dwACTION_PARAM2;

	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return;
	PGLCROWCLIENT pCrow = pLand->GetCrow ( m_sCrowID.dwID );
	if ( !pCrow )	return;

	switch ( dwMsg )
	{
	case SNpcTalk::EM_STORAGE:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			CInnerInterface::GetInstance().SetDefaultPosInterface( INVENTORY_WINDOW );
			CInnerInterface::GetInstance().SetDefaultPosInterface( STORAGE_WINDOW );
			CInnerInterface::GetInstance().ShowGroupFocus ( INVENTORY_WINDOW );
			CInnerInterface::GetInstance().SetStorageWindowOpen ( m_sCrowID.dwID );
		}
		break;
	case SNpcTalk::EM_MARKET:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			CInnerInterface::GetInstance().SetDefaultPosInterface( INVENTORY_WINDOW );
			CInnerInterface::GetInstance().SetDefaultPosInterface( DIALOGUE_WINDOW );
			CInnerInterface::GetInstance().SetMarketWindowOpen ( pCrow->m_pCrowData->sNativeID );
			CInnerInterface::GetInstance().ShowGroupFocus ( INVENTORY_WINDOW );
		}
		break;
	case SNpcTalk::EM_CURE:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			GLGaeaClient::GetInstance().GetCharacter()->ReqCure ( m_sCrowID.dwID, dwGlobalID );
		}
		break;
	case SNpcTalk::EM_STARTPOINT:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			GLGaeaClient::GetInstance().GetCharacter()->ReqReGenGate ( m_sCrowID.dwID );
		}
		break;

	case SNpcTalk::EM_CHAR_RESET:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			GLGaeaClient::GetInstance().GetCharacter()->ReqCharReset ( m_sCrowID.dwID );
		}
		break;

	// Need Add New Item Con.
	case SNpcTalk::EM_ITEM_TRADE:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			GLGaeaClient::GetInstance().GetCharacter()->ReqItemTrade ( m_sCrowID.dwID, dwGlobalID, pParamA, paramB );
		}
		break;

	case SNpcTalk::EM_BUSSTATION:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			
			//	NOTE : ¹ö½º Á¤·ùÀå ÀÎÅÍÆäÀÌ½º ·Îµå.
			CInnerInterface::GetInstance().SetBusWindowOpen ( m_sCrowID.dwID, pNpcTalk );
		}
		break;

	case SNpcTalk::EM_CLUB_NEW:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );

            //	NOTE : Å¬·´ ¸¸µé±â ½ÅÃ»
			CInnerInterface::GetInstance().SetClubMake ( m_sCrowID.dwID );
		}
		break;

	case SNpcTalk::EM_CLUB_UP:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			
			GLGaeaClient::GetInstance().GetCharacter()->ReqClubRank(m_sCrowID.dwID);
		}
		break;

	case SNpcTalk::EM_CD_CERTIFY:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			GLGaeaClient::GetInstance().GetCharacter()->ReqCDCertify(m_sCrowID.dwID);
		}
		break;

	case SNpcTalk::EM_COMMISSION:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );

			//	NOTE : ¼ö¼ö·á ÁöÁ¤
			//
			DoModal ( ID2GAMEINTEXT("MODAL_COMMISSION"), MODAL_INPUT, EDITBOX, MODAL_COMMISSION );
		}
		break;

	case SNpcTalk::EM_CLUB_STORAGE:
		{
			GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter ();
			GLCLUB& sCLUB = pCharacter->m_sCLUB;
			bool bVALID_CLUB = sCLUB.m_dwID!=CLUB_NULL;
			bool bMASTER = sCLUB.m_dwMasterID==pCharacter->m_dwCharID;

			if ( bVALID_CLUB && bMASTER )
			{
				CInnerInterface::GetInstance().HideGroup ( GetWndID () );

				pCharacter->ReqGetClubStorage ();

				//	NOTE : Ã¢°í ¶ç¿ì±â
				//			
				CInnerInterface::GetInstance().SetDefaultPosInterface( INVENTORY_WINDOW );
				CInnerInterface::GetInstance().SetDefaultPosInterface( CLUB_STORAGE_WINDOW );
				CInnerInterface::GetInstance().ShowGroupFocus ( INVENTORY_WINDOW );
				CInnerInterface::GetInstance().SetClubStorageWindowOpen ();
			}
			else
			{
				CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT("ONLY_CLUB_MASTER_USE_CLUBSTORAGE") );
			}
		}
		break;

	case SNpcTalk::EM_ITEM_REBUILD:	// ITEMREBUILD_MARK
		{
			CInnerInterface::GetInstance().HideGroup( GetWndID() );
			CInnerInterface::GetInstance().OpenItemRebuildWindow();
		}
		break;

	case SNpcTalk::EM_ODDEVEN:
		{
			CInnerInterface::GetInstance().HideGroup( GetWndID() );
			CInnerInterface::GetInstance().SetDefaultPosInterface( GAMBLE_DIALOGUE );
			CInnerInterface::GetInstance().SetDefaultPosInterface( INVENTORY_WINDOW );
			CInnerInterface::GetInstance().ShowGroupFocus ( GAMBLE_DIALOGUE );
			CInnerInterface::GetInstance().ShowGroupFocus ( INVENTORY_WINDOW );
		}
		break;
	case SNpcTalk::EM_RECOVERY_EXP:
		{
			CInnerInterface::GetInstance().HideGroup( GetWndID() );
			GLGaeaClient::GetInstance().GetCharacter()->ReqGetReExpNpc( m_sCrowID.dwID );
		}
		break;
	case SNpcTalk::EM_RANDOM_PAGE:
		{
			int nCnt = MAX_RANDOM_PAGE;

			for ( int i = 0; i < MAX_RANDOM_PAGE; ++i )
			{
				if ( pNpcTalk->m_dwRandomPageID[i] == UINT_MAX )
				{
					nCnt = i;
					break;
				}
			}

			if ( nCnt <= 0 ) 
			{
				CDebugSet::ToLogFile( "Random Page Not Found [%s]",m_DialogueSet.m_strFileName );
				break;
			}
			
			int nChoice = int ( rand() % nCnt );

			LoadNode( pNpcTalk->m_dwRandomPageID[nChoice], true, pNpcTalk->m_dwRandomTime );
		}
		break;
	case SNpcTalk::EM_ITEMSEARCH_PAGE:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			CInnerInterface::GetInstance().HideGroup( ITEM_SEARCH_RESULT_WINDOW );
			CInnerInterface::GetInstance().SetDefaultPosInterface( ITEM_SHOP_SEARCH_WINDOW );
			CInnerInterface::GetInstance().ShowGroupFocus( ITEM_SHOP_SEARCH_WINDOW );
		}
		break;

	case SNpcTalk::EM_ATTENDANCE_BOOK:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			CInnerInterface::GetInstance().ShowGroupFocus ( ATTENDANCE_BOOK_WINDOW );
		}
		break;
	case SNpcTalk::EM_ITEM_MIX:
		{
			CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			CInnerInterface::GetInstance().OpenItemMixWindow( m_sCrowID.dwID );
		}
		break;
	};
}

void CDialogueWindow::TranslateQuestStartMessage ( SNpcTalk* pNpcTalk )
{
	GASSERT(pNpcTalk&&"CDialogueWindow::TranslateQuestStartMessage");

	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return;
	PGLCROWCLIENT pCrow = pLand->GetCrow ( m_sCrowID.dwID );
	if ( !pCrow )	return;

	for ( int i = 0; i < MAX_QUEST_START; ++i )
	{
		if ( pNpcTalk->m_dwQuestStartID[i] != UINT_MAX && pNpcTalk->DoTEST(m_pCHAR, i))
		{
			GLGaeaClient::GetInstance().GetCharacter()->ReqQuestStart ( 
				m_sCrowID.dwID, pNpcTalk->m_dwGLOB_ID, pNpcTalk->m_dwQuestStartID[i] );
		}
	}
}

void CDialogueWindow::TranslateQuestStepMessage ( SNpcTalk* pNpcTalk )
{
	GASSERT(pNpcTalk&&"CDialogueWindow::TranslateQuestStepMessage");

	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand )	return;
	PGLCROWCLIENT pCrow = pLand->GetCrow ( m_sCrowID.dwID );
	if ( !pCrow )	return;

	GLGaeaClient::GetInstance().GetCharacter()->ReqQuestStepNpcTalk ( m_sCrowID.dwID,
		pNpcTalk->m_dwGLOB_ID, pNpcTalk->m_dwACTION_PARAM1, pNpcTalk->m_dwACTION_PARAM2 );
}

void CDialogueWindow::LoadBasicTalk ()
{
	if ( !m_pDialogueCase ) return ;
	const std::string str = m_pDialogueCase->GetBasicTalk ();

	m_pQuestionBox->SetText ( str.c_str(), NS_UITEXTCOLOR::WHITE ); // QUESTION DIALOGUE

	int nTotal = m_pQuestionBox->GetTotalLine ();
	int nViewPerPage = m_pQuestionBox->GetVisibleLine ();
	CBasicScrollThumbFrame* const pThumbFrame = m_pScrollBar->GetThumbFrame ();
	pThumbFrame->SetState ( nTotal, nViewPerPage );
	pThumbFrame->SetPercent ( 0.0f );
}

void CDialogueWindow::LoadButtonTalk ( bool bRandom )
{
	m_pAnswerBox->ClearText ();

	static const int nKEYWORDSIZE = 10;
	static const CString strKeyword[nKEYWORDSIZE] = 
	{
		"DIALOGUE_ICON_HEAL",
		"DIALOGUE_ICON_TRADE",
		"DIALOGUE_ICON_STARTPOINT",
		"DIALOGUE_ICON_STORAGE",
		"DIALOGUE_ICON_MARKET",
		"DIALOGUE_ICON_RESETPOINT",
		"DIALOGUE_ICON_BUS",
		"DIALOGUE_ICON_QUEST_START",
		"DIALOGUE_ICON_QUEST_ING",
		"DIALOGUE_ICON_TALK",
	};

	enum
	{
		ICON_HEAL,
		ICON_TRADE,
		ICON_STARTPOINT,
		ICON_STORAGE,
		ICON_MARKET,
		ICON_RESETPOINT,
		ICON_BUS,
		ICON_QUEST_START,
		ICON_QUEST_ING,
		ICON_QUEST_TALK,
	};

	//	¹öÆ° ÅØ½ºÆ® ¼³Á¤
	if ( !m_pDialogueCase ) return ;
	CNpcTalkControl* pNpcTalkControl = m_pDialogueCase->GetTalkControl ();
	if ( pNpcTalkControl )
	{
		CNpcTalkControl::NPCMAP* pMap = pNpcTalkControl->GetTalkMap ();
		CNpcTalkControl::NPCMAP_IT iter = pMap->begin();
		CNpcTalkControl::NPCMAP_IT iter_end = pMap->end();

		vector<SNpcTalk*> vecTalk;
		vecTalk.reserve( pMap->size() );

		for ( ; iter != iter_end; ++iter )
		{
			SNpcTalk* pNpcTalk = (*iter).second;
			vecTalk.push_back( pNpcTalk );
		}
		
		if ( bRandom )
		{
			random_shuffle( vecTalk.begin(), vecTalk.end() );			
		}

		vector<SNpcTalk*>::iterator	pos = vecTalk.begin();
		vector<SNpcTalk*>::iterator	pos_end = vecTalk.end();

		for ( ; pos != pos_end; ++pos )
		{
			SNpcTalk* pNpcTalk = (SNpcTalk*) (*pos);

			//	Note : Á¶°Ç¿¡ ºÎÇÕÇÏÁö ¸øÇÒ °æ¿ì Ãß°¡ÇÏÁö ¾ÊÀ½.
			if ( !pNpcTalk->DoTEST(m_pCHAR) )	continue;
			
			CString strAnswerTalk = pNpcTalk->GetTalk();			

            int nImageType = 0;	
			D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
			switch ( pNpcTalk->m_nACTION )
			{
			case SNpcTalk::EM_QUEST_START:
				{
					dwColor = NS_UITEXTCOLOR::LIGHTCYAN;
					nImageType = ICON_QUEST_START;

					//	NOTE : ºñ¿ëÀÌ ÀÖÀ» °æ¿ì Ãß°¡
					DWORD dwQuestID = pNpcTalk->m_dwQuestStartID[0];
					GLQUEST* pQuest = GLQuestMan::GetInstance().Find ( dwQuestID );
					if ( !pQuest )
					{
						CDebugSet::ToLogFile ( "quest id = %d ÀÇ Á¤º¸¸¦ °¡Á®¿ÀÁö ¸øÇÏ¿´½À´Ï´Ù.", dwQuestID );
						continue;
					}

					const DWORD dwBeginMoney = pQuest->m_dwBeginMoney;
					if ( dwBeginMoney )
					{
						CString strQuestCost;
						strQuestCost.Format ( " [%s:%d]", ID2GAMEWORD ( "QUEST_BEGIN_MONEY" ), dwBeginMoney );
						strAnswerTalk += strQuestCost;
					}					
				}
				break;

			case SNpcTalk::EM_QUEST_STEP:
				{
					dwColor = NS_UITEXTCOLOR::LIGHTCYAN;
					nImageType = ICON_QUEST_START;
				}
				break;

			case SNpcTalk::EM_BASIC:
				{
					switch ( pNpcTalk->m_dwACTION_NO )
					{
					//case SNpcTalk::EM_STORAGE:	nImageType = ICON_STORAGE; break;
					//case SNpcTalk::EM_MARKET:	nImageType = ICON_MARKET; break;
					case SNpcTalk::EM_CURE:		nImageType = ICON_HEAL; break;
					case SNpcTalk::EM_STARTPOINT: nImageType = ICON_STARTPOINT; break;
					//case SNpcTalk::EM_CHAR_RESET: nImageType = ICON_RESETPOINT; break;
					//case SNpcTalk::EM_ITEM_TRADE: nImageType = ICON_TRADE; break;
					default:	nImageType = ICON_QUEST_TALK;		break;
					}
				}
				break;

			case SNpcTalk::EM_PAGE_MOVE:
				{
					nImageType = ICON_QUEST_TALK;
				}
				break;

			}

			nImageType = ( nImageType >= nKEYWORDSIZE )?nKEYWORDSIZE-1:nImageType;

			int nIndex = m_pAnswerBox->AddText ( strAnswerTalk, dwColor );
			m_pAnswerBox->SetTextData ( nIndex, pNpcTalk->m_dwNID );				 
			m_pAnswerBox->SetTextImage ( nIndex, strKeyword[nImageType] );
		}

		int nTotal = m_pAnswerBox->GetTotalLine ();
		int nViewPerPage = m_pAnswerBox->GetVisibleLine ();
		CBasicScrollThumbFrame* const pThumbFrame = m_pAnswerScrollBar->GetThumbFrame ();
		pThumbFrame->SetState ( nTotal, nViewPerPage );
		pThumbFrame->SetPercent ( 0.0f );
	}
}

void CDialogueWindow::LoadNode( DWORD dwNID, bool bRandom, DWORD dwRandomTime )
{
	m_pDialogue = m_DialogueSet.GetDialogue ( dwNID );
	GASSERT(m_pDialogue&&"m_DialogueSet.GetDialogue()");
	if ( !m_pDialogue )			return;
	
	DWORD dwIndex = m_pDialogue->FindConditionSatisfied ( m_pCHAR );
	GASSERT(dwIndex!=UINT_MAX&&"m_pDialogue->FindConditionSatisfied()");
	if ( dwIndex==UINT_MAX )	return;

	CNpcDialogueCase* pCase = m_pDialogue->GetDlgCase(dwIndex);	
	GASSERT(pCase&&"m_pDialogueCase = NULL");
	m_pDialogueCase = pCase;

	m_dwRandomTime = dwRandomTime;
	m_fRandomTime = 0.0f;

    //
	if ( m_dwRandomTime > 0 )
	{
		m_pRandomTimeButton->SetVisibleSingle( TRUE );
		m_pRandomTimeBack->SetVisibleSingle( TRUE );
		m_pRandomTimeText->SetVisibleSingle( TRUE );
		
		CString strTime;
		strTime.Format( "%d", m_dwRandomTime );

		m_pRandomTimeText->SetText( strTime, NS_UITEXTUTIL::BLACK );

	}
	else
	{
		m_pRandomTimeButton->SetVisibleSingle( FALSE );
		m_pRandomTimeBack->SetVisibleSingle( FALSE );
		m_pRandomTimeText->SetVisibleSingle( FALSE );
	}

	LoadBasicTalk ();
	LoadButtonTalk ( bRandom );
}

BOOL CDialogueWindow::SetDialogueData ( STARGETID sCrowID, GLCHARLOGIC *pCHAR )
{
	GASSERT ( pCHAR );
	if ( sCrowID.emCrow != CROW_NPC )	return FALSE;	

	m_sCrowID = sCrowID;
	m_pCHAR = pCHAR;

	PGLCROWCLIENT pCrow = GLGaeaClient::GetInstance().GetActiveMap()->GetCrow(sCrowID.dwID);
	if ( !pCrow )
		return FALSE;
	else
	{
		InitMarket( pCrow->m_pCrowData->sNativeID );
		m_pMoneyItem->ClearText();
		MoneyTotal = 0;
		m_pCountSlot = 0;
	}

	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData( pCrow->m_pCrowData->sNativeID );
	if ( m_DialogueSet.Load ( pCrowData->GetTalkFile() ) )
	{
		LoadNode ( nSTARTINDEX );
		return TRUE;
	}

	return FALSE;
}
void CDialogueWindow::GetItemIndex ( int* pnPosX, int* pnPosY )
{
	*pnPosX = m_nPosX;
	*pnPosY = m_nPosY;
}

void CDialogueWindow::SetItemIndex ( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

int	 CDialogueWindow::GetPageIndex ()
{
	return m_nPageIndex;
}

SNATIVEID	CDialogueWindow::GetMarketID ()
{
	return m_sMarketID;
}

SINVENITEM&	CDialogueWindow::GetItem ( int nPosX, int nPosY )
{
	return m_pPage[m_nPageIndex]->GetItem ( nPosX, nPosY );
}
void CDialogueWindow::InitMarket()
{
	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( m_sMarketID );
	if ( pCrowData )
	{
		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			GLInventory& ref_Inventory = *pCrowData->GetSaleInven(i);
			m_pPage[i]->UnLoadItemPage ();
			m_pPage[i]->LoadItemPage ( ref_Inventory );
			m_pInterestItemPage[i]->UnLoadItemPage ();
			m_pInterestItemPage[i]->LoadInterestItem ( ref_Inventory );

			//	ÃßÈÄ¿¡ ¼öÁ¤
			CString strTabText = pCrowData->GetSaleType(i).c_str();
			if( strTabText == "")
			{
				m_pPageButton[i]->SetVisibleSingle( FALSE );
			}
			else
			{
				m_pPageButton[i]->SetOneLineText ( strTabText );
				m_pPageButton[i]->SetVisibleSingle( TRUE );
			}
		}
	}
}
void CDialogueWindow::InitMarket ( SNATIVEID sNativeID )
{
	m_sMarketID = sNativeID;

	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( m_sMarketID );
	if ( pCrowData )
	{
		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			GLInventory& ref_Inventory = *pCrowData->GetSaleInven(i);
			m_pPage[i]->UnLoadItemPage ();
			m_pPage[i]->LoadItemPage ( ref_Inventory );
			m_pInterestItemPage[i]->UnLoadItemPage ();
			m_pInterestItemPage[i]->LoadInterestItem ( ref_Inventory );

			//	ÃßÈÄ¿¡ ¼öÁ¤
			CString strTabText = pCrowData->GetSaleType(i).c_str();
			if( strTabText == "")
			{
				m_pPageButton[i]->SetVisibleSingle( FALSE );
			}
			else
			{
				m_pPageButton[i]->SetOneLineText ( strTabText );
				m_pPageButton[i]->SetVisibleSingle( TRUE );
			}
		}
	}	

	SetVisible ( NEW_MARKET_PAGE1 );
}

BOOL CDialogueWindow::IsUsingMaketPage( int nPage )
{
	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( m_sMarketID );
	GLInventory& ref_Inventory = *pCrowData->GetSaleInven(nPage);

	if( ref_Inventory.GetNumItems() > 0 )
		return true;
	else
		return false;
}
