#include "StdAfx.h"
#include "CCtfRankingPage2.h"
#include "CCtfRankingSlot.h"
#include "BasicTextBoxEx.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "d3dfont.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "BasicScrollBarEx.h"
#include "BasicTextButton.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CCtfRankingPage2::nSTARTLINE = 0;
const int CCtfRankingPage2::nOUTOFRANGE = -1;

CCtfRankingPage2::CCtfRankingPage2()
	: m_pCTFBaseRank			( NULL )
	, m_pCTFBaseSchool		( NULL )
	, m_pCTFBaseClass			( NULL )
	, m_pCTFBaseCharName		( NULL )
	, m_pCTFBaseKill			( NULL )
	, m_pCTFBaseDeath			( NULL )
	, m_pCTFBaseHeal			( NULL )
	, m_pCTFBaseResu			( NULL )
	, m_pCTFBaseContrib		( NULL )
	, m_pCTFBaseDamage		( NULL )
	, m_pScrollBar			( NULL )
	, m_pLineBoxMyRankHead	( NULL )
	, m_pLineBoxMyRankTail	( NULL )
	, m_nStart(0)
	, m_nTotal(0)
	, m_nRankType(3)
{
	for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ ) m_pRank[i] = NULL;
}

CCtfRankingPage2::~CCtfRankingPage2()
{
}

