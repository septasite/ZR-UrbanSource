#include "StdAfx.h"
#include "ItemShopWindowMenu.h"
#include "ItemShopWindowMenuButton.h"
#include "InnerInterface.h"
#include "UITextControl.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemShopWindowMenu::CItemShopWindowMenu ()
	: m_wType( 0 )
{
	for(int i=0; i < 13; i++ )
		m_pMenuButton[i] = NULL;
}

CItemShopWindowMenu::~CItemShopWindowMenu ()
{
}

CItemShopWindowMenuButton* CItemShopWindowMenu::CreateMenu ( CString strKeyword, UIGUID ControlID, CString strOn, CString strOff )
{
	CItemShopWindowMenuButton* pSlot = new CItemShopWindowMenuButton;
	pSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pSlot->CreateSubControl( strOff, strOn );
	pSlot->SetVisibleSingle(TRUE);
	RegisterControl ( pSlot );

	return pSlot;
}

void CItemShopWindowMenu::CreateSubControl()
{
	for(int i=0; i < 13; i++ )
	{
		CString strKeyword, strKeyOff, strKeyOn;
		strKeyword.Format( "ITEMSHOP_WINDOW_MENU_BUTTON0%d", i );
		strKeyOff.Format( "ITEMSHOP_WINDOW_MENU_BUTTON_OFF0%d", i );
		strKeyOn.Format( "ITEMSHOP_WINDOW_MENU_BUTTON_ON0%d", i );

		m_pMenuButton[i] = CreateMenu ( strKeyword, MENU_00 + i, strKeyOn, strKeyOff );
	}

	SetType(0);
	m_pMenuButton[0]->SetOn();
}
void CItemShopWindowMenu::SetButtonOn ( WORD wType )
{
	for(int i=0; i < 13; i++ )
	{
		m_pMenuButton[i]->SetOff();
	}
	m_pMenuButton[wType]->SetOn();
}
void CItemShopWindowMenu::TranslateUIMessage( UIGUID ControlID, DWORD dwMsg )
{
	switch( ControlID )
	{
	case MENU_00:
	case MENU_01:
	case MENU_02:
	case MENU_03:
	case MENU_04:
	case MENU_05:
	case MENU_06:
	case MENU_07:
	case MENU_08:
	case MENU_09:
	case MENU_10:
	case MENU_11:
	case MENU_12:
		{
			int nIndex = ControlID - MENU_00;
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEWORD("ITEMSHOP_MENU_BUTTON", nIndex ), NS_UITEXTCOLOR::DEFAULT  );
			}
			if ( CHECK_MOUSEIN_LBUPLIKE( dwMsg ))
			{
				for(int i = 0; i < 13; i++ )
				{
					if ( i == nIndex ) 
						continue;

					m_pMenuButton[i]->SetOff();
				}
				SetType( nIndex );
				
			}
		}
		break;
	}
}