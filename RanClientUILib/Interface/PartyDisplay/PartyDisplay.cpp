#include "StdAfx.h"
#include "PartySlotDisplay.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"
#include "PartyDisplay.h"
#include "../RanClientUILib/Interface/InnerInterface.h"
#include "PartyDisplayBuffInfo.h"

#include "GLGaeaClient.h"
#include "GLPartyClient.h"
#include "../RanClientUILib/Interface/BasicLineBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartyDisplay::CPartyDisplay ()
{
	for(int i = 0; i < MAXPARTY; i++ )
	{
		m_pPartySlot[i] = NULL;
	}
}

CPartyDisplay::~CPartyDisplay ()
{
}

void CPartyDisplay::CreateSubControl ()
{		
	CString strMemberKeyword[MAXPARTY] = 
	{
		"PARTYDISPLAY_SLOT_MEMBER0",
		"PARTYDISPLAY_SLOT_MEMBER1",
		"PARTYDISPLAY_SLOT_MEMBER2",
		"PARTYDISPLAY_SLOT_MEMBER3",
		"PARTYDISPLAY_SLOT_MEMBER4",
		"PARTYDISPLAY_SLOT_MEMBER5",
		"PARTYDISPLAY_SLOT_MEMBER6",
		"PARTYDISPLAY_SLOT_MEMBER7",
	};

	for ( int i = 0; i < MAXPARTY; i++ )
	{
		CPartySlotDisplay* pPartySlot = new CPartySlotDisplay;
		pPartySlot->CreateSub ( this, strMemberKeyword[i].GetString (), UI_FLAG_DEFAULT, PARTYDISPLAY_SLOT_MEMBER0 + i );
		pPartySlot->CreateSubControl ();
		RegisterControl ( pPartySlot );
		m_pPartySlot[i] = pPartySlot;
	}
}

void CPartyDisplay::SetSlotMember ( CPartySlotDisplay* pPartySlot, GLPARTY_CLIENT *pMember, BOOL bSameMap, const int nPartySlotID )
{
	if ( !pPartySlot || !pMember )
	{
		return ;
	}
	
	pPartySlot->SetVisibleSingle ( TRUE );
}

void CPartyDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	m_bCHECK_MOUSE_STATE = false; 

	m_PosX = x;
	m_PosY = y;

	const UIRECT& rcGlobalPos = GetGlobalPos ();

	m_bMOUSEIN = false; 

	m_rcOriginalPos = GetGlobalPos();
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( IsExclusiveSelfControl() )
	{
		SetLocalPos ( D3DXVECTOR2 ( m_vGap.x, m_vGap.y ) );
	}

	for ( int i = 0; i < MAXPARTY; i++ ) 
	{
		m_pPartySlot[i]->SetVisibleSingle ( FALSE );
	}

	GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();	

	if( pMaster )
	{
		GLPARTY_CLIENT *pSelf = FindSelfClient ();
		if ( !pSelf ) return ;

		SetSlotMember ( m_pPartySlot[0], pMaster, IsSameMap ( pSelf, pMaster ), 0 );

		DWORD nMEMBER_NUM = GLPartyClient::GetInstance().GetMemberNum();
		if( nMEMBER_NUM > 1 )
		{
			nMEMBER_NUM -= 1; 
			for ( DWORD i = 0; i < nMEMBER_NUM; i++ )
			{
				GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember ( i );			
				if ( pMember )
				{				
					const BOOL bONESELF = pMember->ISONESELF ();

					SetSlotMember ( m_pPartySlot[i+1], pMember, IsSameMap ( pSelf, pMember ), i + 1 );
				}
			}
		}
	}
}


BOOL CPartyDisplay::IsSameMap ( GLPARTY_CLIENT *pSelf, GLPARTY_CLIENT *pMember )
{
	if ( !pSelf || !pMember )
	{
		GASSERT ( 0 && "잘못된 데이타입니다." );
		return FALSE;
	}

	return pSelf->m_sMapID.dwID == pMember->m_sMapID.dwID;
}

GLPARTY_CLIENT*	CPartyDisplay::FindSelfClient ()
{
	GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();
	if ( pMaster && pMaster->ISONESELF() )
	{
		return pMaster;
	}
	else
	{
		DWORD nMEMBER_NUM = GLPartyClient::GetInstance().GetMemberNum();
		if( nMEMBER_NUM > 1 )
		{
			nMEMBER_NUM -= 1;
			for ( DWORD i = 0; i < nMEMBER_NUM; i++ )
			{
				GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember( i );
				if ( pMember && pMember->ISONESELF () )
				{
					return pMember;				
				}
			}
		}
	}

	return NULL;
}

void CPartyDisplay::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( !m_bCHECK_MOUSE_STATE )
	{
		CheckMouseState ();
		m_bCHECK_MOUSE_STATE = true;
	}

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( PARTY_DISPLAY );
			}
		}
		break;
	case PARTYDISPLAY_SLOT_MEMBER0:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if (CHECK_MOUSEIN_RBUPLIKE(dwMsg))
				{
					GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();
					if ( pMaster )
					{
						STARGETID sTARID(CROW_PC,pMaster->m_dwGaeaID);
						GLGaeaClient::GetInstance().GetCharacter ()->ReqSkillReaction(sTARID);
					}
				}
			}
		}
		break;
	case PARTYDISPLAY_SLOT_MEMBER1:
	case PARTYDISPLAY_SLOT_MEMBER2:
	case PARTYDISPLAY_SLOT_MEMBER3:
	case PARTYDISPLAY_SLOT_MEMBER4:
	case PARTYDISPLAY_SLOT_MEMBER5:
	case PARTYDISPLAY_SLOT_MEMBER6:
	case PARTYDISPLAY_SLOT_MEMBER7:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if (CHECK_MOUSEIN_RBUPLIKE(dwMsg))
				{
					int nIndex = ControlID - PARTYDISPLAY_SLOT_MEMBER1;

					GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember( nIndex );
					if ( pMember )
					{
						STARGETID sTARID(CROW_PC,pMember->m_dwGaeaID);
						GLGaeaClient::GetInstance().GetCharacter ()->ReqSkillReaction(sTARID);
					}
				}
			}
		}
		break;
	case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( GetWndID () );
				CInnerInterface::GetInstance().ShowGroupBottom ( GetWndID () );
			}
		}
		break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}

void CPartyDisplay::CheckMouseState ()
{
	const DWORD dwMsg = GetMessageEx ();
	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{	
		if ( dwMsg & UIMSG_LB_DOWN )
		{
			SetExclusiveControl();	
			m_vGap.x = m_PosX;
			m_vGap.y = m_PosY;
		}
		else if ( CHECK_LB_UP_LIKE ( dwMsg ) )
		{
			ResetExclusiveControl();			
		}
	}
	else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
	{								
		ResetExclusiveControl();				
	}
}