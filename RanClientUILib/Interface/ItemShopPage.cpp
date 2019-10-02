#include "StdAfx.h"

#include "ItemShopPage.h"
#include "ItemSlot.h"
#include "InnerInterface.h"
#include "BasicScrollBarEx.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicTextBoxEx.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "../EngineLib/DxCommon/d3dfont.h"
#include "./GLCharData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CItemShopPage::nSTARTLINE = 0;
const int CItemShopPage::nOUTOFRANGE = -1;

CItemShopPage::CItemShopPage ()
	: m_pScrollBar ( NULL )
	, m_nCurPos ( -1 )
	
{
	memset( m_pItemSlotArrayDummy, 0, sizeof( m_pItemSlotArrayDummy ) );
}

CItemShopPage::~CItemShopPage ()
{
}

CUIControl*	CItemShopPage::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl , UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	RegisterControl ( pControl );
	return pControl;
}

void CItemShopPage::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	static CString strSlotKeyword[nMAX_ONE_VIEW_SLOT] =
	{
		"ITEMSHOP_ITEM_SLOT0",
		"ITEMSHOP_ITEM_SLOT1",
		"ITEMSHOP_ITEM_SLOT2",
		"ITEMSHOP_ITEM_SLOT3",
		"ITEMSHOP_ITEM_SLOT4",
		"ITEMSHOP_ITEM_SLOT5",
		"ITEMSHOP_ITEM_SLOT6",
		"ITEMSHOP_ITEM_SLOT7",
		"ITEMSHOP_ITEM_SLOT8",
		"ITEMSHOP_ITEM_SLOT9"
	};
	//	더미 슬롯
	for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ )
	{
		m_pItemSlotArrayDummy[i] = CreateControl ( strSlotKeyword[i].GetString () );
	}

	//	실제 데이타
	for ( int i = 0; i < ITEMSHOP_INVEN_Y; i++ )
	{
		m_pItemSlotArray[i] = CreateItemSlot ( strSlotKeyword[0], ITEM_SLOT0 + i  );

	}
	
	//	스크롤바
	CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
	pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
	pScrollBar->CreateBaseScrollBar ( "ITEMSHOP_PAGE_SCROLL" );
	pScrollBar->GetThumbFrame()->SetState ( ITEMSHOP_INVEN_Y, nMAX_ONE_VIEW_SLOT );
	RegisterControl ( pScrollBar );
	m_pScrollBar = pScrollBar;	

	SetItemSlotRender ( nSTARTLINE, nMAX_ONE_VIEW_SLOT );
}

CBasicTextBox* CItemShopPage::CreateStaticControl ( const char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}
void CItemShopPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE, nOUTOFRANGE );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_pScrollBar )
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
	}
}

void CItemShopPage::ResetAllItemSlotRender ( int nTotal )
{
	if ( nTotal < 0 ) return ;

	for ( int i = 0; i < nTotal; i++ )
	{
		CItemSlot* pItemSlot = m_pItemSlotArray[i];
		if ( pItemSlot )
		{
			pItemSlot->SetVisibleSingle ( FALSE );
		}
		
	}
}

void CItemShopPage::SetItemSlotRender ( int nStartIndex, int nTotal )
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

CItemSlot* CItemShopPage::CreateItemSlot ( CString strKeyword, UIGUID ControlID )
{
	CItemSlot* pItemSlot = new CItemSlot;
	pItemSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pItemSlot->CreateSubControl ( ITEMSHOP_INVEN_X, TRUE , TRUE );
	RegisterControl ( pItemSlot );

	return pItemSlot;
}

void CItemShopPage::LoadItem ( SINVENITEM& ref_InvenItem  )
{	
	
	int nPosX = ref_InvenItem.wPosX;
	int nPosY = ref_InvenItem.wPosY;
		
	m_pItemSlotArray[nPosY]->SetItemImage ( nPosX, ref_InvenItem );
}

void CItemShopPage::LoadItemPage ( WORD wType , WORD wCur )
{
	GLInventory::CELL_MAP *pItemList;
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	if ( pCharacter )
	{
		if ( wCur == 1 )
		{
			pItemList = pCharacter->m_cInvenItemShopVote[wType].GetItemList();
		}else if ( wCur == 2 )
		{
			pItemList = pCharacter->m_cInvenItemShopPremium[wType].GetItemList();
		}else pItemList = pCharacter->m_cInvenItemShop[wType].GetItemList();
	}else return;

	if ( pItemList->size () > (ITEMSHOP_INVEN_Y * ITEMSHOP_INVEN_X) )
	{
		GASSERT ( 0 && "인터페이스 사이즈보다, 데이타크기가 큽니다." );
		return ;
	}

	//{	//	삭제

	//	GLInventory::CELL_MAP_ITER iter = pItemList->begin();
	//	GLInventory::CELL_MAP_ITER iter_end = pItemList->end();

	//	for ( WORD y = 0; y < ITEMShop_INVEN_Y; y++ )
	//	{
	//		for ( WORD x = 0; x < ITEMShop_INVEN_X; x++ )
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

void CItemShopPage::UnLoadItemPage ()
{
	for ( int y = 0; y < ITEMSHOP_INVEN_Y; y++ )
	{
		for ( int x = 0; x < ITEMSHOP_INVEN_X; x++ )
		{
			UnLoadItem ( x, y );
		}
	}
}

SINVENITEM& CItemShopPage::GetItem ( int nPosX, int nPosY )
{
	return m_pItemSlotArray[nPosY]->GetItemImage ( nPosX );
}

void CItemShopPage::UnLoadItem ( int nPosX, int nPosY )
{
	m_pItemSlotArray[nPosY]->ResetItemImage ( nPosX );
}

void CItemShopPage::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
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
}

void CItemShopPage::SetItemIndex ( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void CItemShopPage::GetItemIndex ( int* pnPosX, int* pnPosY )
{
	*pnPosX = m_nPosX;
	*pnPosY = m_nPosY;
}