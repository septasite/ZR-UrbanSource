#include "StdAfx.h"
#include "InterestItem.h"
#include "ItemSlot.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "GLItemMan.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CInterestItem::nSTARTLINE = 0;
const int CInterestItem::nOUTOFRANGE = -1;

CInterestItem::CInterestItem () 
	: m_nCurPos ( -1 )
	, m_nPosX ( 0 )
	, m_nPosY ( 0 )
	, m_PosXNew ( 0 )
	, m_PosYNew ( 0 )
{
	memset ( m_pItemSlotArray, 0, sizeof ( CItemSlot* ) * INTEREST_INVEN_Y );
	memset ( m_pItemSlotArrayDummy, 0, sizeof ( CUIControl* ) * nMAX_ONE_VIEW_SLOT_NEW );
}

CInterestItem::~CInterestItem ()
{
}

CUIControl*	CInterestItem::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

void CInterestItem::CreateSubControl ()
{
	CString strSlotKeyword[nMAX_ONE_VIEW_SLOT_NEW] =
	{
		"INTEREST_ITEM_SLOT0",
		"INTEREST_ITEM_SLOT1",
		"INTEREST_ITEM_SLOT2",
		"INTEREST_ITEM_SLOT3",
		"INTEREST_ITEM_SLOT4"
	};

	{	//	더미 슬롯
		for ( int i = 0; i < nMAX_ONE_VIEW_SLOT_NEW; i++ )
		{
			m_pItemSlotArrayDummy[i] = CreateControl ( strSlotKeyword[i].GetString () );
		}
	}

	const int nExampleCount = 5;
	{	//	실제 데이타
		for ( int i = 0; i < nExampleCount; i++ )
		{
			m_pItemSlotArray[i] = CreateItemSlot ( strSlotKeyword[0], ITEM_SLOT0 + i );
		}
	}

	SetItemSlotRender ( 0, nMAX_ONE_VIEW_SLOT_NEW );
}

void CInterestItem::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	SetItemIndex ( nOUTOFRANGE, nOUTOFRANGE );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	SetItemSlotRender ( 0, nMAX_ONE_VIEW_SLOT_NEW );
}

void CInterestItem::ResetAllItemSlotRender ( int nTotal )
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

void CInterestItem::SetItemSlotRender ( int nStartIndex, int nTotal )
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

CItemSlot* CInterestItem::CreateItemSlot ( CString strKeyword, UIGUID ControlID )
{
	CItemSlot* pItemSlot = new CItemSlot;
	pItemSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pItemSlot->CreateSubControl ( INTEREST_INVEN_X );
	RegisterControl ( pItemSlot );
	return pItemSlot;
}

