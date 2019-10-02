#include "StdAfx.h"
#include "TradeInventoryPage.h"
#include "ItemSlotEx.h"
#include "BasicScrollBarEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../Interface/GameTextControl.h"
#include "GLGaeaClient.h"
#include "GLInventory.h"
#include "GLGaeaClient.h"
#include "d3dfont.h"
#include "InnerInterface.h"
#include "UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CTradeInventoryPage::nSTARTLINE = 0;
const int CTradeInventoryPage::nOUTOFRANGE = -1;

CTradeInventoryPage::CTradeInventoryPage () :
	//m_pScrollBar ( NULL ),
	m_nCurPos ( -1 ),
	m_nONE_VIEW_SLOT ( nONE_VIEW_SLOT_DEFAULT )
{
	memset ( m_pItemSlotArray, 0, sizeof( m_pItemSlotArray ) );
	memset ( m_pItemSlotArrayDummy, 0, sizeof( m_pItemSlotArrayDummy ) );
	memset ( m_Button, 0, sizeof ( CUIControl* ) * 3 );	
	memset ( m_ButtonSet, 0, sizeof ( CUIControl* ) * 3 );	
	memset ( m_ButtonText, 0, sizeof ( CBasicTextBox* ) * 3 );
}

CTradeInventoryPage::~CTradeInventoryPage ()
{
}

CUIControl*	CTradeInventoryPage::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

void CTradeInventoryPage::CreateSubControl ()
{

	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW );

	CString strSlotKeyword1[nMAX_ONE_VIEW_SLOT3] =
	{
		"TRADEINVENTORYSLOT_ITEM_SLOT0",
		"TRADEINVENTORYSLOT_ITEM_SLOT1",
		"TRADEINVENTORYSLOT_ITEM_SLOT2",
		"TRADEINVENTORYSLOT_ITEM_SLOT3",
		"TRADEINVENTORYSLOT_ITEM_SLOT4",
		"TRADEINVENTORYSLOT_ITEM_SLOT5",
		"TRADEINVENTORYSLOT_ITEM_SLOT6",
		"TRADEINVENTORYSLOT_ITEM_SLOT7",
		"TRADEINVENTORYSLOT_ITEM_SLOT8",
		"TRADEINVENTORYSLOT_ITEM_SLOT9",
		"TRADEINVENTORYSLOT_ITEM_SLOT10",
		"TRADEINVENTORYSLOT_ITEM_SLOT11",
		"TRADEINVENTORYSLOT_ITEM_SLOT12",
		"TRADEINVENTORYSLOT_ITEM_SLOT13",
		"TRADEINVENTORYSLOT_ITEM_SLOT14",
		"TRADEINVENTORYSLOT_ITEM_SLOT15",
		"TRADEINVENTORYSLOT_ITEM_SLOT16",
		"TRADEINVENTORYSLOT_ITEM_SLOT17",
		"TRADEINVENTORYSLOT_ITEM_SLOT18",
		"TRADEINVENTORYSLOT_ITEM_SLOT19",
		"TRADEINVENTORYSLOT_ITEM_SLOT20",
		"TRADEINVENTORYSLOT_ITEM_SLOT21",
		"TRADEINVENTORYSLOT_ITEM_SLOT22",
		"TRADEINVENTORYSLOT_ITEM_SLOT23",
		"TRADEINVENTORYSLOT_ITEM_SLOT24",
		"TRADEINVENTORYSLOT_ITEM_SLOT25",
		"TRADEINVENTORYSLOT_ITEM_SLOT26",
		"TRADEINVENTORYSLOT_ITEM_SLOT27",
		"TRADEINVENTORYSLOT_ITEM_SLOT28",
		"TRADEINVENTORYSLOT_ITEM_SLOT29"
	};

	// Button page

	CString strButton[3] =
	{
		"INVENTORY_BUTTON0",
		"INVENTORY_BUTTON1",
		"INVENTORY_BUTTON2"
	};

	CString strButtonSet[3] =
	{
		"INVENTORY_BUTTON0_F",
		"INVENTORY_BUTTON1_F",
		"INVENTORY_BUTTON2_F"
	};

	CString strButtonText[3] =
	{
		"INVENTORY_BUTTON_TEXT0",
		"INVENTORY_BUTTON_TEXT1",
		"INVENTORY_BUTTON_TEXT2"
	};

	for ( int i = 0; i < 3 ; i++ )
	{
		m_Button[i] = new CUIControl;
		m_Button[i]->CreateSub ( this, strButton[i].GetString (), UI_FLAG_DEFAULT, INVENTORY_BUTTON0 + i );
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_Button[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_Button[i] );

		m_ButtonSet[i] = new CUIControl;
		m_ButtonSet[i]->CreateSub ( this, strButtonSet[i].GetString (), UI_FLAG_DEFAULT );
		if ( m_ButtonSet[0] )
		{
			m_ButtonSet[0]->SetVisibleSingle ( TRUE );
		}
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
		m_ButtonSet[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_ButtonSet[i] );

		m_ButtonText[i] = new CBasicTextBox;
		m_ButtonText[i]->CreateSub ( this, strButtonText[i].GetString (), UI_FLAG_DEFAULT );
		m_ButtonText[i]->SetFont ( pFont8 );
		m_ButtonText[i]->SetTextAlign ( TEXT_ALIGN_LEFT );	
		m_ButtonText[i]->AddText ( ID2GAMEWORD ( "NEW_INVENTORY_BUTTON_SLOT", i ) );
		RegisterControl ( m_ButtonText[i] );
	}

	//	더미 슬롯
	for ( int i = 0; i < nMAX_ONE_VIEW_SLOT3; i++ )
	{
		m_pItemSlotArrayDummy[i] = CreateControl ( strSlotKeyword1[i].GetString () );
	}
	
	//	실제 데이타
	for ( int i = 0; i < EM_INVENSIZE_Y_FORCE; i++ )
	{
		m_pItemSlotArray[i] = CreateItemSlot ( strSlotKeyword1[0], ITEM_SLOT00 + i );
	}
	
	{	//	스크롤바
		//m_pScrollBar = new CBasicScrollBarEx;
		//m_pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
		//m_pScrollBar->CreateBaseScrollBar ( "INVENTORY_PAGE_SCROLL" );
		//m_pScrollBar->GetThumbFrame()->SetState ( EM_INVENSIZE_Y_FORCE, m_nONE_VIEW_SLOT );
		//RegisterControl ( m_pScrollBar );
	}

	ResetAllItemSlotRender ( 10,30 );
	SetItemSlotRender ( 0, 10 );
}

void CTradeInventoryPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE, nOUTOFRANGE );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	//	NOTE
	//		사용/가부 설정
	UpdateBLOCK ();

	/*if ( m_pScrollBar )
	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
		int nTotal = pThumbFrame->GetTotal ();

		if ( nTotal < m_nONE_VIEW_SLOT ) return ;
	
		const int nViewPerPage = pThumbFrame->GetViewPerPage ();
		if ( nViewPerPage <= nTotal )
		{
			int nCurPos = nSTARTLINE;
			const int nMovableLine = nTotal - nViewPerPage;
			float fPercent = pThumbFrame->GetPercent ();

			nCurPos = (int)floor(fPercent * nMovableLine);
			if ( nCurPos < nSTARTLINE ) nCurPos = nSTARTLINE;

			if ( m_nCurPos == nCurPos ) return;

			m_nCurPos = nCurPos;

			ResetAllItemSlotRender ( nTotal );
			SetItemSlotRender ( nCurPos, nCurPos + nViewPerPage );
		}
	}*/
}

void CTradeInventoryPage::ResetAllItemSlotRender ( int index ,int nTotal )
{
	if ( nTotal < 0 ) return ;

	for ( int i = index; i < nTotal; i++ )
	{
		CItemSlotEx* pItemSlot = m_pItemSlotArray[i];
		if ( pItemSlot )
		{
			pItemSlot->SetVisibleSingle ( FALSE );
		}
	}
}

