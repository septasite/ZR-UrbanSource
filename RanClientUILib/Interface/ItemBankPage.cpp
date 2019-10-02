#include "StdAfx.h"

#include "ItemBankPage.h"
#include "ItemSlot.h"
#include "BasicScrollBarEx.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../Interface/GameTextControl.h"
#include "d3dfont.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "InnerInterface.h"
#include "UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CItemBankPage::nSTARTLINE = 0;
const int CItemBankPage::nOUTOFRANGE = -1;

CItemBankPage::CItemBankPage (): 
	//m_pScrollBar ( NULL )
	m_nCurPos ( -1 )
{
	memset( m_pItemSlotArray, 0, sizeof( m_pItemSlotArray ) );
	memset( m_pItemSlotArrayDummy, 0, sizeof( m_pItemSlotArrayDummy ) );
	memset ( m_Button, 0, sizeof ( CUIControl* ) * 4 );	
	memset ( m_ButtonSet, 0, sizeof ( CUIControl* ) * 4 );	
	memset ( m_ButtonText, 0, sizeof ( CBasicTextBox* ) * 4 );	
}

CItemBankPage::~CItemBankPage ()
{
}

CUIControl*	CItemBankPage::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

void CItemBankPage::CreateSubControl ()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_SHADOW_FLAG );

	static CString strSlotKeyword[nMAX_ONE_VIEW_SLOT] =
	{
		"ITEMBANK_ITEM_SLOT0",
		"ITEMBANK_ITEM_SLOT1",
		"ITEMBANK_ITEM_SLOT2",
		"ITEMBANK_ITEM_SLOT3",
		"ITEMBANK_ITEM_SLOT4",
		"ITEMBANK_ITEM_SLOT5",
		"ITEMBANK_ITEM_SLOT6",
		"ITEMBANK_ITEM_SLOT7",
		"ITEMBANK_ITEM_SLOT8",
		"ITEMBANK_ITEM_SLOT9",
		"ITEMBANK_ITEM_SLOT10",
		"ITEMBANK_ITEM_SLOT11",
		"ITEMBANK_ITEM_SLOT12",
		"ITEMBANK_ITEM_SLOT13",
		"ITEMBANK_ITEM_SLOT14",
		"ITEMBANK_ITEM_SLOT15",
		"ITEMBANK_ITEM_SLOT16",
		"ITEMBANK_ITEM_SLOT17",
		"ITEMBANK_ITEM_SLOT18",
		"ITEMBANK_ITEM_SLOT19",
		"ITEMBANK_ITEM_SLOT20",
		"ITEMBANK_ITEM_SLOT21",
		"ITEMBANK_ITEM_SLOT22",
		"ITEMBANK_ITEM_SLOT23",
		"ITEMBANK_ITEM_SLOT24",
		"ITEMBANK_ITEM_SLOT25",
		"ITEMBANK_ITEM_SLOT26",
		"ITEMBANK_ITEM_SLOT27",
		"ITEMBANK_ITEM_SLOT28",
		"ITEMBANK_ITEM_SLOT29",
		"ITEMBANK_ITEM_SLOT30",
		"ITEMBANK_ITEM_SLOT31",
		"ITEMBANK_ITEM_SLOT32",
		"ITEMBANK_ITEM_SLOT33",
		"ITEMBANK_ITEM_SLOT34",
		"ITEMBANK_ITEM_SLOT35",
		"ITEMBANK_ITEM_SLOT36",
		"ITEMBANK_ITEM_SLOT37",
		"ITEMBANK_ITEM_SLOT38",
		"ITEMBANK_ITEM_SLOT39",
	};

	// Button page

	CString strButton[4] =
	{
		"ITEMBANK_BUTTON0",
		"ITEMBANK_BUTTON1",
		"ITEMBANK_BUTTON2",
		"ITEMBANK_BUTTON3"
	};

	CString strButtonSet[4] =
	{
		"ITEMBANK_BUTTON0_F",
		"ITEMBANK_BUTTON1_F",
		"ITEMBANK_BUTTON2_F",
		"ITEMBANK_BUTTON3_F"
	};

	CString strButtonText[4] =
	{
		"ITEMBANK_BUTTON_TEXT0",
		"ITEMBANK_BUTTON_TEXT1",
		"ITEMBANK_BUTTON_TEXT2",
		"ITEMBANK_BUTTON_TEXT3"
	};

	for ( int i = 0; i < 4 ; i++ )
	{
		m_Button[i] = new CUIControl;
		m_Button[i]->CreateSub ( this, strButton[i].GetString (), UI_FLAG_DEFAULT, ITEMBANK_BUTTON0 + i );
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_Button[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_Button[i] );

		m_ButtonSet[i] = new CUIControl;
		m_ButtonSet[i]->CreateSub ( this, strButtonSet[i].GetString (), UI_FLAG_DEFAULT );	
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
		m_ButtonSet[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_ButtonSet[i] );

		m_ButtonText[i] = new CBasicTextBox;
		m_ButtonText[i]->CreateSub ( this, strButtonText[i].GetString (), UI_FLAG_DEFAULT );
		m_ButtonText[i]->SetFont ( pFont8 );
		m_ButtonText[i]->SetTextAlign ( TEXT_ALIGN_LEFT );	
		m_ButtonText[i]->AddText ( ID2GAMEWORD ( "NEW_ITEMBANK_BUTTON_SLOT", i ) );
		RegisterControl ( m_ButtonText[i] );
	}

	//	더미 슬롯
	for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ )
	{
		m_pItemSlotArrayDummy[i] = CreateControl ( strSlotKeyword[i].GetString () );
	}

	//	실제 데이타
	for ( int i = 0; i < ITEMBANK_INVEN_Y; i++ )
	{
		m_pItemSlotArray[i] = CreateItemSlot ( strSlotKeyword[i], ITEM_SLOT0 + i );
	}
	
	//	스크롤바
	//CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
	//pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
	//pScrollBar->CreateBaseScrollBar ( "ITEMBANK_PAGE_SCROLL" );
	//pScrollBar->GetThumbFrame()->SetState ( ITEMBANK_INVEN_Y, nMAX_ONE_VIEW_SLOT );
	//RegisterControl ( pScrollBar );
	//m_pScrollBar = pScrollBar;	

	//SetItemSlotRender ( nSTARTLINE, nMAX_ONE_VIEW_SLOT );
	ResetAllItemSlotRender ( 10,40 );
	SetItemSlotRender ( 0, 10 );
}

void CItemBankPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE, nOUTOFRANGE );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	/*if ( m_pScrollBar )
	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
		int nTotal = pThumbFrame->GetTotal ();

		if ( nTotal <= nMAX_ONE_VIEW_SLOT ) return ;

		const int nViewPerPage = pThumbFrame->GetViewPerPage ();
		if ( nViewPerPage < nTotal )
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

void CItemBankPage::ResetAllItemSlotRender ( int index,int nTotal )
{
	if ( nTotal < 0 ) return ;

	for ( int i = index; i < nTotal; i++ )
	{
		CItemSlot* pItemSlot = m_pItemSlotArray[i];
		if ( pItemSlot )
		{
			pItemSlot->SetVisibleSingle ( FALSE );
		}
	}
}

void CItemBankPage::SetItemSlotRender ( int nStartIndex, int nTotal )
{
	if ( nTotal < 0 ) return ;

	const UIRECT& rcParentPos = GetGlobalPos ();

	for ( int i = nStartIndex; i < nTotal; i++ )
	{
		CItemSlot* pItemSlot = m_pItemSlotArray[i];
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

CItemSlot* CItemBankPage::CreateItemSlot ( CString strKeyword, UIGUID ControlID )
{
	CItemSlot* pItemSlot = new CItemSlot;
	pItemSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pItemSlot->CreateSubControl ( ITEMBANK_INVEN_X, TRUE );
	RegisterControl ( pItemSlot );

	return pItemSlot;
}

void CItemBankPage::LoadItem ( SINVENITEM& ref_InvenItem )
{	
	int nPosX = ref_InvenItem.wPosX;
	int nPosY = ref_InvenItem.wPosY;
	m_pItemSlotArray[nPosY]->SetItemImage ( nPosX, ref_InvenItem );
}

void CItemBankPage::LoadItemPage ( GLInventory &ItemData )
{
	GLInventory::CELL_MAP *pItemList = ItemData.GetItemList();
	
	if ( pItemList->size () > (ITEMBANK_INVEN_Y * ITEMBANK_INVEN_X) )
	{
		GASSERT ( 0 && "인터페이스 사이즈보다, 데이타크기가 큽니다." );
		return ;
	}

	//{	//	삭제

	//	GLInventory::CELL_MAP_ITER iter = pItemList->begin();
	//	GLInventory::CELL_MAP_ITER iter_end = pItemList->end();

	//	for ( WORD y = 0; y < ITEMBANK_INVEN_Y; y++ )
	//	{
	//		for ( WORD x = 0; x < ITEMBANK_INVEN_X; x++ )
	//		{
	//			SINVENITEM& ref_InvenItem = GetItem ( x, y );
	//			if ( ref_InvenItem.sItemCustom.sNativeID != NATIVEID_NULL() )
	//			{
	//				GLInventory::CELL_KEY foundkey ( x, y );
	//				GLInventory::CELL_MAP_ITER found = pItemList->find ( foundkey );
	//				if ( found == iter_end )
	//				{
	//					UnLoadItem ( x, y );
	//				}
	//			}
	//		}
	//	}
	//}

	//	등록
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

void CItemBankPage::UnLoadItemPage ()
{
	for ( int y = 0; y < ITEMBANK_INVEN_Y; y++ )
	{
		for ( int x = 0; x < ITEMBANK_INVEN_X; x++ )
		{
			UnLoadItem ( x, y );
		}
	}
}

SINVENITEM& CItemBankPage::GetItem ( int nPosX, int nPosY )
{
	return m_pItemSlotArray[nPosY]->GetItemImage ( nPosX );
}

void CItemBankPage::UnLoadItem ( int nPosX, int nPosY )
{
	m_pItemSlotArray[nPosY]->ResetItemImage ( nPosX );
}

void CItemBankPage::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( ITEM_SLOT0 <= ControlID && ControlID < ITEM_SLOT_END )
	{
		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{
			const int nPosY = ControlID - ITEM_SLOT0;
			CItemSlot* pSlot = m_pItemSlotArray[nPosY];
			const int nPosX = pSlot->GetItemIndex ();

			if ( nPosY < 0 || nPosX < 0 ) return ;

			SetItemIndex ( nPosX, nPosY );
		}
	}
	switch ( ControlID )
	{
	case ITEMBANK_BUTTON0:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				ITEMBANK1();
			}
		}
		break;
	case ITEMBANK_BUTTON1:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				ITEMBANK2();
			}
		}
		break;
	case ITEMBANK_BUTTON2:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				ITEMBANK3();
			}
		}
		break;
	case ITEMBANK_BUTTON3:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				ITEMBANK4();
			}
		}
		break;
	}
}
void CItemBankPage::ITEMBANK1()
{
	for ( int i = 0; i < 4; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[0]->SetVisibleSingle ( TRUE );
	m_Button[0]->SetVisibleSingle ( FALSE );
	ResetAllItemSlotRender ( 10,40 );
	SetItemSlotRender ( 0, 10 );
}
void CItemBankPage::ITEMBANK2()
{
	for ( int i = 0; i < 4; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[1]->SetVisibleSingle ( TRUE );
	m_Button[1]->SetVisibleSingle ( FALSE );
	ResetAllItemSlotRender ( 0,10 );
	ResetAllItemSlotRender ( 20,40 );
	SetItemSlotRender ( 10, 20 );
}
void CItemBankPage::ITEMBANK3()
{
	for ( int i = 0; i < 4; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[2]->SetVisibleSingle ( TRUE );
	m_Button[2]->SetVisibleSingle ( FALSE );
	ResetAllItemSlotRender ( 0,20 );
	ResetAllItemSlotRender ( 30,40 );
	SetItemSlotRender ( 20, 30 );
}
void CItemBankPage::ITEMBANK4()
{
	for ( int i = 0; i < 4; i++ )
	{
		m_Button[i]->SetVisibleSingle ( TRUE );
		m_ButtonSet[i]->SetVisibleSingle ( FALSE );
	}
	m_ButtonSet[3]->SetVisibleSingle ( TRUE );
	m_Button[3]->SetVisibleSingle ( FALSE );

	ResetAllItemSlotRender ( 0,30 );
	SetItemSlotRender ( 30, 40 );
}
void CItemBankPage::SetItemIndex ( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void CItemBankPage::GetItemIndex ( int* pnPosX, int* pnPosY )
{
	*pnPosX = m_nPosX;
	*pnPosY = m_nPosY;
}