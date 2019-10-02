#include "StdAfx.h"
#include "LargeMapWindow.h"
#include "LargeMapWindowMob.h"
#include "LargeMapWindowCheckBox.h"

#include "../RanClientLib/G-Logic/GLContrlServerMsg.h"
#include "../RanClientLib/G-Logic/GLCrowData.h"
#include "../RanClientLib/G-Logic/GLItemMan.h"

#include "../RanClientUILib/Interface/InnerInterface.h"
#include "../RanClientUILib/Interface/BasicLineBox.h"
#include "../RanClientUILib/Interface/BasicLineBoxEx.h"
#include "../RanClientUILib/Interface/BasicTextBoxEx.h"
#include "../RanClientUILib/Interface/BasicScrollBarEx.h"
#include "../RanClientUILib/Interface/UITextControl.h"
#include "../RanClientUILib/Interface/GameTextControl.h"

#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CLargeMapWindowMob::nSTARTLINE = 0;
const int CLargeMapWindowMob::nOUTOFRANGE = -1;

CLargeMapWindowMob::CLargeMapWindowMob ():
	m_nONE_VIEW_SLOT ( 10 ),
	m_nCurPos ( -1 )
{
	SecureZeroMemory ( m_pMob, sizeof( m_pMob ) );
	SecureZeroMemory ( m_pMobArrayDummy, sizeof( m_pMobArrayDummy ) );
}

CLargeMapWindowMob::~CLargeMapWindowMob ()
{
}

void CLargeMapWindowMob::CreateSubControl()
{
	m_pMobMain = CreateMobSlot( "MAP_WINDOW_INFO_TAP_MONSTER0_CHECKBOX", CROW_MAIN );
	m_pMobMain->SetTextTitle( ID2GAMEWORD("MAP_MONSTER_INFO",0), NS_UITEXTCOLOR::WHITE );

	CString strSlotKeyword[nMAX_ONE_VIEW_SLOT] =
	{
		"MAP_WINDOW_INFO_TAP_MONSTER1_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER2_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER3_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER4_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER5_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER6_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER7_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER8_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER9_CHECKBOX",
		"MAP_WINDOW_INFO_TAP_MONSTER10_CHECKBOX"
	};

	for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ )	m_pMobArrayDummy[i] = CreateControl ( strSlotKeyword[i].GetString () );
	for ( int i = 0; i < MAXCROW; i++ )				m_pMob[i] = CreateMobSlot ( strSlotKeyword[0], CROW_SLOT0 + i );

	{
		m_pScrollBar = new CBasicScrollBarEx;
		m_pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
		m_pScrollBar->CreateBaseScrollBar ( "MAP_WINDOW_INFO_TAP_MONSTER_LIST_SCROLL" );
		m_pScrollBar->GetThumbFrame()->SetState ( MAXCROW, nMAX_ONE_VIEW_SLOT );
		RegisterControl ( m_pScrollBar );
	}
}

void CLargeMapWindowMob::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	for( int i = m_nIndex; i < MAXCROW; i++ ) m_pMob[i]->SetVisibleSingle(FALSE);

	if ( m_pScrollBar )
	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
		int nTotal = pThumbFrame->GetTotal ();

		if ( nTotal < nMAX_ONE_VIEW_SLOT ) return ;
	
		const int nViewPerPage = pThumbFrame->GetViewPerPage ();
		if ( nViewPerPage <= nTotal )
		{
			int nCurPos = nSTARTLINE;
			const int nMovableLine = nTotal - nViewPerPage;
			float fPercent = pThumbFrame->GetPercent ();

			nCurPos = (int)floor(fPercent * nMovableLine);
			if ( nCurPos < nSTARTLINE ) nCurPos = nSTARTLINE;

			if ( m_nCurPos == nCurPos ) return;

			m_nCurPos = nCurPos;

			ResetAllCrowRender ( nTotal );
			SetCrowRender ( nCurPos, nCurPos + nViewPerPage );
		}
	}

	if ( m_nIndex == 0 ) m_pScrollBar->SetVisibleSingle(FALSE);
	else m_pScrollBar->SetVisibleSingle(TRUE);
}

