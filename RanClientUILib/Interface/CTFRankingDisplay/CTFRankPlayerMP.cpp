#include "StdAfx.h"
#include "CTFRankPlayerMP.h"
#include "CTFRankPlayerBase.h"
#include "CTFRankPlayerSlot.h"
#include "../BasicLineBox.h"
#include "../BasicScrollBarEx.h"
#include "../../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "../RanClientLib/G-Logic/GLCaptureTheField/GLCaptureTheFieldData.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFRankPlayerMP::CCTFRankPlayerMP () :
	m_pBase( NULL )
	, m_pScrollBar(NULL)
	, m_nStart( 0 )
	, m_nTotal( 0 )
{
	for ( int i=0; i < CTF_PLAYER_SLOT_MAX; ++ i )
	{
		m_pSlot[i] = NULL;
	}

}

CCTFRankPlayerMP::~CCTFRankPlayerMP ()
{
}

void CCTFRankPlayerMP::CreateSubControl ()
{
	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CTF_RESULT_RANKING_LINEBOX" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CTF_RESULT_RANK_SCROLLBAR_BACKGROUND" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "CTF_RESULT_RANKING_LINE_BOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxNoBody ( 
		"CTF_RESULT_RANKING_LINEBOX",
		"CTF_RESULT_RANKING_LINE_BOX_LEFT", "CTF_RESULT_RANKING_LINE_BOX_RIGHT", "CTF_RESULT_RANKING_LINE_BOX_TOP", "CTF_RESULT_RANKING_LINE_BOX_BOTTOM" );
	RegisterControl ( pBasicLineBox );

	pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub ( this, "CTF_RESULT_RANKING_LINE_BOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxNoBody ( 
		"CTF_RESULT_RANKING_LINEBOX2",
		"CTF_RESULT_RANKING_LINE_BOX_LEFT", "CTF_RESULT_RANKING_LINE_BOX_RIGHT", "CTF_RESULT_RANKING_LINE_BOX_TOP", "CTF_RESULT_RANKING_LINE_BOX_BOTTOM" );
	RegisterControl ( pBasicLineBox );

	m_pBase = new CCTFRankPlayerBase;
	m_pBase->CreateSub( this, "CTF_RESULT_RANKSLOT_BASE" );
	m_pBase->CreateSubControl();
	RegisterControl( m_pBase );

	m_pScrollBar = new CBasicScrollBarEx;
	m_pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, RANKPLAYER_SCROLLBAR );
	m_pScrollBar->CreateBaseScrollBar ( "CTF_RESULT_RANK_SCROLLBAR" );
	m_pScrollBar->GetThumbFrame()->SetState ( 1, 10 );
	RegisterControl ( m_pScrollBar );


	std::string strSLOT_PLAYER[CTF_PLAYER_SLOT_MAX] = 
	{
		"CTF_RESULT_RANKSLOT_00",
		"CTF_RESULT_RANKSLOT_01",
		"CTF_RESULT_RANKSLOT_02",
		"CTF_RESULT_RANKSLOT_03",
		"CTF_RESULT_RANKSLOT_04",
		"CTF_RESULT_RANKSLOT_05",
		"CTF_RESULT_RANKSLOT_06",
		"CTF_RESULT_RANKSLOT_07",
		"CTF_RESULT_RANKSLOT_08",
		"CTF_RESULT_RANKSLOT_09",
	};

	for ( int i=0; i < CTF_PLAYER_SLOT_MAX; ++ i )
	{
		m_pSlot[i] = new CCTFRankPlayerSlot;
		m_pSlot[i]->CreateSub ( this, strSLOT_PLAYER[i].c_str() );
		m_pSlot[i]->CreateSubControl ();
		RegisterControl ( m_pSlot[i] );	
		m_pSlot[i]->SetVisibleSingle( FALSE );
	}
}


void CCTFRankPlayerMP::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_nTotal = (int)GLGaeaClient::GetInstance().m_CaptureTheFieldRankingPlayerMPVec.size();

	if ( m_pScrollBar )
	{
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal();

			if( nTotal != m_nTotal )
				m_pScrollBar->GetThumbFrame()->SetState ( m_nTotal, CTF_PLAYER_SLOT_MAX );	
		}
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal ();
			if ( nTotal <= CTF_PLAYER_SLOT_MAX ) return ;
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

void CCTFRankPlayerMP::RefreshRanking()
{
	m_nTotal = (int)GLGaeaClient::GetInstance().m_CaptureTheFieldRankingPlayerMPVec.size();

	RenderView();
}

void CCTFRankPlayerMP::RenderView()
{
	for ( int i=0; i < CTF_PLAYER_SLOT_MAX; ++ i )
	{
		if ( m_pSlot[i] )
		{
			m_pSlot[i]->DataReset();
			m_pSlot[i]->SetVisibleSingle( FALSE );
		}
	}

	CTF_RANK_PLAYER_CLIENT_VEC& vecRank = GLGaeaClient::GetInstance().m_CaptureTheFieldRankingPlayerMPVec;

	int nEnd = m_nStart + CTF_PLAYER_SLOT_MAX;
	int nSlot = 0;

	for ( int i = m_nStart; i < nEnd; ++ i )
	{
		if ( i >= vecRank.size() )	continue;
		if ( m_pSlot[nSlot] )
		{
			SCTF_RANK_PLAYER_CLIENT sRANK = vecRank[i];
			m_pSlot[nSlot]->SetVisibleSingle( TRUE );
			m_pSlot[nSlot]->DataUpdate( sRANK.wRanking, sRANK.szCharName, sRANK.cSCHOOL, sRANK.cCLASS, sRANK.llDAMAGE, sRANK.wKillNum, sRANK.wDeathNum );
			nSlot ++ ;
		}
	}
}

void CCTFRankPlayerMP::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );
}

void CCTFRankPlayerMP::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

}

