#include "StdAfx.h"
#include "CCtfRankingSelf.h"
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



CCtfRankingSelf::CCtfRankingSelf()
	: m_pRank(NULL)
{
}

CCtfRankingSelf::~CCtfRankingSelf()
{
}

void CCtfRankingSelf::CreateSubControl()
{				
	m_pRank = new CCtfRankingSlot;
	m_pRank->CreateSub ( this, "CTF_RESULT_SLOT_0" );
	m_pRank->CreateSubControl ( NS_UITEXTCOLOR::WHITE );
	RegisterControl ( m_pRank );
	m_pRank->SetVisibleSingle( FALSE );
}

void CCtfRankingSelf::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCtfRankingSelf::RefreshRankSlot()
{
	if ( m_pRank )
	{
		m_pRank->SetVisibleSingle( TRUE );
		const STWP_RANK_EX& sMyRank = GLGaeaClient::GetInstance().m_sMyCtfRank;
		m_pRank->Init(sMyRank.wCharRanking,
				sMyRank.wSchool,
				sMyRank.dwClass,
				sMyRank.szCharName,
				sMyRank.dwDamageNum,
				sMyRank.dwHealNum,
				sMyRank.wKillNum,
				sMyRank.wDeathNum,
				sMyRank.wResuNum,
				true );
	}
}

