#include "StdAfx.h"
#include "InventoryWindow.h"
#include "InventoryPageWearView.h"
#include "InventoryViewCharItemWindow.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "MarketWindow.h"
#include "d3dfont.h"
#include "DxGlobalStage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CInventoryViewCharItemWindow::CInventoryViewCharItemWindow ()
{
}

CInventoryViewCharItemWindow::~CInventoryViewCharItemWindow ()
{
}

void CInventoryViewCharItemWindow::CreateSubControl ()
{
	const EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );
	{
		m_pPageWearEx = new CInventoryPageWearView;
		m_pPageWearEx->CreateSub ( this, "INVENTORY_PAGE_WEAR_VIEW", UI_FLAG_DEFAULT, INVENTORY_PAGEWEAR_VIEW );
		m_pPageWearEx->CreateSubControl ( nClassType );
		RegisterControl ( m_pPageWearEx );
	}
}

void CInventoryViewCharItemWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CInventoryViewCharItemWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( INVENTORY_VIEW_WINDOW );
			}
		}
		break;

	case INVENTORY_PAGEWEAR_VIEW:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pPageWearEx->GetItemIndex ();
				if ( nIndex < 0 ) return ;

				{
					SITEMCUSTOM sItemCustom = m_pPageWearEx->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}
				}

			}
		}
		break;
	case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( INVENTORY_VIEW_WINDOW );
				//m_pPageWearEx->ReSetAllItemEx();
			}
		}
		break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}

void CInventoryViewCharItemWindow::SetItemInInventory(int m_nIndex, SITEMCUSTOM& sItemCustom)
{
	m_pPageWearEx->SetItemInInventoryEx(m_nIndex, sItemCustom);
}
