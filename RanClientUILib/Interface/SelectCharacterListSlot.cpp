#include "StdAfx.h"
#include "SelectCharacterListSlot.h"
#include "SelectCharacterListImage.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "DxGlobalStage.h"
#include "GLGaeaClient.h"
#include "BasicScrollBarEx.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CSelectCharacterListSlot::nSTARTLINE = 0;
const int CSelectCharacterListSlot::nOUTOFRANGE = -1;

CSelectCharacterListSlot::CSelectCharacterListSlot ()
	: m_pScrollBar ( NULL )
	, m_nCurPos ( -1 )
{
	memset ( m_pCharImageArray, 0, sizeof ( CSelectCharacterListImage* ) * GLCONST::MAX_SERVERCHAR );
	memset ( m_pCharImageArrayDummy, 0, sizeof ( CUIControl* ) * nMAX_ONE_VIEW_SLOT );
}

CSelectCharacterListSlot::~CSelectCharacterListSlot ()
{
}

CUIControl*	CSelectCharacterListSlot::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

void CSelectCharacterListSlot::CreateSubControl ( SCHARINFO_LOBBY sCharInfoArray[GLCONST::MAX_SERVERCHAR], int nCharCount )
{
	if ( nCharCount < 1 ) return ;

	CString strImageKeyword[nMAX_ONE_VIEW_SLOT] =
	{
		"SELECT_CHAR_WINDOW_CHAR_LIST_ITEM_0",
		"SELECT_CHAR_WINDOW_CHAR_LIST_ITEM_1",
		"SELECT_CHAR_WINDOW_CHAR_LIST_ITEM_2",
		"SELECT_CHAR_WINDOW_CHAR_LIST_ITEM_3",
		"SELECT_CHAR_WINDOW_CHAR_LIST_ITEM_4",
	};

	{
		for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ )
		{
			m_pCharImageArrayDummy[i] = CreateControl ( strImageKeyword[i].GetString() );
		}
	}

	{
		if ( nCharCount < nMAX_ONE_VIEW_SLOT )
		{
			nCharCount = nMAX_ONE_VIEW_SLOT;
		}
		m_vecViewChar.clear();

		for ( int i = 0; i < GLCONST::MAX_SERVERCHAR; i++ )
		{
			m_pCharImageArray[i] = CreateCharImage ( strImageKeyword[0], SELECT_CHAR_ITEM0 + 1, SCHARINFO_LOBBY sCharInfoArray[i] );
		}
		m_nMaxCharCnt = nCharCount;
	}

	{
		CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
		pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
		pScrollBar->CreateBaseScrollBar ( "SELECT_CHAR_WINDOW_SCROLLBAR" );
		pScrollBar->GetThumbFrame()->SetState ( nCharCount, nMAX_ONE_VIEW_SLOT );
		RegisterControl ( pScrollBar );
		m_pScrollBar = pScrollBar;
	}

	SetCharSlotRender ( nSTARTLINE, nMAX_ONE_VIEW_SLOT );

}

CSelectCharacterListImage*	CSelectCharacterListSlot::CreateCharImage ( CString strKeyword, UIGUID ControlID, SCHARINFO_LOBBY sCharInfoID )
{
	CSelectCharacterListImage* pCharImage = new CSelectCharacterListImage;
	pCharImage->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pCharImage->CreateSubControl ( sCharInfoID );
	RegisterControl ( pCharImage );
	return pSkillSlot;
}

