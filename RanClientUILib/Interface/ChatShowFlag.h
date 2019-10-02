#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"

////////////////////////////////////////////////////////////////////
//	사용자 메시지 정의
const DWORD UIMSG_CHAT_NORMAL	= UIMSG_USER1;
const DWORD UIMSG_CHAT_PRIVATE	= UIMSG_USER2;
const DWORD UIMSG_CHAT_PARTY	= UIMSG_USER3;
const DWORD UIMSG_CHAT_CLUB		= UIMSG_USER4;
const DWORD UIMSG_CHAT_ALLIANCE = UIMSG_USER5;
const DWORD UIMSG_CHAT_SYSTEM	= UIMSG_USER6;
const DWORD UIMSG_CHAT_REGION	= UIMSG_USER7;

class	CBasicButton;
class	CBasicTextBox;

class	CUIChatShowFlag : public CUIGroup
{
private:
	enum
	{
		CHAT_NORMAL_CHECK = NO_ID + 1,
		CHAT_PRIVATE_CHECK,
		CHAT_PARTY_CHECK,
		CHAT_CLUB_CHECK,
		CHAT_REGION_CHECK,
		CHAT_ALLIANCE_CHECK,
		CHAT_SYSTEM_CHECK,

		CHAT_NORMAL_TEXTBOX,
		CHAT_PRIVATE_TEXTBOX,
		CHAT_PARTY_TEXTBOX,
		CHAT_CLUB_TEXTBOX,
		CHAT_REGION_TEXTBOX,
		CHAT_ALLIANCE_TEXTBOX,
		CHAT_SYSTEM_TEXTBOX
	};

public:
	CUIChatShowFlag ();
	virtual	~CUIChatShowFlag ();

	void	CreateSubControl ();

private:
    CBasicButton*	CreateButton ( const CString& strKeyword, const CString& strFlipKeyword, const UIGUID& cID );
	CBasicTextBox*	CreateTextBox ( const CString& strKeyword, const CString& strText, const UIGUID& cID );

public:
	virtual void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID cID, DWORD dwMsg );

private:
	CBasicButton*	m_pNormalButton;
	CBasicButton*	m_pPrivateButton;
	CBasicButton*	m_pPartyButton;
	CBasicButton*	m_pClubButton;
	CBasicButton*	m_pRegionButton;
	CBasicButton*	m_pAllianceButton;
	CBasicButton*	m_pSystemButton;

	CBasicTextBox*	m_pNormalTextBox;
	CBasicTextBox*	m_pPrivateTextBox;
	CBasicTextBox*	m_pPartyTextBox;
	CBasicTextBox*	m_pClubTextBox;
	CBasicTextBox*	m_pRegionTextBox;
	CBasicTextBox*	m_pAllianceTextBox;
	CBasicTextBox*	m_pSystemTextBox;
};