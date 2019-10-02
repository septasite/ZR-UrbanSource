#include "StdAfx.h"
#include "MiniPartyWindow.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "MiniPartySlot.h"
#include "InnerInterface.h"
#include "PartyBuffInfo.h"

#include "GLGaeaClient.h"
#include "GLPartyClient.h"
#include "BasicLineBox.h"
#include "GLChar.h"
#include "GLGaeaServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMiniPartyWindow::CMiniPartyWindow ()
	: m_pPartyBuffInfo(NULL)
{
	memset( m_pPartySlot, 0, sizeof(m_pPartySlot) );
	memset( m_pSlotOver, 0, sizeof(m_pSlotOver) );
}

CMiniPartyWindow::~CMiniPartyWindow ()
{
}

void CMiniPartyWindow::CreateSubControl ()
{	
	int nTextAlign = TEXT_ALIGN_LEFT;
	D3DCOLOR dwFontColor = NS_UITEXTCOLOR::DEFAULT;
	
	{
		m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "RNMINIPARTY_WINDOW_REGION", UI_FLAG_DEFAULT);	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	}
	{
		m_pBackLine1 = new CBasicLineBox;
		m_pBackLine1->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine1->CreateBaseBoxSkill ( "RNMINIPARTY_WINDOW_SLOT_BACK" );
		RegisterControl ( m_pBackLine1 );
	}
	
	{
		m_pLineBox0 = new CBasicLineBoxEx;
		m_pLineBox0->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox0->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER0" );
		m_pLineBox0->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox0 );

		m_pLineBox1 = new CBasicLineBoxEx;
		m_pLineBox1->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox1->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER1" );
		m_pLineBox1->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox1 );

		m_pLineBox2 = new CBasicLineBoxEx;
		m_pLineBox2->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox2->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER2" );
		m_pLineBox2->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox2 );

		m_pLineBox3 = new CBasicLineBoxEx;
		m_pLineBox3->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox3->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER3" );
		m_pLineBox3->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox3 );

		m_pLineBox4 = new CBasicLineBoxEx;
		m_pLineBox4->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox4->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER4" );
		m_pLineBox4->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox4 );

		m_pLineBox5 = new CBasicLineBoxEx;
		m_pLineBox5->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox5->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER5" );
		m_pLineBox5->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox5 );

		m_pLineBox6 = new CBasicLineBoxEx;
		m_pLineBox6->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox6->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER6" );
		m_pLineBox6->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox6 );

		m_pLineBox7 = new CBasicLineBoxEx;
		m_pLineBox7->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBox7->CreateBaseBoxDialogueWhite ( "MINIPARTY_LINEBOX_OVER7" );
		m_pLineBox7->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBox7 );
	}
	

	CBasicTextBox* pTextBox = NULL;

	CString strMemberKeyword[MAXPARTY] = 
	{
		"MINIPARTY_SLOT_MEMBER0",
		"MINIPARTY_SLOT_MEMBER1",
		"MINIPARTY_SLOT_MEMBER2",
		"MINIPARTY_SLOT_MEMBER3",
		"MINIPARTY_SLOT_MEMBER4",
		"MINIPARTY_SLOT_MEMBER5",
		"MINIPARTY_SLOT_MEMBER6",
		"MINIPARTY_SLOT_MEMBER7",
	};

	for ( int i = 0; i < MAXPARTY; i++ )
	{
		CMiniPartySlot* pPartySlot = new CMiniPartySlot;
		pPartySlot->CreateSub ( this, strMemberKeyword[i].GetString (), UI_FLAG_DEFAULT, MINIPARTY_SLOT_MEMBER0 + i );
		pPartySlot->CreateSubControl ();
		RegisterControl ( pPartySlot );
		m_pPartySlot[i] = pPartySlot;
	}
	
	/*CString strMemberOverKeyword[MAXPARTY] =
	{
		"MINIPARTY_SLOT_OVER0",
		"MINIPARTY_SLOT_OVER1",
		"MINIPARTY_SLOT_OVER2",
		"MINIPARTY_SLOT_OVER3",
		"MINIPARTY_SLOT_OVER4",
		"MINIPARTY_SLOT_OVER5",
		"MINIPARTY_SLOT_OVER6",
		"MINIPARTY_SLOT_OVER7",
	};

	for ( int i = 0; i < MAXPARTY; i++ )
	{
		CUIControl* pSlotOver = new CUIControl;
		pSlotOver->CreateSub ( this, strMemberOverKeyword[i].GetString () );
		RegisterControl ( pSlotOver );
		m_pSlotOver[i] = pSlotOver;
		pSlotOver->SetVisibleSingle ( FALSE );
	}*/
	
	

	//	NOTE
	//		버프 남은 시간 표시
	{
		CPartyBuffInfo* pPartyBuffInfo = new CPartyBuffInfo;
		pPartyBuffInfo->CreateSub ( this, "MINIPARTY_BUFF_INFO", UI_FLAG_DEFAULT, MINIPARTY_BUFF_INFO );
		pPartyBuffInfo->CreateSubControl ();
		RegisterControl ( pPartyBuffInfo );
		m_pPartyBuffInfo = pPartyBuffInfo;
	}
}
//waley to, magulo pa logic mo.
//ggwa ka muna ng 'setslotmember' version ng sw rank window, then after that tsaka ka ggwa ng refresher, gaya nitong setslotmember wait
void CMiniPartyWindow::SetSlotMember ( CMiniPartySlot* pPartySlot, GLPARTY_CLIENT *pMember, BOOL bSameMap, const int nPartySlotID )
{
	if ( !pPartySlot || !pMember )
	{
		GASSERT ( 0 && "CMiniPartyWindow::SetSlotMember()" );
		return ;
	}
	if( bSameMap )
	{
		float fHPPercent = 0.0f;
		if( pMember->m_sHP.dwMax != 0 )
		{
			fHPPercent = float(pMember->m_sHP.dwNow) / float(pMember->m_sHP.dwMax);
		}
		pPartySlot->SetHP( fHPPercent );
		pPartySlot->SetPlayerName ( pMember->m_szName );	
		pPartySlot->SetPlayerNameColor ( pMember->m_sHP.dwNow );
		pPartySlot->IsPlayerSameMap ( bSameMap );
	}
	else
	{
		float fHPPercent = 100.0f;
		pPartySlot->SetHP ( fHPPercent );
		pPartySlot->SetPlayerName ( "" );
		pPartySlot->IsPlayerSameMap ( !bSameMap );
	}
	const int nClassType = CharClassToIndex ( pMember->m_emClass );
	pPartySlot->SetClass ( nClassType );
	pPartySlot->SetSchool ( pMember->m_wSchool );
	pPartySlot->SetNumber( nPartySlotID );

	pPartySlot->SetVisibleSingle ( TRUE );
}

void CMiniPartyWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if( !IsVisible() )	return ;

	const UIRECT& rcGlobalPos = GetGlobalPos ();
	m_pPartyBuffInfo->SetLocalPos ( D3DXVECTOR2 ( x + 25 - rcGlobalPos.left, y + 25 - rcGlobalPos.top ) );
	
	m_bMOUSEIN = false; 

	for ( int i = 0; i < MAXPARTY; i++ )
	{
		m_pPartySlot[i]->SetNameColorDefault();
	}
	/*for ( int i = 0; i < MAXPARTY; i++ )
	{
		m_pSlotOver[i]->SetVisibleSingle ( FALSE );
	}*/

	m_pLineBox0->SetVisibleSingle ( FALSE );
	m_pLineBox1->SetVisibleSingle ( FALSE );
	m_pLineBox2->SetVisibleSingle ( FALSE );
	m_pLineBox3->SetVisibleSingle ( FALSE );
	m_pLineBox4->SetVisibleSingle ( FALSE );
	m_pLineBox5->SetVisibleSingle ( FALSE );
	m_pLineBox6->SetVisibleSingle ( FALSE );
	m_pLineBox7->SetVisibleSingle ( FALSE );

	m_pPartyBuffInfo->SetVisibleSingle ( FALSE );

	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

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
			nMEMBER_NUM -= 1; // Note : 마스터는 제외
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