void CSelectCharacterListSlot::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return;

	m_nImageIndex = nOUTOFRANGE;
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_pScrollBar )
	{
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nViewPerPage = pThumbFrame->GetViewPerPage ();
			int nBeforeCharCnt = m_vecViewChar.size();

			m_vecViewChar.clear();
			for ( int i = 0; i < m_nMaxCharCnt; i++ )
			{
				SCHARINFO_LOBBY* sCharID = m_pCharImageArray[i]->DxGlobalStage::GetInstance().GetLobyStage->GetSelectCharInfo();
	
				m_vecViewSkill.push_back( i );
			
			}
			if( nBeforeSkillCnt != m_vecViewSkill.size() )
			{
				m_pScrollBar->GetThumbFrame()->SetState ( m_vecViewChar.size(), nMAX_ONE_VIEW_SLOT );
				ResetAllCharImageRender( m_nMaxCharCnt );
				SetCharSlotRender ( 0, 0 + nViewPerPage );			
			}
			
		}
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nTotal = pThumbFrame->GetTotal ();
			if ( nTotal <= nMAX_ONE_VIEW_SLOT ) return ;

			const int nViewPerPage = pThumbFrame->GetViewPerPage ();

			if ( nViewPerPage < nTotal )
			{
				int nCurPos = nSTARTLINE;
				const int nMovableLine = nTotal - nViewPerPage;
				float fPercent = pThumbFrame->GetPercent ();

				nCurPos = (int)floor(fPercent * nMovableLine);
				if ( nCurPos < nSTARTLINE ) nCurPos = nSTARTLINE;

				if ( m_nCurPos == nCurPos ) return;

				m_nCurPos = nCurPos;

				ResetAllCharImageRender ( nTotal );
				SetCharSlotRender ( nCurPos, nCurPos + nViewPerPage );
			}
		}
	}
}

void CSelectCharacterListSlot::ResetAllCharImageRender ( int nTotal )
{
	if ( nTotal < 0 ) return ;

	for ( int i = 0; i < GLCONST::MAX_SERVERCHAR; i++ )
	{
		CSelectCharacterListImage* pCharSel = m_pCharImageArray[i];
		if ( pCharSel )
		{
			pCharSel->SetVisibleSingle ( FALSE );
		}
	}
}

void CSelectCharacterListSlot::SetCharSlotRender ( int nStartIndex, int nTotal )
{
	if ( nTotal < 0 ) return ;

	const UIRECT& rcParentPos = GetGlobalPos ();

	

	int iViewIndex = 0; // 보여질 위치
	int iSlotNum   = 0;	// 보여지는 SlotNum
	for ( int i = nStartIndex; i < m_vecViewChar.size(); i++ )
	{
		if( i >= m_nMaxCharCnt ) break;
		if( i >= nTotal ) break;

		iSlotNum = m_vecViewChar[i];

		CSelectCharacterListImage* pCharSel = m_pCharImageArray[iSlotNum];
		if ( pCharSel )
		{
						
			int nAbsoluteIndex = iViewIndex;
			CUIControl* pDummyControl = m_pCharImageArrayDummy[nAbsoluteIndex];

			const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
			const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();

			pCharSel->SetLocalPos ( rcSlotLocalPos );			
			pCharSel->SetGlobalPos ( rcSlotPos );

			pCharSel->SetVisibleSingle ( TRUE );

			iViewIndex++;
		}
	}

	if( m_vecViewChar.size() < nTotal )
	{
		int iMaxLackTotal = nTotal - m_vecViewChar.size();		
		for( i = 0; i < iMaxLackTotal; i++ )
		{
			iSlotNum++;
			CSelectCharacterListImage* pCharSel = m_pCharImageArray[iSlotNum];
			if ( pCharSel )
			{

				int nAbsoluteIndex = iViewIndex;
				CUIControl* pDummyControl = m_pCharImageArrayDummy[nAbsoluteIndex];

				const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
				const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();

				pCharSel->SetLocalPos ( rcSlotLocalPos );			
				pCharSel->SetGlobalPos ( rcSlotPos );

				pCharSel->SetVisibleSingle ( TRUE );

				iViewIndex++;
			}
		}
	}


	
	for( i = nTotal; i < m_vecViewChar.size(); i++ )
	{
		iSlotNum = m_vecViewChar[i];

		if( m_pCharImageArray[iSlotNum] ) m_pCharImageArray[iSlotNum]->SetVisibleSingle( FALSE );
	}
}

SCHARINFO_LOBBY  CSelectCharacterListSlot::GetCharID ( int nIndex )
{	
	return m_pCharImageArray[nIndex]->DxGlobalStage::GetInstance().GetLobyStage->GetSelectCharInfo();
}

void CSelectCharacterListSlot::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	if ( SELECT_CHAR_ITEM0 <= ControlID && ControlID <= SELECT_CHAR_ITEM5 )
	{
		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{
			m_nSlotIndex = ControlID - SELECT_CHAR_ITEM0;
		}
	}
}