void CCtfRankingPage2::CreateSubControl()
{				

	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_SHADOW_FLAG );

	CString strSlotKeyword[nMAX_ONE_VIEW_SLOT] =
	{
		"CTF_RESULT_SLOT_0",
		"CTF_RESULT_SLOT_1",
		"CTF_RESULT_SLOT_2",
		"CTF_RESULT_SLOT_3",
		"CTF_RESULT_SLOT_4",
		"CTF_RESULT_SLOT_5",
		"CTF_RESULT_SLOT_6",
		"CTF_RESULT_SLOT_7",
		"CTF_RESULT_SLOT_8",
		"CTF_RESULT_SLOT_9"
	};

	m_pLineBoxMyRankHead = new CBasicLineBoxEx;
	m_pLineBoxMyRankHead->CreateSub ( this, "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE_BACK", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxMyRankHead->CreateBaseBoxSkill ( "CTF_RESULT_MYRANK_LINE_HEAD" );
	m_pLineBoxMyRankHead->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxMyRankHead );

	m_pLineBoxMyRankTail = new CBasicLineBoxEx;
	m_pLineBoxMyRankTail->CreateSub ( this, "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE_BACK", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxMyRankTail->CreateBaseBoxSkill ( "CTF_RESULT_MYRANK_LINE_TAIL" );
	m_pLineBoxMyRankTail->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxMyRankTail );

	m_pCTFBaseRank = new CBasicTextBoxEx;
	m_pCTFBaseRank->CreateSub ( this, "CTF_RESULT_TEXT_BASE_RANK" );
	m_pCTFBaseRank->SetFont ( pFont );
	m_pCTFBaseRank->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseRank );	

	m_pCTFBaseSchool = new CBasicTextBoxEx;
	m_pCTFBaseSchool->CreateSub ( this, "CTF_RESULT_TEXT_BASE_SCHOOL" );
	m_pCTFBaseSchool->SetFont ( pFont );
	m_pCTFBaseSchool->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseSchool );	

	m_pCTFBaseClass = new CBasicTextBoxEx;
	m_pCTFBaseClass->CreateSub ( this, "CTF_RESULT_TEXT_BASE_CLASS" );
	m_pCTFBaseClass->SetFont ( pFont );
	m_pCTFBaseClass->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseClass );	

	m_pCTFBaseCharName = new CBasicTextBoxEx;
	m_pCTFBaseCharName->CreateSub ( this, "CTF_RESULT_TEXT_BASE_NAME" );
	m_pCTFBaseCharName->SetFont ( pFont );
	m_pCTFBaseCharName->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseCharName );	

	m_pCTFBaseDamage = new CBasicTextBoxEx;
	m_pCTFBaseDamage->CreateSub ( this, "CTF_RESULT_TEXT_BASE_DAMAGE" );
	m_pCTFBaseDamage->SetFont ( pFont );
	m_pCTFBaseDamage->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseDamage );	

	m_pCTFBaseHeal = new CBasicTextBoxEx;
	m_pCTFBaseHeal->CreateSub ( this, "CTF_RESULT_TEXT_BASE_HEAL" );
	m_pCTFBaseHeal->SetFont ( pFont );
	m_pCTFBaseHeal->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseHeal );	

	m_pCTFBaseKill = new CBasicTextBoxEx;
	m_pCTFBaseKill->CreateSub ( this, "CTF_RESULT_TEXT_BASE_KILL" );
	m_pCTFBaseKill->SetFont ( pFont );
	m_pCTFBaseKill->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseKill );	

	m_pCTFBaseDeath = new CBasicTextBoxEx;
	m_pCTFBaseDeath->CreateSub ( this, "CTF_RESULT_TEXT_BASE_DEATH" );
	m_pCTFBaseDeath->SetFont ( pFont );
	m_pCTFBaseDeath->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseDeath );	

	m_pCTFBaseResu = new CBasicTextBoxEx;
	m_pCTFBaseResu->CreateSub ( this, "CTF_RESULT_TEXT_BASE_REBIRTH" );
	m_pCTFBaseResu->SetFont ( pFont );
	m_pCTFBaseResu->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseResu );	

	m_pCTFBaseContrib = new CBasicTextBoxEx;
	m_pCTFBaseContrib->CreateSub ( this, "CTF_RESULT_TEXT_BASE_CONTRIBUTION" );
	m_pCTFBaseContrib->SetFont ( pFont );
	m_pCTFBaseContrib->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pCTFBaseContrib );	

	for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ )
	{
		m_pRank[i] = new CCtfRankingSlot;
		m_pRank[i]->CreateSub ( this, strSlotKeyword[i].GetString() );
		m_pRank[i]->CreateSubControl ( NS_UITEXTCOLOR::WHITE );
		RegisterControl ( m_pRank[i] );
		m_pRank[i]->SetVisibleSingle( FALSE );
	}
	
	CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
	pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
	pScrollBar->CreateBaseScrollBar ( "CTF_RESULT_RANK_SCROLLBAR" );
	pScrollBar->GetThumbFrame()->SetState ( m_nTotal, nMAX_ONE_VIEW_SLOT );
	RegisterControl ( pScrollBar );
	m_pScrollBar = pScrollBar;

	m_pCTFBaseRank->ClearText();
	m_pCTFBaseSchool->ClearText();
	m_pCTFBaseClass->ClearText();
	m_pCTFBaseCharName->ClearText();
	m_pCTFBaseDamage->ClearText();
	m_pCTFBaseHeal->ClearText();
	m_pCTFBaseKill->ClearText();
	m_pCTFBaseDeath->ClearText();
	m_pCTFBaseResu->ClearText();
	m_pCTFBaseContrib->ClearText();

	m_pCTFBaseRank->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 0 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseSchool->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 1 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseClass->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 2 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseCharName->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 3 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseDamage->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 4 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseHeal->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 5 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseKill->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 6 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseDeath->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 7 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseResu->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 8 ), NS_UITEXTCOLOR::WHITE);
	m_pCTFBaseContrib->AddText( "K+R:D"/*ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 9 )*/, NS_UITEXTCOLOR::WHITE);	
}

