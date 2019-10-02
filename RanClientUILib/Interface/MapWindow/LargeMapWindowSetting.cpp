#include "StdAfx.h"
#include "LargeMapWindow.h"
#include "LargeMapWindowSetting.h"
#include "LargeMapWindowCheckBox.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"
#include "../RanClientUILib/Interface/InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLargeMapWindowSetting::CLargeMapWindowSetting ():
	m_pSetting(NULL)
{
	SecureZeroMemory(m_pSubSetting, sizeof(m_pSubSetting));
}

CLargeMapWindowSetting::~CLargeMapWindowSetting ()
{
}

void CLargeMapWindowSetting::CreateSubControl()
{
	CString strKeywordSubSetting[MAX_SUB_SETTING] = 
	{
		"MAP_WINDOW_SETTING_TAP_GATE_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_NORMAL_NPC_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_PLACE_NAME_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_BUS_STATION_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_LOCKER_MANAGER_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_START_POSITION_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_CLUB_MANAGER_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_POSTBOX_CHECKBOX",
		"MAP_WINDOW_SETTING_TAP_PARTY_PLAYER_CHECKBOX"
	};
	
	for( int i = 0; i < MAX_SUB_SETTING; i++ )
	{
		m_pSubSetting[i] = CreateCheckBox( strKeywordSubSetting[i].GetString(), LARGEMAP_WINDOW_SETTING0 + i, ID2GAMEWORD("LARGEMAP_WINDOW_SUB_SETTING_STATIC_TEXT", i ));
		CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBSETTING[i] = m_pSubSetting[i]->IsChecked();
	}
	
	m_pSetting = CreateCheckBox( "MAP_WINDOW_SETTING_TAP_SIGN_CHECKBOX", LARGEMAP_WINDOW_SETTING, ID2GAMEWORD("LARGEMAP_WINDOW_SETTING_STATIC_TEXT",0));

	m_pMotion = CreateCheckBox( "MAP_WINDOW_SETTING_TAP_ACTION_SETTING_TEXT", MAP_WINDOW_SETTING_TAP_ACTION_SETTING_TEXT, ID2GAMEWORD("LARGEMAP_WINDOW_SETTING_STATIC_TEXT",1));
	m_pSubMotion = CreateCheckBox( "MAP_WINDOW_SETTING_TAP_AUTO_RIDE_VEHICLE_TEXT", MAP_WINDOW_SETTING_TAP_AUTO_RIDE_VEHICLE_TEXT, ID2GAMEWORD("LARGEMAP_WINDOW_SUB_MOTION_STATIC_TEXT",0));

}

CLargeMapWindowCheckBox* CLargeMapWindowSetting::CreateCheckBox( const char* strKeyword, UIGUID cID, CString strText )
{
	CLargeMapWindowCheckBox* pCheck = new CLargeMapWindowCheckBox;
	pCheck->CreateSub(this, strKeyword, UI_FLAG_DEFAULT, cID );
	pCheck->CreateSubControl();
	pCheck->SetTextTitle( strText, NS_UITEXTCOLOR::WHITE );
	pCheck->ForceCheck();
	RegisterControl( pCheck );

	return pCheck;
}

void CLargeMapWindowSetting::TranslateUIMessage ( UIGUID cID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( cID, dwMsg );

	switch ( cID )
	{
	case LARGEMAP_WINDOW_SETTING:
		{
			if( CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			{
				m_pSetting->SetCheck();
				BOOL bCHECK = m_pSetting->IsChecked();
				
				for( int i = 0; i < MAX_SUB_SETTING; i++ ) 
				{
					if ( bCHECK ) m_pSubSetting[i]->ForceCheck();
					else m_pSubSetting[i]->ForceUnCheck();

					CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBSETTING[i] = bCHECK;
				}
			}
		}
		break;
	case MAP_WINDOW_SETTING_TAP_ACTION_SETTING_TEXT:
		{
			if( CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			{
				m_pMotion->SetCheck();
				BOOL bCHECK = m_pMotion->IsChecked();
				
				if ( bCHECK ) m_pSubMotion->ForceCheck();
				else m_pSubMotion->ForceUnCheck();

				CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBMOTION = bCHECK;
			}
		}
		break;
	case LARGEMAP_WINDOW_SETTING0:
	case LARGEMAP_WINDOW_SETTING1:
	case LARGEMAP_WINDOW_SETTING2:
	case LARGEMAP_WINDOW_SETTING3:
	case LARGEMAP_WINDOW_SETTING4:
	case LARGEMAP_WINDOW_SETTING5:
	case LARGEMAP_WINDOW_SETTING6:
	case LARGEMAP_WINDOW_SETTING7:
	case LARGEMAP_WINDOW_SETTING8:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			{
				int nIndex = cID - LARGEMAP_WINDOW_SETTING0;
				m_pSubSetting[nIndex]->SetCheck();
				CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBSETTING[nIndex] = m_pSubSetting[nIndex]->IsChecked();
			}
		}
		break;
	case MAP_WINDOW_SETTING_TAP_AUTO_RIDE_VEHICLE_TEXT:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			{
				m_pSubMotion->SetCheck();
				CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBMOTION = m_pSubMotion->IsChecked();
			}
		}
		break;
	}
}