#include "StdAfx.h"
#include "PartySlot.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "BasicLineBox.h"
#include "GLCharDefine.h"
#include "InnerInterface.h"
#include "FriendWindow.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "d3dfont.h"

#include "../EngineLib/DxCommon/DxFontMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartySlot::CPartySlot ()
	: m_pTextNum( NULL )
	, m_pDie( NULL )
	, m_pLevelText( NULL )
	, m_pMapText( NULL )
	, m_pNameText( NULL )
	, m_pPosText( NULL ) 
	, m_pAddFriendBtn( NULL )
{
	SecureZeroMemory(m_pClassLive, sizeof(m_pClassLive));
	SecureZeroMemory(m_pClassDie, sizeof(m_pClassDie));
	SecureZeroMemory(m_pSchool, sizeof(m_pSchool));
}

CPartySlot::~CPartySlot ()
{
}

void CPartySlot::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "PARTY_INFO_SLOT_REGION" );
	RegisterControl ( pBasicLineBox );

	m_pTextNum = CreateStaticControl( "PARTY_INFO_SLOT_TEXT", pFont, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pMaster = CreateControl( "PARTY_INFO_SLOT_MASTER" );

	CString strClassLive[GLCI_NUM_NEWEST] =
	{
		"PARTY_INFO_BRAWLER_MALE_LIVE",
		"PARTY_INFO_SWORDSMAN_MALE_LIVE",
		"PARTY_INFO_ARCHER_FEMALE_LIVE",
		"PARTY_INFO_SHAMAN_FEMALE_LIVE",
		"PARTY_INFO_EXTREME_MALE_LIVE",
		"PARTY_INFO_EXTREME_FEMALE_LIVE",
		"PARTY_INFO_BRAWLER_FEMALE_LIVE",
		"PARTY_INFO_SWORDSMAN_FEMALE_LIVE",
		"PARTY_INFO_ARCHER_MALE_LIVE",
		"PARTY_INFO_SHAMAN_MALE_LIVE",
		"PARTY_INFO_SCIENTIST_MALE_LIVE",
		"PARTY_INFO_SCIENTIST_FEMALE_LIVE",
		"PARTY_INFO_ASSASSIN_MALE_LIVE",
		"PARTY_INFO_ASSASSIN_FEMALE_LIVE",
		"PARTY_INFO_TRICKER_MALE_LIVE",
		"PARTY_INFO_TRICKER_FEMALE_LIVE",
	};

	CString strClassDie[GLCI_NUM_NEWEST] =
	{
		"PARTY_INFO_BRAWLER_MALE_DIE",
		"PARTY_INFO_SWORDSMAN_MALE_DIE",
		"PARTY_INFO_ARCHER_FEMALE_DIE",
		"PARTY_INFO_SHAMAN_FEMALE_DIE",
		"PARTY_INFO_EXTREME_MALE_DIE",
		"PARTY_INFO_EXTREME_FEMALE_DIE",
		"PARTY_INFO_BRAWLER_FEMALE_DIE",
		"PARTY_INFO_SWORDSMAN_FEMALE_DIE",
		"PARTY_INFO_ARCHER_MALE_DIE",
		"PARTY_INFO_SHAMAN_MALE_DIE",
		"PARTY_INFO_SCIENTIST_MALE_DIE",
		"PARTY_INFO_SCIENTIST_FEMALE_DIE",
		"PARTY_INFO_ASSASSIN_MALE_DIE",
		"PARTY_INFO_ASSASSIN_FEMALE_DIE",
		"PARTY_INFO_TRICKER_MALE_DIE",
		"PARTY_INFO_TRICKER_FEMALE_DIE",
	};

	for( int i = 0; i < GLCI_NUM_NEWEST; i++ )
	{
		m_pClassLive[i] = CreateControl( strClassLive[i].GetString()); 
		m_pClassDie[i] = CreateControl( strClassDie[i].GetString()); 

		m_pClassLive[i]->SetVisibleSingle(FALSE);
		m_pClassDie[i]->SetVisibleSingle(FALSE);
	}

	m_pDie = CreateControl( "PARTY_INFO_DIE" );

	CString strKeywordSchool[3] = 
	{
		"PARTY_INFO_SM",
		"PARTY_INFO_HA",
		"PARTY_INFO_BH"
	};

	for( int i = 0; i < 3; i++ ) m_pSchool[i] = CreateControl( strKeywordSchool[i].GetString());

	m_pLevelText = CreateStaticControl( "PARTY_INFO_LEVEL_TEXT", pFont, TEXT_ALIGN_LEFT );
	m_pMapText = CreateStaticControl( "PARTY_INFO_MAP_TEXT", pFont, TEXT_ALIGN_LEFT );
	m_pNameText = CreateStaticControl( "PARTY_INFO_NAME_TEXT", pFont, TEXT_ALIGN_RIGHT );
	m_pPosText = CreateStaticControl( "PARTY_INFO_POS_TEXT", pFont, TEXT_ALIGN_RIGHT );

	m_pSelect = CreateControl( "PARTY_INFO_SELECT" );
	m_pSelect->SetVisibleSingle(FALSE);

	m_pAddFriendBtn = CreateFlipButton( "PARTY_INFO_ADD_BUTTON", "PARTY_INFO_ADD_BUTTON_F", "PARTY_INFO_ADD_BUTTON_OVER", PARTY_INFO_ADD_BUTTON );
	CreateFlipButton( "PARTY_INFO_VIEW_BUTTON", "PARTY_INFO_VIEW_BUTTON_F", "PARTY_INFO_VIEW_BUTTON_OVER", PARTY_INFO_VIEW_BUTTON );

	m_bSelect = FALSE;
}