void CLargeMapWindowMob::TranslateUIMessage ( UIGUID cID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( cID, dwMsg );

	if ( CROW_SLOT0 <= cID && cID < CROW_SLOT_END )
	{
		if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
		{
			const int nIndex = cID - CROW_SLOT0;
			m_pMob[nIndex]->SetCheck();
			CInnerInterface::GetInstance().GetLargeMapWindow()->m_bMOB[nIndex] = m_pMob[nIndex]->IsChecked();
		}
	}

	switch(cID)
	{
	case CROW_MAIN:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE(dwMsg))
			{
				m_pMobMain->SetCheck();
				for(int i = 0; i < m_nIndex; i++ )
				{
					if ( m_pMobMain->IsChecked()) m_pMob[i]->ForceCheck();
					else m_pMob[i]->ForceUnCheck();

					CInnerInterface::GetInstance().GetLargeMapWindow()->m_bMOB[i] = m_pMobMain->IsChecked();
				}
			}
		}
		break;
	}
}

void CLargeMapWindowMob::LoadMob (NET_MSG_GENERIC* nmg)
{
	GLMSG::SNETPC_REQ_CROWLIST_FB* pNetMsg = (GLMSG::SNETPC_REQ_CROWLIST_FB*)nmg;
    PCROWDATA pCrow = GLCrowDataMan::GetInstance().GetCrowData( pNetMsg->sCrowID.wMainID, pNetMsg->sCrowID.wSubID );

	if ( pCrow )
	{
		CString strName;
		strName.Format("%s", pCrow->GetName());
		m_pMob[m_nIndex]->SetText(strName, NS_UITEXTCOLOR::WHITE, pCrow->sNativeID );
		m_pMob[m_nIndex]->SetVisibleSingle(TRUE);
		m_sNativeID[m_nIndex] = pCrow->sNativeID;
		m_nIndex++;
	}

	ResetAllCrowRender (m_nIndex);
	SetCrowRender( 0, 10 );

	m_pScrollBar->GetThumbFrame()->SetState( m_nIndex, 10 );
}

void CLargeMapWindowMob::ClearMobList()
{
	m_nIndex = 0;
	for( int i = 0; i < MAXCROW; i++ ) m_pMob[i]->ClearText();
}

CUIControl*	CLargeMapWindowMob::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CLargeMapWindowCheckBox* CLargeMapWindowMob::CreateMobSlot ( CString strKeyword, UIGUID ControlID )
{
	CLargeMapWindowCheckBox* pCrowSlot = new CLargeMapWindowCheckBox;
	pCrowSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pCrowSlot->CreateSubControl();
	pCrowSlot->SetVisibleSingle(TRUE);
	RegisterControl ( pCrowSlot );

	return pCrowSlot;
}

void CLargeMapWindowMob::SetCrowRender ( int nStartIndex, int nTotal )
{
	if ( nTotal < 0 ) return ;

	const UIRECT& rcParentPos = GetGlobalPos ();

	for ( int i = nStartIndex; i < nTotal; i++ )
	{
		CLargeMapWindowCheckBox* pMob = m_pMob[i];

		if ( pMob )
		{
			int nAbsoluteIndex = i - nStartIndex;

			CUIControl* pDummyControl = m_pMobArrayDummy[nAbsoluteIndex];			
			const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
			const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();

			pMob->SetLocalPos ( rcSlotLocalPos );
			pMob->SetGlobalPos ( rcSlotPos );

			pMob->SetVisibleSingle ( TRUE );
		}
	}
}

void CLargeMapWindowMob::ResetAllCrowRender ( int nTotal )
{
	if ( nTotal < 0 ) return ;

	for ( int i = 0; i < nTotal; i++ )
	{
		CLargeMapWindowCheckBox* pMob = m_pMob[i];
		if ( pMob ) pMob->SetVisibleSingle ( FALSE );
	}
}