void CTradeInventoryPage::SetItemSlotRender ( int nStartIndex, int nTotal )
{
	if ( nTotal < 0 ) return ;

	const UIRECT& rcParentPos = GetGlobalPos ();

	for ( int i = nStartIndex; i < nTotal; i++ )
	{
		CItemSlotEx* pItemSlot = m_pItemSlotArray[i];
		if ( pItemSlot )
		{
			int nAbsoluteIndex = i - nStartIndex;

			CUIControl* pDummyControl = m_pItemSlotArrayDummy[nAbsoluteIndex];			
			const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
			const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();

			pItemSlot->SetLocalPos ( rcSlotLocalPos );
			pItemSlot->SetGlobalPos ( rcSlotPos );

			pItemSlot->SetVisibleSingle ( TRUE );
		}
	}
}

CItemSlotEx* CTradeInventoryPage::CreateItemSlot ( CString strKeyword, UIGUID ControlID )
{
	CItemSlotEx* pItemSlot = new CItemSlotEx;
	pItemSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pItemSlot->CreateSubTradeInventory ( EM_INVENSIZE_X );
	RegisterControl ( pItemSlot );

	return pItemSlot;
}



void CTradeInventoryPage::SetItemIndex ( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void CTradeInventoryPage::GetItemIndex ( int* pnPosX, int* pnPosY )
{
	*pnPosX = m_nPosX;
	*pnPosY = m_nPosY;
}

void CTradeInventoryPage::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( ITEM_SLOT00 <= ControlID && ControlID < ITEM_SLOT_END )
	{
		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{
			const int nPosY = ControlID - ITEM_SLOT00;
			CItemSlot* pSlot = m_pItemSlotArray[nPosY];
			const int nPosX = pSlot->GetItemIndex ();

			if ( nPosY < 0 || nPosX < 0 ) return ;

			SetItemIndex ( nPosX, nPosY );
		}
	}
	switch ( ControlID )
	{
	case INVENTORY_BUTTON0:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				TRADEINVENTORY1();
			}
		}
		break;
	case INVENTORY_BUTTON1:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				//CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("FUNCTION_DISABLED") );
				//return;
				TRADEINVENTORY2();
			}
		}
		break;
	case INVENTORY_BUTTON2:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				//CInnerInterface::GetInstance().PrintMsgTextDlg ( NS_UITEXTCOLOR::DISABLE, ID2GAMEINTEXT("FUNCTION_DISABLED") );
				//return;
				TRADEINVENTORY3();
			}
		}
		break;
	}
}

