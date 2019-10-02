//#include "StdAfx.h"
//#include "CCtfRankingPage.h"
//#include "CCtfRankingSlot.h"
//#include "BasicTextBoxEx.h"
//#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
//#include "d3dfont.h"
//#include "GLGaeaClient.h"
//#include "UITextControl.h"
//#include "GameTextControl.h"
//#include "BasicScrollBarEx.h"
//#include "BasicTextButton.h" 
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
//
//const int CCtfRankingPage::nSTARTLINE = 0;
//const int CCtfRankingPage::nOUTOFRANGE = -1;
//
//CCtfRankingPage::CCtfRankingPage()
//	:	m_pCTFBaseRank			( NULL )
//	,	m_pCTFBaseSchool		( NULL )
//	,	m_pCTFBaseClass			( NULL )
//	,	m_pCTFBaseCharName		( NULL )
//	,	m_pCTFBaseKill			( NULL )
//	,	m_pCTFBaseDeath			( NULL )
//	,	m_pCTFBaseHeal			( NULL )
//	,	m_pCTFBaseResu			( NULL )
//	,	m_pCTFBaseContrib		( NULL )
//	,	m_pCTFBaseDamage		( NULL )
//	,	m_pScrollBar			( NULL )
//	,	m_pLineBoxMyRankHead	( NULL )
//	,	m_pLineBoxMyRankTail	( NULL )
//{
//	memset ( m_pRankSlot, 0, sizeof ( CCtfRankingSlot* ) * 99 );
//	memset ( m_pRankSlotArrayDummy, 0, sizeof ( CUIControl* ) * nMAX_ONE_VIEW_SLOT );
//}
//
//CCtfRankingPage::~CCtfRankingPage()
//{
//}
//
//void CCtfRankingPage::CreateSubControl ( int nRankCount, bool bMyRank )
//{				
//	//if ( nRankCount < 1 ) return ;
//
//	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_SHADOW_FLAG );
//
//	CString strSlotKeyword[nMAX_ONE_VIEW_SLOT] =
//	{
//		"CTF_RESULT_SLOT_0",
//		"CTF_RESULT_SLOT_1",
//		"CTF_RESULT_SLOT_2",
//		"CTF_RESULT_SLOT_3",
//		"CTF_RESULT_SLOT_4",
//		"CTF_RESULT_SLOT_5",
//		"CTF_RESULT_SLOT_6",
//		"CTF_RESULT_SLOT_7",
//		"CTF_RESULT_SLOT_8",
//		"CTF_RESULT_SLOT_9"
//	};
//
//	m_pLineBoxMyRankHead = new CBasicLineBoxEx;
//	m_pLineBoxMyRankHead->CreateSub ( this, "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE_BACK", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
//	m_pLineBoxMyRankHead->CreateBaseBoxSkill ( "CTF_RESULT_MYRANK_LINE_HEAD" );
//	m_pLineBoxMyRankHead->SetVisibleSingle ( TRUE );
//	RegisterControl ( m_pLineBoxMyRankHead );
//
//	m_pLineBoxMyRankTail = new CBasicLineBoxEx;
//	m_pLineBoxMyRankTail->CreateSub ( this, "BASIC_LINE_BOX_EX_BODY_DIALOGUE_WHITE_BACK", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
//	m_pLineBoxMyRankTail->CreateBaseBoxSkill ( "CTF_RESULT_MYRANK_LINE_TAIL" );
//	m_pLineBoxMyRankTail->SetVisibleSingle ( TRUE );
//	RegisterControl ( m_pLineBoxMyRankTail );
//
//	m_pCTFBaseRank = new CBasicTextBoxEx;
//	m_pCTFBaseRank->CreateSub ( this, "CTF_RESULT_TEXT_BASE_RANK" );
//	m_pCTFBaseRank->SetFont ( pFont );
//	m_pCTFBaseRank->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseRank );	
//
//	m_pCTFBaseSchool = new CBasicTextBoxEx;
//	m_pCTFBaseSchool->CreateSub ( this, "CTF_RESULT_TEXT_BASE_SCHOOL" );
//	m_pCTFBaseSchool->SetFont ( pFont );
//	m_pCTFBaseSchool->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseSchool );	
//
//	m_pCTFBaseClass = new CBasicTextBoxEx;
//	m_pCTFBaseClass->CreateSub ( this, "CTF_RESULT_TEXT_BASE_CLASS" );
//	m_pCTFBaseClass->SetFont ( pFont );
//	m_pCTFBaseClass->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseClass );	
//
//	m_pCTFBaseCharName = new CBasicTextBoxEx;
//	m_pCTFBaseCharName->CreateSub ( this, "CTF_RESULT_TEXT_BASE_NAME" );
//	m_pCTFBaseCharName->SetFont ( pFont );
//	m_pCTFBaseCharName->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseCharName );	
//
//	m_pCTFBaseDamage = new CBasicTextBoxEx;
//	m_pCTFBaseDamage->CreateSub ( this, "CTF_RESULT_TEXT_BASE_DAMAGE" );
//	m_pCTFBaseDamage->SetFont ( pFont );
//	m_pCTFBaseDamage->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseDamage );	
//
//	m_pCTFBaseHeal = new CBasicTextBoxEx;
//	m_pCTFBaseHeal->CreateSub ( this, "CTF_RESULT_TEXT_BASE_HEAL" );
//	m_pCTFBaseHeal->SetFont ( pFont );
//	m_pCTFBaseHeal->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseHeal );	
//
//	m_pCTFBaseKill = new CBasicTextBoxEx;
//	m_pCTFBaseKill->CreateSub ( this, "CTF_RESULT_TEXT_BASE_KILL" );
//	m_pCTFBaseKill->SetFont ( pFont );
//	m_pCTFBaseKill->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseKill );	
//
//	m_pCTFBaseDeath = new CBasicTextBoxEx;
//	m_pCTFBaseDeath->CreateSub ( this, "CTF_RESULT_TEXT_BASE_DEATH" );
//	m_pCTFBaseDeath->SetFont ( pFont );
//	m_pCTFBaseDeath->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseDeath );	
//
//	m_pCTFBaseResu = new CBasicTextBoxEx;
//	m_pCTFBaseResu->CreateSub ( this, "CTF_RESULT_TEXT_BASE_REBIRTH" );
//	m_pCTFBaseResu->SetFont ( pFont );
//	m_pCTFBaseResu->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseResu );	
//
//	m_pCTFBaseContrib = new CBasicTextBoxEx;
//	m_pCTFBaseContrib->CreateSub ( this, "CTF_RESULT_TEXT_BASE_CONTRIBUTION" );
//	m_pCTFBaseContrib->SetFont ( pFont );
//	m_pCTFBaseContrib->SetTextAlign ( TEXT_ALIGN_CENTER_X );
//	RegisterControl ( m_pCTFBaseContrib );	
//
//	for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ )
//	{
//		m_pRankSlotArrayDummy[i] = CreateControl ( strSlotKeyword[i].GetString () );
//	}
//	if(bMyRank){
//		for ( int i = 0; i < 99; i++ )
//		{
//			m_pRankSlot[i] = CreateRankSlot ( strSlotKeyword[0], CTF_RESULT_SLOT_0 + i, i+1 ,NS_UITEXTCOLOR::WHITE);
//			
//		}
//	}
//	else m_pRankSlot[0] = CreateRankSlot ( "CTF_RESULT_MYRANK_SLOT", CTF_RESULT_MYSLOT, 100 ,NS_UITEXTCOLOR::GREENYELLOW);
//	
//
//	//m_pMyRankSlot = CreateRankSlot("CTF_RESULT_MYRANK_SLOT", CTF_RESULT_MYSLOT, 1,NS_UITEXTCOLOR::BRIGHTGREEN );
//	//m_pMyRankSlot->SetVisibleSingle(TRUE);
//
//	if ( nRankCount < nMAX_ONE_VIEW_SLOT )
//	{
//		nRankCount = nMAX_ONE_VIEW_SLOT;
//	}
//	m_nMaxRankCnt = nRankCount;
//
//	m_vecViewRank.clear();
//
//	CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
//	pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
//	pScrollBar->CreateBaseScrollBar ( "CTF_RESULT_RANK_SCROLLBAR" );
//	pScrollBar->GetThumbFrame()->SetState ( nRankCount, nMAX_ONE_VIEW_SLOT );
//	RegisterControl ( pScrollBar );
//	m_pScrollBar = pScrollBar;
//
//	if(!bMyRank)
//	{
//		m_pCTFBaseRank->SetVisibleSingle(FALSE);
//		m_pCTFBaseSchool->SetVisibleSingle(FALSE);
//		m_pCTFBaseClass->SetVisibleSingle(FALSE);
//		m_pCTFBaseCharName->SetVisibleSingle(FALSE);
//		m_pCTFBaseDamage->SetVisibleSingle(FALSE);
//		m_pCTFBaseHeal->SetVisibleSingle(FALSE);
//		m_pCTFBaseKill->SetVisibleSingle(FALSE);
//		m_pCTFBaseDeath->SetVisibleSingle(FALSE);
//		m_pCTFBaseResu->SetVisibleSingle(FALSE);
//		m_pCTFBaseContrib->SetVisibleSingle(FALSE);
//		m_pLineBoxMyRankHead->SetVisibleSingle(FALSE);
//		m_pLineBoxMyRankTail->SetVisibleSingle(FALSE);
//		m_pScrollBar->SetVisibleSingle(FALSE);
//	}
//}
//
//CUIControl*	CCtfRankingPage::CreateControl ( const char* szControl )
//{
//	CUIControl* pControl = new CUIControl;
//	pControl->CreateSub ( this, szControl );
//	RegisterControl ( pControl );
//	return pControl;
//}
//
//CCtfRankingSlot* CCtfRankingPage::CreateRankSlot ( CString strKeyword, UIGUID ControlID, int index, D3DCOLOR dwColor )
//{
//	CCtfRankingSlot* pRankSlot = new CCtfRankingSlot;
//	pRankSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
//	pRankSlot->CreateSubControl ( dwColor );
//	RegisterControl ( pRankSlot );
//	return pRankSlot;
//}
//
//void CCtfRankingPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
//{
//	if ( !IsVisible () ) return ;
//
//	m_nSlotIndex = nOUTOFRANGE;
//	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
//
//	if ( m_pScrollBar )
//	{
//		{
//			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
//			int nViewPerPage = pThumbFrame->GetViewPerPage ();
//			int nBeforeRankCnt = m_vecViewRank.size();
//
//			m_vecViewRank.clear();
//			for ( int i = 0; i < m_nMaxRankCnt; i++ )
//			{
//				m_vecViewRank.push_back( i );
//			}
//
//			if( nBeforeRankCnt != m_vecViewRank.size() )
//			{
//				m_pScrollBar->GetThumbFrame()->SetState ( m_vecViewRank.size(), nMAX_ONE_VIEW_SLOT );
//				ResetAllRankSlotRender( m_nMaxRankCnt );
//				SetRankSlotRender ( 0, 0 + nViewPerPage );			
//			}
//			
//		}
//		{
//			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
//			int nTotal = pThumbFrame->GetTotal ();
//			if ( nTotal <= nMAX_ONE_VIEW_SLOT ) return ;
//
//			const int nViewPerPage = pThumbFrame->GetViewPerPage ();
//
//			if ( nViewPerPage < nTotal )
//			{
//				int nCurPos = nSTARTLINE;
//				const int nMovableLine = nTotal - nViewPerPage;
//				float fPercent = pThumbFrame->GetPercent ();
//
//				nCurPos = (int)floor(fPercent * nMovableLine);
//				if ( nCurPos < nSTARTLINE ) nCurPos = nSTARTLINE;
//
//				if ( m_nCurPos == nCurPos ) return;
//
//				m_nCurPos = nCurPos;
//
//				ResetAllRankSlotRender ( nTotal );
//				SetRankSlotRender ( nCurPos, nCurPos + nViewPerPage );
//			}
//		}
//	}
//}
//
//void CCtfRankingPage::ResetAllRankSlotRender ( int nTotal )
//{
//	if ( nTotal < 0 ) return ;
//
//	for ( int i = 0; i < 99; i++ )
//	{
//		CCtfRankingSlot* pRankSlot = m_pRankSlot[i];
//		if ( pRankSlot )
//		{
//			pRankSlot->SetVisibleSingle ( FALSE );
//		}
//	}
//}
//
//void CCtfRankingPage::SetRankSlotRender ( int nStartIndex, int nTotal )
//{
//	if ( nTotal < 0 ) return ;
//
//	const UIRECT& rcParentPos = GetGlobalPos ();
//
//	int iViewIndex = 0; 
//	int iSlotNum   = 0;	
//	for ( int i = nStartIndex; i < m_vecViewRank.size(); i++ )
//	{
//		if( i >= m_nMaxRankCnt ) break;
//		if( i >= nTotal ) break;
//
//		iSlotNum = m_vecViewRank[i];
//
//		CCtfRankingSlot* pRankSlot = m_pRankSlot[iSlotNum];
//		if ( pRankSlot )
//		{
//						
//			int nAbsoluteIndex = iViewIndex;
//			CUIControl* pDummyControl = m_pRankSlotArrayDummy[nAbsoluteIndex];
//
//			const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
//			const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();
//
//			pRankSlot->SetLocalPos ( rcSlotLocalPos );			
//			pRankSlot->SetGlobalPos ( rcSlotPos );
//
//			pRankSlot->SetVisibleSingle ( TRUE );
//
//			iViewIndex++;
//		}
//	}
//
//	if( m_vecViewRank.size() < nTotal )
//	{
//		int iMaxLackTotal = nTotal - m_vecViewRank.size();		
//		for( i = 0; i < iMaxLackTotal; i++ )
//		{
//			iSlotNum++;
//			CCtfRankingSlot* pRankSlot = m_pRankSlot[iSlotNum];
//			if ( pRankSlot )
//			{
//
//				int nAbsoluteIndex = iViewIndex;
//				CUIControl* pDummyControl = m_pRankSlotArrayDummy[nAbsoluteIndex];
//
//				const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
//				const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();
//
//				pRankSlot->SetLocalPos ( rcSlotLocalPos );			
//				pRankSlot->SetGlobalPos ( rcSlotPos );
//
//				pRankSlot->SetVisibleSingle ( TRUE );
//
//				iViewIndex++;
//			}
//		}
//	}
//
//
//	
//	for( i = nTotal; i < m_vecViewRank.size(); i++ )
//	{
//		iSlotNum = m_vecViewRank[i];
//
//		if( m_pRankSlot[iSlotNum] ) m_pRankSlot[iSlotNum]->SetVisibleSingle( FALSE );
//	}
//}
//
//void CCtfRankingPage::Init()
//{
//	m_pCTFBaseRank->ClearText();
//	m_pCTFBaseSchool->ClearText();
//	m_pCTFBaseClass->ClearText();
//	m_pCTFBaseCharName->ClearText();
//	m_pCTFBaseDamage->ClearText();
//	m_pCTFBaseHeal->ClearText();
//	m_pCTFBaseKill->ClearText();
//	m_pCTFBaseDeath->ClearText();
//	m_pCTFBaseResu->ClearText();
//	m_pCTFBaseContrib->ClearText();
//
//	m_pCTFBaseRank->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 0 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseSchool->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 1 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseClass->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 2 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseCharName->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 3 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseDamage->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 4 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseHeal->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 5 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseKill->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 6 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseDeath->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 7 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseResu->AddText( ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 8 ), NS_UITEXTCOLOR::WHITE);
//	m_pCTFBaseContrib->AddText( "K+R:D"/*ID2GAMEWORD( "CTF_RESULT_TEXT_BASE", 9 )*/, NS_UITEXTCOLOR::WHITE);	
//}
//
//void CCtfRankingPage::RefreshRankSlot( bool bMyRank, int wSchool )
//{
//	if( !bMyRank )
//	{
//		TWP_RANK_VEC& vecCtfRank = GLGaeaClient::GetInstance().m_vecCtfRank;
//		int nRankNum = GLGaeaClient::GetInstance().m_vecCtfRank.size();
//		SetRankCnt( vecCtfRank.size() );
//		int slotCnt = 0;
//		for(int i=0;i<nRankNum;i++)
//		{
//			if( wSchool == vecCtfRank[i].wSchool )
//			{
//				if (m_pRankSlot[slotCnt] )
//				{
//					m_pRankSlot[slotCnt]->Init(vecCtfRank[i].wCharRanking,
//										vecCtfRank[i].wSchool,
//										vecCtfRank[i].dwClass,
//										vecCtfRank[i].szCharName,
//										vecCtfRank[i].dwDamageNum,
//										vecCtfRank[i].dwHealNum,
//										vecCtfRank[i].wKillNum,
//										vecCtfRank[i].wDeathNum,
//										vecCtfRank[i].wResuNum,
//										false);
//					slotCnt++;
//					SetRankCnt( slotCnt );
//				}
//			}
//			else if( wSchool == 3)
//			{
//				if (m_pRankSlot[i] )
//				{
//				m_pRankSlot[i]->Init(vecCtfRank[i].wCharRanking,
//		                				vecCtfRank[i].wSchool,
//										vecCtfRank[i].dwClass,
//										vecCtfRank[i].szCharName,
//										vecCtfRank[i].dwDamageNum,
//										vecCtfRank[i].dwHealNum,
//										vecCtfRank[i].wKillNum,
//										vecCtfRank[i].wDeathNum,
//										vecCtfRank[i].wResuNum,
//										false);
//				}
//			}
//		}
//	}
//	else
//	{
//		const STWP_RANK_EX& sMyRank = GLGaeaClient::GetInstance().m_sMyCtfRank;
//		m_pRankSlot[0]->Init(sMyRank.wCharRanking,
//		sMyRank.wSchool,
//		sMyRank.dwClass,
//		sMyRank.szCharName,
//		sMyRank.dwDamageNum,
//		sMyRank.dwHealNum,
//		sMyRank.wKillNum,
//		sMyRank.wDeathNum,
//		sMyRank.wResuNum,
//		true);
//	}
//}