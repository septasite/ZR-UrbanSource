#include "StdAfx.h"
#include "CompoundWindowMenu.h"
#include "CompoundWindowMenuButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCompoundWindowMenu::CCompoundWindowMenu ()
	: m_wType( 0 )
{
	for(int i=0; i < 13; i++ )
		m_pMenuButton[i] = NULL;
}

CCompoundWindowMenu::~CCompoundWindowMenu ()
{
}

CCompoundWindowMenuButton* CCompoundWindowMenu::CreateMenu ( CString strKeyword, UIGUID ControlID, CString strOn, CString strOff )
{
	CCompoundWindowMenuButton* pSlot = new CCompoundWindowMenuButton;
	pSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pSlot->CreateSubControl( strOff, strOn );
	pSlot->SetVisibleSingle(TRUE);
	RegisterControl ( pSlot );

	return pSlot;
}

void CCompoundWindowMenu::CreateSubControl()
{
	for(int i=0; i < 13; i++ )
	{
		CString strKeyword, strKeyOff, strKeyOn;
		strKeyword.Format( "ITEM_COMPOUND_WINDOW_MENU_BUTTON0%d", i );
		strKeyOff.Format( "ITEM_COMPOUND_WINDOW_MENU_BUTTON_OFF0%d", i );
		strKeyOn.Format( "ITEM_COMPOUND_WINDOW_MENU_BUTTON_ON0%d", i );

		m_pMenuButton[i] = CreateMenu ( strKeyword, MENU_00 + i, strKeyOn, strKeyOff );
	}

	SetType(0);
	m_pMenuButton[0]->SetOn();
}

void CCompoundWindowMenu::TranslateUIMessage( UIGUID ControlID, DWORD dwMsg )
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
			if ( CHECK_MOUSEIN_LBUPLIKE( dwMsg ))
			{
				int nIndex = ControlID - MENU_00;
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