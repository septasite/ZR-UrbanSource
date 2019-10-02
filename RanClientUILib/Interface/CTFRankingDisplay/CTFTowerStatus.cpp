#include "StdAfx.h"
#include "CTFTowerStatus.h"
#include "CTFTowerStatusSlot.h"
#include "../BasicLineBox.h"
#include "../BasicScrollBarEx.h"
#include "../../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "../RanClientLib/G-Logic/GLCaptureTheField/GLCaptureTheFieldData.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFTowerStatus::CCTFTowerStatus () :
	m_pScrollBar(NULL)
{
	for ( int i=0; i < TOWERSCORE_SLOT_MAX; ++ i )
	{
		m_pSlot[i] = NULL;
	}
}

CCTFTowerStatus::~CCTFTowerStatus ()
{
}

void CCTFTowerStatus::CreateSubControl ()
{
	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CTF_TOWER_LINE" );
	RegisterControl ( pBasicLineBox );

	m_pScrollBar = new CBasicScrollBarEx;
	m_pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, TOWERSCORE_SCROLLBAR );
	m_pScrollBar->CreateBaseScrollBar ( "CTF_TOWER_SCROLLBAR" );
	m_pScrollBar->GetThumbFrame()->SetState ( 1, 6 );
	RegisterControl ( m_pScrollBar );

	std::string strSLOT_PLAYER[TOWERSCORE_SLOT_MAX] = 
	{
		"CTF_TOWER_SLOT_0",
		"CTF_TOWER_SLOT_1",
		"CTF_TOWER_SLOT_2",
		"CTF_TOWER_SLOT_3",
		"CTF_TOWER_SLOT_4",
		"CTF_TOWER_SLOT_5",
	};

	for ( int i=0; i < TOWERSCORE_SLOT_MAX; ++ i )
	{
		m_pSlot[i] = new CCTFTowerStatusSlot;
		m_pSlot[i]->CreateSub ( this, strSLOT_PLAYER[i].c_str() );
		m_pSlot[i]->CreateSubControl ();
		RegisterControl ( m_pSlot[i] );	
		m_pSlot[i]->SetVisibleSingle( FALSE );
	}
}


void CCTFTowerStatus::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_nTotal = (int)GLGaeaClient::GetInstance().m_CaptureTheFieldTowerScoreVec.size();

	if ( m_pScrollBar )
	{
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal();

			if( nTotal != m_nTotal )
				m_pScrollBar->GetThumbFrame()->SetState ( m_nTotal, TOWERSCORE_SLOT_MAX );	
		}
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal ();
			if ( nTotal <= TOWERSCORE_SLOT_MAX ) return ;
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

void CCTFTowerStatus::RefreshRanking()
{
	m_nTotal = (int)GLGaeaClient::GetInstance().m_CaptureTheFieldTowerScoreVec.size();

	RenderView();
}

void CCTFTowerStatus::RenderView()
{
	for ( int i=0; i < TOWERSCORE_SLOT_MAX; ++ i )
	{
		if ( m_pSlot[i] )
		{
			m_pSlot[i]->DataReset();
			m_pSlot[i]->SetVisibleSingle( FALSE );
		}
	}

	CTF_SCORE_TOWER_VEC& vecRank = GLGaeaClient::GetInstance().m_CaptureTheFieldTowerScoreVec;

	int nEnd = m_nStart + TOWERSCORE_SLOT_MAX;
	int nSlot = 0;

	for ( int i = m_nStart; i < nEnd; ++ i )
	{
		if ( i >= vecRank.size() )	continue;
		if ( m_pSlot[nSlot] )
		{
			SCTF_SCORE_TOWER sDATA = vecRank[i];

			SNATIVEID sID  = sDATA.sCROWID;
			SCROWDATA* pCROW = GLCrowDataMan::GetInstance().GetCrowData( sID );
			if( pCROW )
			{
				m_pSlot[nSlot]->SetVisibleSingle( TRUE );
				m_pSlot[nSlot]->DataUpdate( pCROW->GetName(), sDATA.wOWNER );
				nSlot ++ ;
			}
		}
	}
}

void CCTFTowerStatus::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case TOWERSCORE_SCROLLBAR:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_CTF_SCROLLBAR );
			}
		}
		break;
	}
}

void CCTFTowerStatus::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

}