CBasicButton* CPartySlot::CreateFlipButton ( char* szButton, char* szButtonFlip, char* szButtonOver, UIGUID ControlID )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, CBasicButton::CLICK_FLIP );
	pButton->CreateMouseOver ( szButtonOver );
	RegisterControl ( pButton );
	return pButton;
}

CUIControl*	CPartySlot::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CPartySlot::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	pStaticText->SetVisibleSingle(TRUE);
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CPartySlot::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage(ControlID, dwMsg);

	switch(ControlID)
	{
	case PARTY_INFO_ADD_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE(dwMsg)) CInnerInterface::GetInstance().GetFriendWindow()->ADD_FRIEND(GetName());
		}
		break;
	case PARTY_INFO_VIEW_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE(dwMsg)) CInnerInterface::GetInstance().PrintConsoleText("Not yet available.");
		}
		break;
	}
}

int CPartySlot::SetSlotNum(CString strNum)
{
	m_pTextNum->ClearText();

	if ( m_pTextNum ) return m_pTextNum->AddTextNoSplit( strNum, NS_UITEXTCOLOR::WHITE );
	return -1;
}

void CPartySlot::SetMaster(BOOL bMaster)
{
	m_bMaster = bMaster;
	if ( m_pMaster ) m_pMaster->SetVisibleSingle(m_bMaster);
}

void CPartySlot::SetClass(int nClass)
{
	if ( nClass < GLCI_FIGHTER_M && nClass > GLCI_TESTING_W ) return;

	for(int i = 0; i < GLCI_NUM_NEWEST; i++ )
	{
		m_pClassLive[i]->SetVisibleSingle(FALSE);
		m_pClassDie[i]->SetVisibleSingle(FALSE);
	}

	m_pClassLive[nClass]->SetVisibleSingle(IsSameMap()&&!IsDie());
	m_pClassDie[nClass]->SetVisibleSingle(!IsSameMap()||IsSameMap()&&IsDie());
}

void CPartySlot::SetDie(BOOL bDIE)
{
	m_bDIE = bDIE;

	BOOL bBOTH = (IsSameMap() && IsDie()) ? TRUE : FALSE;
	if ( m_pDie ) m_pDie->SetVisibleSingle(bBOTH);
}

void CPartySlot::SetSchool(int nSchool)
{
	if ( nSchool < 0 || nSchool > 3 ) return;
	for(int i = 0; i < 3; i++ ) m_pSchool[i]->SetVisibleSingle(FALSE);
	m_pSchool[nSchool]->SetVisibleSingle(TRUE);
}

void CPartySlot::SetInfo(CString strLevel, CString strMap, CString strName, CString strPos, BOOL bSELF )
{
	m_strName = "";
	m_pLevelText->ClearText();
	m_pMapText->ClearText();
	m_pNameText->ClearText();
	m_pPosText->ClearText();

	m_pPosText->SetVisibleSingle(IsSameMap());
	D3DCOLOR dwColor =	IsDie() && IsSameMap() ? NS_UITEXTCOLOR::RED : !IsDie() && IsSELECT() ? NS_UITEXTCOLOR::GOLD : NS_UITEXTCOLOR::WHITE;
	m_pLevelText->AddTextNoSplit( strLevel, dwColor );
	m_pMapText->AddTextNoSplit( strMap, dwColor );
	m_pNameText->AddTextNoSplit( strName, dwColor );
	m_pPosText->AddTextNoSplit( strPos, dwColor );

	m_strName = strName;

/*	BOOL bFriend = FALSE;
	if ( !bSELF )
	{
		SFRIEND* pFriend = GLFriendClient::GetInstance().GetFriend (strName.GetString());
		if ( pFriend && !pFriend->IsBLOCK () )
			bFriend = TRUE;
	}
	else
	{
		bFriend = bSELF;
	}
	m_pAddFriendBtn->SetVisibleSingle(!bFriend );*/
}

void CPartySlot::SetSelect(BOOL bSELECT)
{
	m_bSelect = bSELECT;
	if ( m_pSelect ) m_pSelect->SetVisibleSingle(bSELECT);
}