void CCtfRankingPage2::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_nTotal = 0;
	if ( m_nRankType == 3 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankAll.size();
	else if ( m_nRankType == 2 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankPHX.size();
	else if ( m_nRankType == 1 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankMP.size();
	else if ( m_nRankType == 0 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankSG.size();

	if ( m_pScrollBar )
	{
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal();

			if( nTotal != m_nTotal )
				m_pScrollBar->GetThumbFrame()->SetState ( m_nTotal, nMAX_ONE_VIEW_SLOT );	
		}
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal ();
			if ( nTotal <= nMAX_ONE_VIEW_SLOT ) return ;
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

void CCtfRankingPage2::RefreshRankSlot()
{
	m_nTotal = 0;
	if ( m_nRankType == 3 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankAll.size();
	else if ( m_nRankType == 2 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankPHX.size();
	else if ( m_nRankType == 1 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankMP.size();
	else if ( m_nRankType == 0 )
		m_nTotal= (int)GLGaeaClient::GetInstance().m_vecCtfRankSG.size();

	RenderView();
}

void CCtfRankingPage2::RenderView()
{
	//FIX Rankings on all tabs by AnFire16
	for ( int i=0; i < nMAX_ONE_VIEW_SLOT; ++ i )
	{
		if ( m_pRank[i] )
			m_pRank[i]->SetVisibleSingle( FALSE );
	}

	TWP_RANK_VEC vecCtfRank;
	TWP_RANK_VEC vecCtfRankSG;
	TWP_RANK_VEC vecCtfRankMP;
	TWP_RANK_VEC vecCtfRankPHX;
	if ( m_nRankType == 3 )
		vecCtfRank = GLGaeaClient::GetInstance().m_vecCtfRankAll;
	else if ( m_nRankType == 2 )
		vecCtfRankPHX = GLGaeaClient::GetInstance().m_vecCtfRankPHX;
	else if ( m_nRankType == 1 )
		vecCtfRankMP = GLGaeaClient::GetInstance().m_vecCtfRankMP;
	else if ( m_nRankType == 0 )
		vecCtfRankSG = GLGaeaClient::GetInstance().m_vecCtfRankSG;

	int nEnd = m_nStart + nMAX_ONE_VIEW_SLOT;
	int nSlot = 0;
	int nSlotSG = 0;
	int nSlotMP = 0;
	int nSlotPHX = 0;

	for ( int i = m_nStart; i < nEnd; ++ i )
	{
		if ( i >= vecCtfRank.size() )	continue;

		if ( m_pRank[nSlot] )
		{
			m_pRank[nSlot]->SetVisibleSingle( TRUE );
			m_pRank[nSlot]->Init(vecCtfRank[i].wCharRanking,
				vecCtfRank[i].wSchool,
				vecCtfRank[i].dwClass,
				vecCtfRank[i].szCharName,
				vecCtfRank[i].dwDamageNum,
				vecCtfRank[i].dwHealNum,
				vecCtfRank[i].wKillNum,
				vecCtfRank[i].wDeathNum,
				vecCtfRank[i].wResuNum,
				false);
			nSlot ++ ;
		}
	}

	//SG Rankings
	for ( int i = m_nStart; i < nEnd; ++ i )
	{
		if ( i >= vecCtfRankSG.size() )	continue;

		if ( m_pRank[nSlotSG] )
		{
			m_pRank[nSlotSG]->SetVisibleSingle( TRUE );
			m_pRank[nSlotSG]->Init(i+1,
				vecCtfRankSG[i].wSchool,
				vecCtfRankSG[i].dwClass,
				vecCtfRankSG[i].szCharName,
				vecCtfRankSG[i].dwDamageNum,
				vecCtfRankSG[i].dwHealNum,
				vecCtfRankSG[i].wKillNum,
				vecCtfRankSG[i].wDeathNum,
				vecCtfRankSG[i].wResuNum,
				false);
			nSlotSG ++ ;
		}
	}

	//MP Rankings
	for ( int i = m_nStart; i < nEnd; ++ i )
	{
		if ( i >= vecCtfRankMP.size() )	continue;

		if ( m_pRank[nSlotMP] )
		{
			m_pRank[nSlotMP]->SetVisibleSingle( TRUE );
			m_pRank[nSlotMP]->Init(i+1,
				vecCtfRankMP[i].wSchool,
				vecCtfRankMP[i].dwClass,
				vecCtfRankMP[i].szCharName,
				vecCtfRankMP[i].dwDamageNum,
				vecCtfRankMP[i].dwHealNum,
				vecCtfRankMP[i].wKillNum,
				vecCtfRankMP[i].wDeathNum,
				vecCtfRankMP[i].wResuNum,
				false);
			nSlotMP ++ ;
		}
	}

	//Phoenix Rankings
	for ( int i = m_nStart; i < nEnd; ++ i )
	{
		if ( i >= vecCtfRankPHX.size() )	continue;

		if ( m_pRank[nSlotPHX] )
		{
			m_pRank[nSlotPHX]->SetVisibleSingle( TRUE );
			m_pRank[nSlotPHX]->Init(i+1,
				vecCtfRankPHX[i].wSchool,
				vecCtfRankPHX[i].dwClass,
				vecCtfRankPHX[i].szCharName,
				vecCtfRankPHX[i].dwDamageNum,
				vecCtfRankPHX[i].dwHealNum,
				vecCtfRankPHX[i].wKillNum,
				vecCtfRankPHX[i].wDeathNum,
				vecCtfRankPHX[i].wResuNum,
				false);
			nSlotPHX ++ ;
		}
	}
}