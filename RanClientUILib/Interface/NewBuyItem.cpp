#include "StdAfx.h"
#include "NewBuyItem.h"
#include "ItemSlot.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "GLItemMan.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CNewBuyItem::nSTARTLINE = 0;
const int CNewBuyItem::nOUTOFRANGE = -1;

CNewBuyItem::CNewBuyItem () 
	: m_nCurPos ( -1 )
	, m_PosXNew ( 0 )
	, m_PosYNew ( 0 )
	, m_nPosX ( 0 )
	, m_nPosY ( 0 )
{
	memset ( m_pItemSlotArray, 0, sizeof ( CItemSlot* ) * NEW_SALE_INVEN_Y );
	memset ( m_pItemSlotArrayDummy, 0, sizeof ( CUIControl* ) * nMAX_ONE_VIEW_SLOT_NEW );
}

CNewBuyItem::~CNewBuyItem ()
{
}

CUIControl*	CNewBuyItem::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

void CNewBuyItem::CreateSubControl ()
{
	CString strSlotKeyword[nMAX_ONE_VIEW_SLOT_NEW] =
	{
		"NEW_BUY_ITEM_SLOT0",
	};

	{	//	더미 슬롯
		for ( int i = 0; i < nMAX_ONE_VIEW_SLOT_NEW; i++ )
		{
			m_pItemSlotArrayDummy[i] = CreateControl ( strSlotKeyword[i].GetString () );
		}
	}

	const int nExampleCount = 1;
	{	//	실제 데이타
		for ( int i = 0; i < nExampleCount; i++ )
		{
			m_pItemSlotArray[i] = CreateItemSlot ( strSlotKeyword[0], ITEM_SLOT0 + i );
		}
	}

	SetItemSlotRender ( 0, nMAX_ONE_VIEW_SLOT_NEW );
}

void CNewBuyItem::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE, nOUTOFRANGE );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	SetItemSlotRender ( 0, 1 );
}

void CNewBuyItem::ResetAllItemSlotRender ( int nTotal )
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

void CNewBuyItem::SetItemSlotRender ( int nStartIndex, int nTotal )
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

CItemSlot* CNewBuyItem::CreateItemSlot ( CString strKeyword, UIGUID ControlID )
{
	CItemSlot* pItemSlot = new CItemSlot;
	pItemSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pItemSlot->CreateSubControl ( NEW_SALE_INVEN_X );
	RegisterControl ( pItemSlot );
	return pItemSlot;
}

void CNewBuyItem::SetItemIndex ( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void CNewBuyItem::GetItemIndex ( int* pnPosX, int* pnPosY )
{
	*pnPosX = m_nPosX;
	*pnPosY = m_nPosY;
}

void CNewBuyItem::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( ITEM_SLOT0 <= ControlID && ControlID < ITEM_SLOT_END )
	{
		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{
			const int nPosY = ControlID - ITEM_SLOT0;
			CItemSlot* pSlot = m_pItemSlotArray[nPosY];
			const int nPosX = pSlot->GetItemIndex ();

			SetItemIndex ( nPosX, nPosY );
		}
	}
}

void CNewBuyItem::LoadItem ( SINVENITEM& ref_InvenItem )
{
	if ( m_PosYNew > 0 || m_PosXNew > 9 )
		return;
	int nPosX = m_PosXNew;
	int nPosY = m_PosYNew;
	m_pItemSlotArray[nPosY]->SetItemImage ( nPosX, ref_InvenItem );
	m_PosXNew++;
}

void CNewBuyItem::LoadItemPage ( GLInventory &ItemData )
{
//	SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM();

	GLInventory::CELL_MAP *ItemList = ItemData.GetItemList();

	if ( ItemList->size () > ( NEW_SALE_INVEN_Y * NEW_SALE_INVEN_X) )
	{
		GASSERT ( 0 && "인터페이스 사이즈보다, 데이타크기가 큽니다." );
		return ;
	}

	GLInventory::CELL_MAP_ITER iter = ItemList->begin();
	GLInventory::CELL_MAP_ITER iter_end = ItemList->end();

//	int nPosX, nPosY;
	for ( ; iter!=iter_end; ++iter )
	{
		SINVENITEM* pInvenItem = (*iter).second;
		SITEMCUSTOM &ref_ItemCustom = pInvenItem->sItemCustom;
		SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_ItemCustom.sNativeID );
		if ( !pItemData )	continue;
		
//		nPosX = (*iter).second->wPosX;
//		nPosY = (*iter).second->wPosY;

		LoadItem ( *pInvenItem );
	}
}


void CNewBuyItem::UnLoadItemPage ()
{
	for ( int y = 0; y < NEW_SALE_INVEN_Y; y++ )
	{
		for ( int x = 0; x < NEW_SALE_INVEN_X; x++ )
		{
			UnLoadItem ( x, y );
		}
	}
	m_PosXNew = 0;
	m_PosYNew = 0;
}

SINVENITEM& CNewBuyItem::GetItem ( int nPosX, int nPosY )
{
	return m_pItemSlotArray[nPosY]->GetItemImage ( nPosX );
}

void CNewBuyItem::UnLoadItem ( int nPosX, int nPosY )
{
	m_pItemSlotArray[nPosY]->ResetItemImage ( nPosX );
	m_PosXNew--;
}
void CNewBuyItem::LoadItemNew( int x , int y , SINVENITEM& ref_InvenItem)
{
	m_pItemSlotArray[y]->SetItemImage ( x, ref_InvenItem );
}