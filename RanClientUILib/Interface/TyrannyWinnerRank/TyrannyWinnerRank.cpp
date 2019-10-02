#include "StdAfx.h"
#include "TyrannyWinnerRank.h"
#include "TyrannyWinnerRankSlot.h"
#include "../InnerInterface.h"
#include "../BasicTextButton.h"
#include "../GameTextControl.h"
#include "../BasicScrollBarEx.h"
#include "../../EngineUiLib/GUInterface/BasicScrollThumbFrame.h"
#include "../RanClientLib/G-Logic/GLTowerWarsDefine.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTyrannyWinnerRank::CTyrannyWinnerRank () :
	m_pBackGround( NULL )
	, m_pScrollBar(NULL)
	, m_nStart( 0 )
	, m_nTotal( 0 )
{
	for ( int i=0; i < TW_PLAYER_SLOT_MAX; ++ i )
	{
		m_pRankSlot[i] = NULL;
	}
}

CTyrannyWinnerRank::~CTyrannyWinnerRank ()
{
}

void CTyrannyWinnerRank::CreateSubControl ()
{	
	m_pBackGround = new CUIControl;
	m_pBackGround->CreateSub ( this, "TW_RANKING_BG", UI_FLAG_DEFAULT );	
	m_pBackGround->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pBackGround );

	m_pScrollBar = new CBasicScrollBarEx;
	m_pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, RANKPLAYER_SCROLLBAR );
	m_pScrollBar->CreateBaseScrollBar ( "TW_RANKING_SCROLL" );
	m_pScrollBar->GetThumbFrame()->SetState ( 1, 10 );
	RegisterControl ( m_pScrollBar );


	std::string strSLOT_PLAYER[TW_PLAYER_SLOT_MAX] = 
	{
		"TW_RANKING_SLOT_00",
		"TW_RANKING_SLOT_01",
		"TW_RANKING_SLOT_02",
		"TW_RANKING_SLOT_03",
		"TW_RANKING_SLOT_04",
		"TW_RANKING_SLOT_05",
		"TW_RANKING_SLOT_06",
		"TW_RANKING_SLOT_07",
		"TW_RANKING_SLOT_08",
		"TW_RANKING_SLOT_09",
	};

	for ( int i=0; i < TW_PLAYER_SLOT_MAX; ++ i )
	{
		m_pRankSlot[i] = new CTyrannyWinnerRankSlot;
		m_pRankSlot[i]->CreateSub ( this, strSLOT_PLAYER[i].c_str() );
		m_pRankSlot[i]->CreateSubControl ();
		RegisterControl ( m_pRankSlot[i] );	
		m_pRankSlot[i]->SetVisibleSingle( FALSE );
	}

}

void CTyrannyWinnerRank::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( TYRANNY_WINNER_DISPLAY );
			}
		}break;
	case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			}
		}break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}

void CTyrannyWinnerRank::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_nTotal = (int)GLGaeaClient::GetInstance().m_TowerWarsWinnerVec.size();

	if ( m_pScrollBar )
	{
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal();

			if( nTotal != m_nTotal )
				m_pScrollBar->GetThumbFrame()->SetState ( m_nTotal, TW_PLAYER_SLOT_MAX );	
		}
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal ();
			if ( nTotal <= TW_PLAYER_SLOT_MAX ) return ;
			const int nViewPerPage = pThumbFrame->GetViewPerPage ();

			if ( nViewPerPage < nTotal )
			{
				int nCurPos = 0;
				const int nMovableLine = nTotal - nViewPerPage;
				float fPercent = pThumbFrame->GetPercent ();
				nCurPos = (int)floor(fPercent * nMovableLine);
				if ( nCurPos < 0 ) nCurPos = 0;
				if ( m_nStart == nCurPos ) return;
				m_nStart = nCurPos;
				RenderView();
			}
		}
	}
}

void CTyrannyWinnerRank::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle( bVisible );
}

void CTyrannyWinnerRank::RefreshRanking()
{
	
	m_nTotal = (int)GLGaeaClient::GetInstance().m_TowerWarsWinnerVec.size();

	RenderView();
}

void CTyrannyWinnerRank::RenderView()
{
	for ( int i=0; i < TW_PLAYER_SLOT_MAX; ++ i )
	{
		if ( m_pRankSlot[i] )
		{
			m_pRankSlot[i]->DataReset();
			m_pRankSlot[i]->SetVisibleSingle( FALSE );
		}
	}

	TWP_RANK_VEC& vecRank = GLGaeaClient::GetInstance().m_TowerWarsWinnerVec;

	int nEnd = m_nStart + TW_PLAYER_SLOT_MAX;
	int nSlot = 0;

	for ( int i = m_nStart; i < nEnd; ++ i )
	{
		if ( i >= (int)vecRank.size() )	continue;
		if ( m_pRankSlot[nSlot] )
		{
			STWP_RANK sRANK = vecRank[i];
			m_pRankSlot[nSlot]->SetVisibleSingle( TRUE );
			m_pRankSlot[nSlot]->DataUpdate( sRANK.wCharRanking, sRANK.szCharName, sRANK.wSchool, sRANK.dwClass, sRANK.dwCharID );
			nSlot ++ ;
		}
	}
}

