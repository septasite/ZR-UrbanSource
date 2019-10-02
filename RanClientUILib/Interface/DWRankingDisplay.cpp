#include "StdAfx.h"
#include "DWRankingDisplay.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "d3dfont.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDWRankingDisplay::CDWRankingDisplay()
	:	m_pDWRankingText ( NULL )
{
	for ( int i = 0; i < 3; i++ )
	{
		m_pSchool[i] = NULL;	
	}

	
}

CDWRankingDisplay::~CDWRankingDisplay()
{
}

void CDWRankingDisplay::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, _DEFAULT_FONT_SHADOW_FLAG );

	{//Add School
		CString strSchool[3] = 
		{
			"TDW_SLOT_SCHOOL0",
			"TDW_SLOT_SCHOOL1",
			"TDW_SLOT_SCHOOL2"
		};

		for ( int i = 0; i < 3; i++ )
		{
			m_pSchool[i] = CreateControl ( strSchool[i].GetString() );
		}
	}

	m_pDWRankingText = new CBasicTextBox;
	m_pDWRankingText->CreateSub ( this, "TDW_RANKING_TEXT" );
	m_pDWRankingText->SetFont ( pFont );
	m_pDWRankingText->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pDWRankingText );	
}

void CDWRankingDisplay::SetSchool ( int nSchoolType )
{
	//add class
	for ( int i = 0; i < 3; i++ )
	{
		m_pSchool[i]->SetVisibleSingle ( FALSE );
	}

	m_pSchool[nSchoolType]->SetVisibleSingle ( TRUE );
}

CUIControl*	CDWRankingDisplay::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}


void CDWRankingDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CDWRankingDisplay::RefreashDWRanking()
{
	if ( !m_pDWRankingText ) return;

	m_pDWRankingText->ClearText();

	const SDW_RANK_EX& sMyRank = GLGaeaClient::GetInstance().m_sMyDWRank;

	CString strMyRanking;
	strMyRanking.Format( "%s :%2d %s : %d %s : %d", ID2GAMEWORD( "TDW_RANKING_DISPLAY", 0 ), sMyRank.wPlayerRanking,
						ID2GAMEWORD( "TDW_RANKING_DISPLAY", 1),  sMyRank.wKillNum, 
						ID2GAMEWORD( "TDW_RANKING_DISPLAY", 2),  sMyRank.wDeathNum );

	m_pDWRankingText->AddText( strMyRanking, NS_UITEXTCOLOR::IDNAMECOLOR );

	int nRankNum = GLGaeaClient::GetInstance().m_vecDWRank.size();
	CString strRanking;
	DW_RANK_VEC& vecDWRank = GLGaeaClient::GetInstance().m_vecDWRank;

	for ( int i = 0; i < nRankNum; ++i )
	{
		strRanking.Format( "%2d %s (%d/%d)", vecDWRank[i].wPlayerRanking,
											 vecDWRank[i].szPlayerName,
											 vecDWRank[i].wKillNum, 
											 vecDWRank[i].wDeathNum );

		m_pDWRankingText->AddText( strRanking, NS_UITEXTCOLOR::WHITE );
	}
}