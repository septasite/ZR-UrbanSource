#include "StdAfx.h"
#include "LargeMapWindow.h"
#include "LargeMapWindowMob.h"
#include "LargeMapWindowImage.h"
#include "LargeMapWindowRadio.h"
#include "LargeMapWindowSetting.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/InnerInterface.h"
#include "../RanClientUILib/Interface/BasicLineBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CLargeMapWindow::CLargeMapWindow ():
	 m_pBackGround(NULL)
	,m_pImage(NULL)
	,m_pSetting(NULL)
	,m_pInfo(NULL)
{
	SecureZeroMemory(m_pRadio, sizeof(m_pRadio));
}

CLargeMapWindow::~CLargeMapWindow ()
{
}

void CLargeMapWindow::CreateSubControl()
{
	m_pBackGround = new CUIControl;
	m_pBackGround->CreateSub ( this, "MAP_WINDOW_MAIN_REGION" );	
	m_pBackGround->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pBackGround );

	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "MAP_WINDOW_TAP_REGION" );
	RegisterControl ( pBasicLineBox );

	m_pImage = new CLargeMapWindowImage;
	m_pImage->CreateSub( this, "MAP_WINDOW_IMAGE" );
	m_pImage->CreateSubControl();
	RegisterControl( m_pImage );

	{
		CString strKeyword[MAX_RADIO_SETTINGS] =
		{
			"MAP_WINDOW_MAIN_SETTING_RADIO_BUTTON",
			"MAP_WINDOW_MAIN_INFO_RADIO_BUTTON",
			"MAP_WINDOW_MAIN_PARTY_RADIO_BUTTON",
			"MAP_WINDOW_MAIN_SEARCH_RADIO_BUTTON"
		};

		for(int i = 0; i < MAX_RADIO_SETTINGS; i++ )
		{
			m_pRadio[i] = new CLargeMapWindowRadio;
			m_pRadio[i]->CreateSub(this, strKeyword[i].GetString(), UI_FLAG_DEFAULT, MAP_WINDOW_MAIN_SETTING_RADIO_BUTTON + i );
			m_pRadio[i]->CreateSubControl();
			m_pRadio[i]->SetRadioText( ID2GAMEWORD("LARGEMAP_WINDOW_RADIO_TEXT",i));
			RegisterControl( m_pRadio[i] );
		}
	}

	m_pSetting = new CLargeMapWindowSetting;
	m_pSetting->CreateSub(this, "MAP_WINDOW_TAP_SETTINGS", UI_FLAG_DEFAULT, MAP_WINDOW_TAP_SETTINGS );
	m_pSetting->CreateSubControl();
	RegisterControl( m_pSetting );
	
	m_pInfo = new CLargeMapWindowMob;
	m_pInfo->CreateSub(this, "MAP_WINDOW_TAP_INFO", UI_FLAG_DEFAULT, MAP_WINDOW_TAP_INFO );
	m_pInfo->CreateSubControl();
	RegisterControl( m_pInfo );

	SetPage(0);
	
	for(int i = 0; i < MAX_SUB_SETTING; i++) m_bSUBSETTING[i] = TRUE;
	m_bSUBMOTION = TRUE;
	for(int j = 0; j < MAXCROW; j++ ) m_bMOB[j] = TRUE;
}

void CLargeMapWindow::SetPage(int nIndex)
{
	for(int i = 0; i < MAX_RADIO_SETTINGS; i++ ) m_pRadio[i]->SetRadioOn(FALSE);
	m_pRadio[nIndex]->SetRadioOn(TRUE);
	m_pSetting->SetVisibleSingle(FALSE);
	m_pInfo->SetVisibleSingle(FALSE);
	switch(nIndex)
	{
	case 0:	m_pSetting->SetVisibleSingle(TRUE);		break;
	case 1:	m_pInfo->SetVisibleSingle(TRUE);		break;
	}
}

void CLargeMapWindow::TranslateUIMessage ( UIGUID cID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( cID, dwMsg );

	switch ( cID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) ) CInnerInterface::GetInstance().SetDefaultPosInterface( LARGEMAP_WINDOW );
		}
		break;
	case MAP_WINDOW_MAIN_SETTING_RADIO_BUTTON:
	case MAP_WINDOW_MAIN_INFO_RADIO_BUTTON:
	case MAP_WINDOW_MAIN_PARTY_RADIO_BUTTON:
	case MAP_WINDOW_MAIN_SEARCH_RADIO_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			{
				int nIndex = cID - MAP_WINDOW_MAIN_SETTING_RADIO_BUTTON;
				SetPage(nIndex);
			}
		}
		break;
	}
}

void CLargeMapWindow::SetMapAxisInfo ( GLMapAxisInfo& sInfo,CString strMapName )
{
	if ( m_pImage ) m_pImage->SetMapAxisInfo( sInfo, strMapName );
}

void CLargeMapWindow::VISIBLE_TARGET_POS( BOOL bVisible )
{
	if ( m_pImage ) m_pImage->VISIBLE_TARGET_POS( bVisible );
}

void CLargeMapWindow::ClearMobList()
{
	m_pImage->ClearMobList();
	m_pInfo->ClearMobList();
	m_nIndex = 0;
	for(int i = 0; i < MAXCROW; i++ ) m_sNativeID[i] = NATIVEID_NULL();
}

void CLargeMapWindow::LoadMob(NET_MSG_GENERIC* nmg, GLCHARLOGIC *pCHAR )
{
	GLMSG::SNETPC_REQ_CROWLIST_FB* pNetMsg = (GLMSG::SNETPC_REQ_CROWLIST_FB*)nmg;
	if ( pNetMsg->bRender )
	{
		if ( m_pImage ) m_pImage->LoadMob(nmg, pCHAR);
	} 
	else 
	{
		if ( m_pInfo ) m_pInfo->LoadMob(nmg);
		m_sNativeID[m_nIndex] = pNetMsg->sCrowID;
		m_nIndex++;
	}	
}