#include "StdAfx.h"
#include "GLGaeaClient.h"
#include "BasicLineBox.h"
#include "BasicLineBoxEx.h"
#include "SkillPage.h"
#include "BasicScrollBarEx.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "SkillSlot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int CSkillPage::nSTARTLINE = 0;
const int CSkillPage::nOUTOFRANGE = -1;

CSkillPage::CSkillPage () :
	m_pScrollBar ( NULL ),
	m_nCurPos ( -1 )
{
	memset ( m_pSkillSlotArray, 0, sizeof ( CSkillSlot* ) * GLSkillMan::MAX_CLASSSKILL );	
	memset ( m_pSkillSlotArrayDummy, 0, sizeof ( CUIControl* ) * nMAX_ONE_VIEW_SLOT );		
}

CSkillPage::~CSkillPage ()
{
}

CUIControl*	CSkillPage::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

void CSkillPage::CreateSubControl ( SNATIVEID sNativeIDArray[GLSkillMan::MAX_CLASSSKILL], int nSkillCount )
{	
	if ( nSkillCount < 1 ) return ;

	CString strSlotKeyword[nMAX_ONE_VIEW_SLOT] =
	{
		"KYNANG_SLOT_0",
		"KYNANG_SLOT_1",
		"KYNANG_SLOT_2",
		"KYNANG_SLOT_3",
		"KYNANG_SLOT_4",
		"KYNANG_SLOT_5",
		"KYNANG_SLOT_6",
		"KYNANG_SLOT_7",
		"KYNANG_SLOT_8",
		"KYNANG_SLOT_9",
		"KYNANG_SLOT_10",
		"KYNANG_SLOT_11",
		"KYNANG_SLOT_12",
		"KYNANG_SLOT_13",
		"KYNANG_SLOT_14",
		"KYNANG_SLOT_15",
		"KYNANG_SLOT_16",
		"KYNANG_SLOT_17"
	};
/*	{	// Ðen Xám Ðen Background
		CBasicLineBoxEx* pBasicLineBoxEx = new CBasicLineBoxEx;
		pBasicLineBoxEx->CreateSub ( this, "BASIC_LINE_BOX_EX_BODY_LOM", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBoxEx->CreateBaseBoxLomBox ( "RNSKILL_SKILL_SLOT_BACK" );
		RegisterControl ( pBasicLineBoxEx );
	}*/
	
/*	{
		CBasicLineBox* pLineBox = new CBasicLineBox;
		pLineBox->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pLineBox->CreateBaseBoxSkill ( "RNSKILL_SKILL_SLOT_BACK" );
		RegisterControl ( pLineBox );
	}*/

	{	//	?? ??
		for ( int i = 0; i < nMAX_ONE_VIEW_SLOT; i++ )
		{
			m_pSkillSlotArrayDummy[i] = CreateControl ( strSlotKeyword[i].GetString () );
		}
	}

	{	//	?? ???		
		if ( nSkillCount < nMAX_ONE_VIEW_SLOT )
		{
			nSkillCount = nMAX_ONE_VIEW_SLOT;
		}

		m_vecViewSkill.clear();		

		for ( int i = 0; i < GLSkillMan::MAX_CLASSSKILL; i++ )
		{
			m_pSkillSlotArray[i] = CreateSkillSlot ( strSlotKeyword[0], KYNANG_SLOT_0 + i, sNativeIDArray[i] );
		}
		m_nMaxSkillCnt = nSkillCount;
	}

	{
		CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
		pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE );
		pScrollBar->CreateBaseScrollBar ( "KYNANG_THANH_CUON" );
		pScrollBar->GetThumbFrame()->SetState ( nSkillCount, nMAX_ONE_VIEW_SLOT );
		RegisterControl ( pScrollBar );
		m_pScrollBar = pScrollBar;
	}

	SetSkillSlotRender ( nSTARTLINE, nMAX_ONE_VIEW_SLOT );
}

CSkillSlot*	CSkillPage::CreateSkillSlot ( CString strKeyword, UIGUID ControlID, SNATIVEID sNativeID )
{
	CSkillSlot* pSkillSlot = new CSkillSlot;
	pSkillSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pSkillSlot->CreateSubControl ( sNativeID );
	RegisterControl ( pSkillSlot );
	return pSkillSlot;
}

void CSkillPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	m_nSlotIndex = nOUTOFRANGE;
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_pScrollBar )
	{
		{
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBar->GetThumbFrame ();
			int nViewPerPage = pThumbFrame->GetViewPerPage ();
			int nBeforeSkillCnt = m_vecViewSkill.size();

			m_vecViewSkill.clear();
			for ( int i = 0; i < m_nMaxSkillCnt; i++ )
			{
				SNATIVEID sSkillID = m_pSkillSlotArray[i]->GetNativeSkillID();
				PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSkillID );
				if( pSkill && pSkill->m_sBASIC.bLearnView && !GLGaeaClient::GetInstance().GetCharacter()->GETLEARNED_SKILL( sSkillID ) ) continue;
				
				m_vecViewSkill.push_back( i );
			}
			if( nBeforeSkillCnt != m_vecViewSkill.size() )
			{
				m_pScrollBar->GetThumbFrame()->SetState ( m_vecViewSkill.size(), nMAX_ONE_VIEW_SLOT );
				ResetAllSkillSlotRender( m_nMaxSkillCnt );
				SetSkillSlotRender ( 0, 0 + nViewPerPage );			
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

				ResetAllSkillSlotRender ( nTotal );
				SetSkillSlotRender ( nCurPos, nCurPos + nViewPerPage );
			}
		}
	}
}

void CSkillPage::ResetAllSkillSlotRender ( int nTotal )
{
	if ( nTotal < 0 ) return ;

	for ( int i = 0; i < GLSkillMan::MAX_CLASSSKILL; i++ )
	{
		CSkillSlot* pSkillSlot = m_pSkillSlotArray[i];
		if ( pSkillSlot )
		{
			pSkillSlot->SetVisibleSingle ( FALSE );
		}
	}
}

void CSkillPage::SetSkillSlotRender ( int nStartIndex, int nTotal )
{
	if ( nTotal < 0 ) return ;

	const UIRECT& rcParentPos = GetGlobalPos ();

	

	int iViewIndex = 0; // ??? ??
	int iSlotNum   = 0;	// ???? SlotNum
	for ( int i = nStartIndex; i < m_vecViewSkill.size(); i++ )
	{
		if( i >= m_nMaxSkillCnt ) break;
		if( i >= nTotal ) break;

		iSlotNum = m_vecViewSkill[i];

		CSkillSlot* pSkillSlot = m_pSkillSlotArray[iSlotNum];
		if ( pSkillSlot )
		{
						
			int nAbsoluteIndex = iViewIndex;
			CUIControl* pDummyControl = m_pSkillSlotArrayDummy[nAbsoluteIndex];

			const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
			const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();

			pSkillSlot->SetLocalPos ( rcSlotLocalPos );			
			pSkillSlot->SetGlobalPos ( rcSlotPos );

			pSkillSlot->SetVisibleSingle ( TRUE );

			iViewIndex++;
		}
	}

	if( m_vecViewSkill.size() < nTotal )
	{
		int iMaxLackTotal = nTotal - m_vecViewSkill.size();		
		for( i = 0; i < iMaxLackTotal; i++ )
		{
			iSlotNum++;
			CSkillSlot* pSkillSlot = m_pSkillSlotArray[iSlotNum];
			if ( pSkillSlot )
			{

				int nAbsoluteIndex = iViewIndex;
				CUIControl* pDummyControl = m_pSkillSlotArrayDummy[nAbsoluteIndex];

				const UIRECT& rcSlotPos = pDummyControl->GetGlobalPos ();
				const UIRECT& rcSlotLocalPos = pDummyControl->GetLocalPos ();

				pSkillSlot->SetLocalPos ( rcSlotLocalPos );			
				pSkillSlot->SetGlobalPos ( rcSlotPos );

				pSkillSlot->SetVisibleSingle ( TRUE );

				iViewIndex++;
			}
		}
	}


	
	for( i = nTotal; i < m_vecViewSkill.size(); i++ )
	{
		iSlotNum = m_vecViewSkill[i];

		if( m_pSkillSlotArray[iSlotNum] ) m_pSkillSlotArray[iSlotNum]->SetVisibleSingle( FALSE );
	}
}

SNATIVEID  CSkillPage::GetSkillID ( int nIndex )
{	
	return m_pSkillSlotArray[nIndex]->GetNativeSkillID ();
}

void CSkillPage::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	if ( KYNANG_SLOT_0 <= ControlID && ControlID <= SKILL_SLOT_END )
	{
	/*case RNSKILL_SLOT_0:
	case RNSKILL_SLOT_1:
	case RNSKILL_SLOT_2:
	case RNSKILL_SLOT_3:
	case RNSKILL_SLOT_4:
	case RNSKILL_SLOT_5:
	case RNSKILL_SLOT_6:
	case RNSKILL_SLOT_7:
	case RNSKILL_SLOT_8:
	case RNSKILL_SLOT_9:
	case RNSKILL_SLOT_10:
	case RNSKILL_SLOT_11:
	case RNSKILL_SLOT_12:
	case RNSKILL_SLOT_13:
	case RNSKILL_SLOT_14:
	case RNSKILL_SLOT_15:
	case RNSKILL_SLOT_16:
	case RNSKILL_SLOT_17:*/
		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{
			m_nSlotIndex = ControlID - KYNANG_SLOT_0;
			//m_pSkillSlotArray[m_nSlotIndex]->SKILLSLOT_ACTIVE();
		}
		
	}
}