BOOL CMiniPartyWindow::IsSameMap ( GLPARTY_CLIENT *pSelf, GLPARTY_CLIENT *pMember )
{
	if ( !pSelf || !pMember )
	{
		GASSERT ( 0 && "잘못된 데이타입니다." );
		return FALSE;
	}

	return pSelf->m_sMapID.dwID == pMember->m_sMapID.dwID;
}

GLPARTY_CLIENT*	CMiniPartyWindow::FindSelfClient ()
{
	GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();
	if ( pMaster && pMaster->ISONESELF() )
	{
		return pMaster;
	}
	else
	{
		//	자기찾기
		DWORD nMEMBER_NUM = GLPartyClient::GetInstance().GetMemberNum();
		if( nMEMBER_NUM > 1 )
		{
			nMEMBER_NUM -= 1; // Note : 마스터는 제외
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

void CMiniPartyWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CMiniPartySlot pPartySlot;
	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( MINIPARTY_WINDOW );
			}
		}
		break;
	case MINIPARTY_SLOT_MEMBER0:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_bMOUSEIN = true;
				m_pLineBox0->SetVisibleSingle ( TRUE );
				m_pPartyBuffInfo->SetPartyID ( 0 );
				m_pPartyBuffInfo->SetVisibleSingle ( TRUE );
				//m_pPartySlot[0]->SetNameHover ();

				if ( dwMsg & UIMSG_MOUSEIN_RB_EVENT )
				{
					GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();	//	마스터
					if ( pMaster )
					{
						STARGETID sTARID(CROW_PC,pMaster->m_dwGaeaID);
						GLGaeaClient::GetInstance().GetCharacter ()->ReqSkillReaction(sTARID);
					}
				}
			}
		}
		break;

	case MINIPARTY_SLOT_MEMBER1:
	case MINIPARTY_SLOT_MEMBER2:
	case MINIPARTY_SLOT_MEMBER3:
	case MINIPARTY_SLOT_MEMBER4:
	case MINIPARTY_SLOT_MEMBER5:
	case MINIPARTY_SLOT_MEMBER6:
	case MINIPARTY_SLOT_MEMBER7:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_bMOUSEIN = true;
				int nIndex = ControlID - MINIPARTY_SLOT_MEMBER0;

				if ( nIndex == 1 ) { m_pLineBox1->SetVisibleSingle ( TRUE ); }
				else if ( nIndex == 2 ) { m_pLineBox2->SetVisibleSingle ( TRUE ); }
				else if ( nIndex == 3 ) { m_pLineBox3->SetVisibleSingle ( TRUE ); }
				else if ( nIndex == 4 ) { m_pLineBox4->SetVisibleSingle ( TRUE ); }
				else if ( nIndex == 5 ) { m_pLineBox5->SetVisibleSingle ( TRUE ); }
				else if ( nIndex == 6 ) { m_pLineBox6->SetVisibleSingle ( TRUE ); }
				else if ( nIndex == 7 ) { m_pLineBox7->SetVisibleSingle ( TRUE ); }

				m_pPartyBuffInfo->SetPartyID ( nIndex );
				m_pPartyBuffInfo->SetVisibleSingle ( TRUE );
				//m_pPartySlot[nIndex]->SetNameHover ();
				if ( dwMsg & UIMSG_MOUSEIN_RB_EVENT )
				{
					int nIndex = ControlID - MINIPARTY_SLOT_MEMBER1;
					GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();
					if ( pMaster )
					{
						GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember( nIndex );
						if ( pMember )
						{
							STARGETID sTARID(CROW_PC,pMember->m_dwGaeaID);
							GLGaeaClient::GetInstance().GetCharacter ()->ReqSkillReaction(sTARID);
						}
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
				CInnerInterface::GetInstance().ShowGroupBottom ( MINIPARTY_OPEN );
			}
		}
		break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}