void CInterestItem::SetItemIndex ( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void CInterestItem::GetItemIndex ( int* pnPosX, int* pnPosY )
{
	*pnPosX = m_nPosX;
	*pnPosY = m_nPosY;
}

void CInterestItem::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
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

void CInterestItem::LoadItem (SINVENITEM& ref_InvenItem )
{
	if ( m_PosYNew > 4 )
		return;
	else
	{
		int nPosX = m_PosXNew;
		int nPosY = m_PosYNew;
		m_pItemSlotArray[nPosY]->SetItemImage ( nPosX, ref_InvenItem );
		m_PosYNew++;
	}
}
DWORD CInterestItem::GetPriceItem( int index )
{
	SINVENITEM Item = GetItem( 0 ,index );
	SITEM* pITEM = GLItemMan::GetInstance().GetItem ( Item.sItemCustom.sNativeID );
	float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetBuyRate();
	float fSHOP_RATE_C = fSHOP_RATE * 0.01f;
	m_pPriceItem[index] = 0;
	if ( pITEM )
		m_pPriceItem[index] = static_cast<DWORD>( pITEM->sBasicOp.dwBuyPrice * fSHOP_RATE_C );
	return m_pPriceItem[index];
}
CString CInterestItem::GetNameItem( int index )
{
	SINVENITEM Item = GetItem( 0 ,index );
	SITEM* pITEM = GLItemMan::GetInstance().GetItem ( Item.sItemCustom.sNativeID );
	m_pNameItem[index] = "";
	if( pITEM )
	{
		const std::string& strItemName = pITEM->GetName();
		m_pNameItem[index] = strItemName.c_str();
	}
	return m_pNameItem[index];
}
void CInterestItem::LoadInterestItem( GLInventory &ItemData )
{
	GLInventory::CELL_MAP *ItemList = ItemData.GetItemList();

	GLInventory::CELL_MAP_ITER iter = ItemList->begin();
	GLInventory::CELL_MAP_ITER iter_end = ItemList->end();

	for ( ; iter!=iter_end; ++iter )
	{
		SINVENITEM* pInvenItem = (*iter).second;
		SITEMCUSTOM &ref_ItemCustom = pInvenItem->sItemCustom;
		SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_ItemCustom.sNativeID );
		if ( !pItemData )	continue;
		LoadItem ( *pInvenItem );
	}
}
void CInterestItem::LoadItemPage ( GLInventory &ItemData )
{
//	SITEMCUSTOM sItemCustom = GLGaeaClient::GetInstance().GetCharacter()->GET_HOLD_ITEM();

	GLInventory::CELL_MAP *ItemList = ItemData.GetItemList();

	if ( ItemList->size () > ( INTEREST_INVEN_X * INTEREST_INVEN_Y ) )
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

		//LoadItem ( *pInvenItem );
	}
}

void CInterestItem::SetUnUse()
{
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	BOOL bAccept(FALSE);

	for ( int y = 0; y < INTEREST_INVEN_Y; y++ )
	{
		for ( int x = 0; x < INTEREST_INVEN_X; x++ )
		{
			SINVENITEM sItem = GetItem(x,y);

			if( sItem.sItemCustom.nidDISGUISE != NATIVEID_NULL() )
				bAccept = pCharacter->ACCEPT_ITEM( sItem.sItemCustom.sNativeID, sItem.sItemCustom.nidDISGUISE );
			else
				bAccept = pCharacter->ACCEPT_ITEM( sItem.sItemCustom.sNativeID );

			if ( !bAccept )
			{
				UnLoadItem ( x, y );
			}
		}
	}
}
void CInterestItem::SetUnBuy()
{
	LONGLONG dwNpcSellPrice = 0;
	volatile LONGLONG dwPrice = 0;
	volatile float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetBuyRate();
	volatile float fSHOP_RATE_C = fSHOP_RATE * 0.01f;

	for ( int y = 0; y < INTEREST_INVEN_Y; y++ )
	{
		for ( int x = 0; x < INTEREST_INVEN_X; x++ )
		{
			SINVENITEM sItem = GetItem(x,y);
			SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sItem.sItemCustom.sNativeID );
			if ( pItemData )
			{
				dwNpcSellPrice = pItemData->sBasicOp.dwBuyPrice;
				dwPrice = DWORD ( (float)dwNpcSellPrice * fSHOP_RATE_C );

				if( dwPrice > GLGaeaClient::GetInstance().GetCharacterLogic().m_lnMoney )
				{
					UnLoadItem ( x, y );
				}
			}
		}
	}
}
void CInterestItem::UnLoadItemPage ()
{
	for ( int y = 0; y < INTEREST_INVEN_Y; y++ )
	{
		for ( int x = 0; x < INTEREST_INVEN_X; x++ )
		{
			UnLoadItem ( x, y );
		}
	}
	m_PosXNew = 0;
	m_PosYNew = 0;
}

SINVENITEM& CInterestItem::GetItem ( int nPosX, int nPosY )
{
	return m_pItemSlotArray[nPosY]->GetItemImage ( nPosX );
}

void CInterestItem::UnLoadItem ( int nPosX, int nPosY )
{
	m_pItemSlotArray[nPosY]->ResetItemImage ( nPosX );
	m_PosYNew--;
}