void CTradeInventoryPage::TRADEINVENTORY1()
{
	for ( int i = 0; i < 3; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[0]->SetVisibleSingle ( TRUE );
	m_Button[0]->SetVisibleSingle ( FALSE );
	ResetAllItemSlotRender ( 10,30 );
	SetItemSlotRender ( 0, 10 );
}
void CTradeInventoryPage::TRADEINVENTORY2()
{
	for ( int i = 0; i < 3; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[1]->SetVisibleSingle ( TRUE );
	m_Button[1]->SetVisibleSingle ( FALSE );
	ResetAllItemSlotRender ( 0,10 );
	ResetAllItemSlotRender ( 20,30 );
	SetItemSlotRender ( 10, 20 );
}
void CTradeInventoryPage::TRADEINVENTORY3()
{
	for ( int i = 0; i < 3; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[2]->SetVisibleSingle ( TRUE );
	m_Button[2]->SetVisibleSingle ( FALSE );
	ResetAllItemSlotRender ( 0,20 );
	SetItemSlotRender ( 20, 30 );
}

void CTradeInventoryPage::LoadItem ( SINVENITEM& ref_InvenItem )
{	
	int nPosX = ref_InvenItem.wPosX;
	int nPosY = ref_InvenItem.wPosY;
	m_pItemSlotArray[nPosY]->SetItemImage ( nPosX, ref_InvenItem );
}

void CTradeInventoryPage::UnLoadItemPage ()
{
	for ( int x = 0; x < EM_INVENSIZE_X; x++ )
	{		
		for ( int y = 0; y < EM_INVENSIZE_Y_FORCE; y++ )
		{
			UnLoadItem ( x, y );
		}
	}
}

SINVENITEM& CTradeInventoryPage::GetItem ( int nPosX, int nPosY )
{
	return m_pItemSlotArray[nPosY]->GetItemImage ( nPosX );
}

void CTradeInventoryPage::UnLoadItem ( int nPosX, int nPosY )
{
	m_pItemSlotArray[nPosY]->ResetItemImage ( nPosX );
}

void CTradeInventoryPage::LoadItemPage ( GLInventory &ItemData )
{
	GLInventory::CELL_MAP *pItemList = ItemData.GetItemList();
	
	if ( pItemList->size () > (EM_INVENSIZE_Y_FORCE * EM_INVENSIZE_X) )
	{
		GASSERT ( 0 && "인터페이스 사이즈보다, 데이타크기가 큽니다." );
		return ;
	}


	{	//	삭제

		GLInventory::CELL_MAP_ITER iter = pItemList->begin();
		GLInventory::CELL_MAP_ITER iter_end = pItemList->end();

		for ( WORD x = 0; x < EM_INVENSIZE_X; x++ )
		{
			for ( WORD y = 0; y < EM_INVENSIZE_Y_FORCE; y++ )
			{
				SINVENITEM& ref_InvenItem = GetItem ( x, y );
				if ( ref_InvenItem.sItemCustom.sNativeID != NATIVEID_NULL() )
				{
					GLInventory::CELL_KEY foundkey ( x, y );
					GLInventory::CELL_MAP_ITER found = pItemList->find ( foundkey );
					if ( found == iter_end )
					{
						UnLoadItem ( x, y );
					}
				}
			}
		}
	}

	{	//	등록
		GLInventory::CELL_MAP_ITER iter = pItemList->begin();
		GLInventory::CELL_MAP_ITER iter_end = pItemList->end();

		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;
			SINVENITEM& ref_InvenItemOld = GetItem ( pInvenItem->wPosX, pInvenItem->wPosY );
			if ( *pInvenItem != ref_InvenItemOld )
			{
				LoadItem ( *pInvenItem );
			}	
		}
	}
}

void  CTradeInventoryPage::UpdateFlipItem ( GLInventory& ref_TradeInventory )
{
	GLInventory::CELL_MAP_ITER iter = ref_TradeInventory.GetItemList()->begin();
	GLInventory::CELL_MAP_ITER iter_end = ref_TradeInventory.GetItemList()->end();

	ResetAllFlipItem ();
	for ( ; iter != iter_end; iter++ )
	{
		SINVENITEM* pInvenItem = (*iter).second;
		if ( pInvenItem )
		{
			int nPosX = pInvenItem->wBackX;
			int nPosY = pInvenItem->wBackY;
			m_pItemSlotArray[nPosY]->SetFlipItem ( nPosX, TRUE );
		}
	}
}


void CTradeInventoryPage::ResetAllFlipItem ()
{
	for ( WORD y = 0; y < EM_INVENSIZE_Y; y++ )
	{
		for ( WORD x = 0; x < EM_INVENSIZE_X; x++ )
		{
			m_pItemSlotArray[y]->SetFlipItem ( x, FALSE );
		}
	}
}

void CTradeInventoryPage::UpdateBLOCK ()
{
	const WORD& wAddINVENLINE = GLGaeaClient::GetInstance().GetCharacter()->GetOnINVENLINE();
	int nUSABLE_INVENLINE = EM_INVEN_DEF_SIZE_Y + wAddINVENLINE;

	if ( EM_INVENSIZE_Y_FORCE < nUSABLE_INVENLINE )
	{		
		GASSERT ( 0 && "데이타 오류입니다." );

		nUSABLE_INVENLINE = EM_INVENSIZE_Y_FORCE;
	}
	
	//	사용 가능
	for ( int i = 0; i < nUSABLE_INVENLINE; i++ )
		m_pItemSlotArray[i]->ResetBLOCK ();

	//	사용 불가능
	for ( int i = nUSABLE_INVENLINE; i < EM_INVENSIZE_Y; i++ )
		m_pItemSlotArray[i]->SetBLOCK ();
}

void CTradeInventoryPage::SetOneViewSlot ( const int& nMAX_ONE_VIEW )
{
	m_nONE_VIEW_SLOT = nMAX_ONE_VIEW;
	m_nCurPos = -1;
	//m_pScrollBar->GetThumbFrame()->SetState ( EM_INVENSIZE_Y_FORCE, nMAX_ONE_VIEW );
}