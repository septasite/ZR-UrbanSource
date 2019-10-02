#include "StdAfx.h"
#include "MarketWindow.h"
#include "MarketPage.h"
#include "DialogueWindow.h"
#include "BasicTextButton.h"
#include "GameTextControl.h"
#include "GLGaeaClient.h"
#include "InnerInterface.h"
#include "GLItemMan.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const	int	CNewDialogueWindow::nOUTOFRANGE = -1;

CNewDialogueWindow::CNewDialogueWindow () :
	m_nPageIndex ( nOUTOFRANGE )
{
	//memset ( m_pPage, 0, sizeof ( CMarketPage* ) * nMAXPAGE );
	//memset ( m_pPageButton, 0, sizeof ( CBasicTextButton* ) * nMAXPAGE );	
}

CNewDialogueWindow::~CNewDialogueWindow ()
{
}

void CNewDialogueWindow::CreateSubControl ()
{
	CString strButtonKeyword[nMAXPAGE] = 
	{
		"DIALOG_WINDOW_PAGE_BUTTON0",
		"DIALOG_WINDOW_PAGE_BUTTON1",
		"DIALOG_WINDOW_PAGE_BUTTON2",
		"DIALOG_WINDOW_PAGE_BUTTON3"
	};

	for ( int i = 0; i < nMAXPAGE; i++ )
	{
		//m_pPage[i] = CreateMarketPage ( MARKET_PAGE0 + i );		
		m_pPageButton[i] = CreateTextButton ( strButtonKeyword[i].GetString (), DIALOG_WINDOW_PAGE_BUTTON0 + i, (char*)ID2GAMEWORD ( "DIALOG_WINDOW_PAGE_BUTTON", i ) );
	}

	//SetVisiblePage ( DIALOG_PAGE0 );
}

CBasicTextButton*  CNewDialogueWindow::CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE19;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON19", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;
}

BOOL CNewDialogueWindow::IsUsingMaketPage( int nPage )
{
	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( m_sMarketID );
	GLInventory& ref_Inventory = *pCrowData->GetSaleInven(nPage);

	if( ref_Inventory.GetNumItems() > 0 )
		return true;
	else
		return false;
}

void CNewDialogueWindow::SetVisiblePage ( int nPage )
{
	if ( nPage < MARKET_PAGE0 || MARKET_PAGE2 < nPage )
	{
		GASSERT ( 0 && "영역을 넘어서는 페이지입니다." );
		return ;
	}

	{	//	리셋
		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			//m_pPage[i]->SetVisibleSingle ( FALSE );
			m_pPageButton[i]->SetFlip ( FALSE );
		}
	}

	m_nPageIndex = nPage - MARKET_PAGE0;
	//m_pPage[m_nPageIndex]->SetVisibleSingle ( TRUE );
	m_pPageButton[m_nPageIndex]->SetFlip ( TRUE );
}

void CNewDialogueWindow::InitMarket ( SNATIVEID sNativeID )
{
	m_sMarketID = sNativeID;

	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( m_sMarketID );
	if ( pCrowData )
	{
		for ( int i = 0; i < nMAXPAGE; i++ )
		{
			GLInventory& ref_Inventory = *pCrowData->GetSaleInven(i);
			//m_pPage[i]->UnLoadItemPage ();
			//m_pPage[i]->LoadItemPage ( ref_Inventory );

			//	추후에 수정
			CString strTabText = pCrowData->GetSaleType(i).c_str();
			m_pPageButton[i]->SetOneLineText ( strTabText );
		}
	}	

	//SetVisiblePage ( MARKET_PAGE0 );
}

void CNewDialogueWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );


    if( ControlID == ET_CONTROL_TITLE || ET_CONTROL_TITLE_F == ControlID )
	{
		if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
		{
			CInnerInterface::GetInstance().SetDefaultPosInterface( DIALOGUE_WINDOW_NEW );
			return ;
		}
	}	
	if ( ControlID == ET_CONTROL_BUTTON )
	{
		if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
		{
			CInnerInterface::GetInstance().SetMarketWindowClose ();
			return ;
		}
	}
}
