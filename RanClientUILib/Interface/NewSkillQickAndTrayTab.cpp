#include "StdAfx.h"
#include ".\skilltraytab.h"
#include "BasicQuickSkillSlot.h"
#include "BasicSkillTray.h"
#include "NewSkillQickAndTrayTab.h"
#include "d3dfont.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "SkillWindowToTray.h"
#include "../EngineUILib/GUInterface/UIKeyCheck.h"

CNewSkillQickAndTrayTab::CNewSkillQickAndTrayTab ()
	: m_pBasicQuickSkillSlot( NULL )
	, m_pSkillTrayTab( NULL )
{

}

CNewSkillQickAndTrayTab::~CNewSkillQickAndTrayTab ()
{
}

void CNewSkillQickAndTrayTab::CreateSubControl ()
{
	m_pBasicQuickSkillSlot = new CBasicQuickSkillSlot;
	m_pBasicQuickSkillSlot->Create ( BASIC_QUICK_SKILL_SLOT, "BASIC_QUICK_SKILL_SLOT" );
	m_pBasicQuickSkillSlot->CreateSubControl ();
	m_pBasicQuickSkillSlot->SetUseSkillImageTwinkle( false ); // 스킬 종료시 깜빡이는 액션을 사용하지 않습니다.
	RegisterControl ( m_pBasicQuickSkillSlot );
	//ShowGroupFocus ( BASIC_QUICK_SKILL_SLOT );

	m_pSkillTrayTab = new CSkillTrayTab;
	m_pSkillTrayTab->CreateEx( QUICK_SKILL_TRAY_TAB_WINDOW, "QUICK_SKILL_TRAY_TAB_WINDOW" );
	m_pSkillTrayTab->CreateSubControl();
	RegisterControl( m_pSkillTrayTab );
	//ShowGroupFocus ( QUICK_SKILL_TRAY_TAB_WINDOW );
}
void CNewSkillQickAndTrayTab::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	m_bCHECK_MOUSE_STATE = false;

	m_PosX = x;
	m_PosY = y;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( IsExclusiveSelfControl() )
	{
		SetGlobalPos ( D3DXVECTOR2 ( x - m_vGap.x, y - m_vGap.y ) );
		//pSkillTrayTab->SetGlobalPos ( D3DXVECTOR2 ( x - m_vGap.x, y - m_vGap.y ) );
		
		//UIRECT rcPosNew = GetGlobalPos ();
		//int newY = rcPosNew.bottom;

		//pButton->SetGlobalPos( D3DXVECTOR2 ( x - m_vGap.x, newY ) );

		//int newXX = rcPosNew.left;
		//int newYY = rcPosNew.top;

		//CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetGlobalPos ( D3DXVECTOR2 ( newXX, newYY ) );
	}
}
void CNewSkillQickAndTrayTab::CheckMouseState ()
{
	const DWORD dwMsg = GetMessageEx ();
	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{
		if( UIMSG_LB_DUP & dwMsg )
		{
			// 윈도우를 디폴트 포지션으로 이동
			AddMessageEx( UIMSG_NEW_SKILL_TAB_LBDUP );
			//SetDiffuse ( D3DCOLOR_ARGB ( 0xFF, 0xFF, 0xFF, 0xFF ) );
			return ;
		}
		
		if ( dwMsg & UIMSG_LB_DOWN )
		{
			//	단독 컨트롤로 등록하고,
			SetExclusiveControl();	

			//	최초 포지션 갭을 기록한다.
			if ( !m_bFirstGap )
			{
				UIRECT rcPos = GetGlobalPos ();
				m_vGap.x = m_PosX - rcPos.left;
				m_vGap.y = m_PosY - rcPos.top;
				m_bFirstGap = TRUE;

				//SetDiffuse ( D3DCOLOR_ARGB ( 0xB4, 0xFF, 0xFF, 0xFF ) );
			}
		}
		else if ( CHECK_LB_UP_LIKE ( dwMsg ) )
		{
			//	단독 컨트롤을 해제하고
			ResetExclusiveControl();
			//	최초 포지션갭을 해제한다.
			m_bFirstGap = FALSE;				

			//SetDiffuse ( D3DCOLOR_ARGB ( 0xFF, 0xFF, 0xFF, 0xFF ) );
		}
	}
	//	컨트롤 영역밖에서 버튼을 떼는 경우가 발생하더라도
	else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
	{								
		//	단독 컨트롤을 해제하고,
		ResetExclusiveControl();
		//	최초 포지션갭을 해제한다.
		m_bFirstGap = FALSE;					

		//SetDiffuse ( D3DCOLOR_ARGB ( 0xFF, 0xFF, 0xFF, 0xFF ) );
	}
}
void CNewSkillQickAndTrayTab::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( !m_bCHECK_MOUSE_STATE )
	{
		CheckMouseState ();
		m_bCHECK_MOUSE_STATE = true;
	}

		switch ( ControlID )
		{
		case QUICK_SKILL_TRAY_TAB_WINDOW:
			{
				if ( CHECK_MOUSE_IN ( dwMsg ) )
				{
					CSkillWindowToTray* pSkillWindowToTray = CInnerInterface::GetInstance().GetSkillWindowToTray ();
					if ( pSkillWindowToTray )
					{
						pSkillWindowToTray->SetUseSnap ( (dwMsg & UIMSG_MOUSEIN_SKILLSLOT) ? TRUE : FALSE );
					}
				}
			}
			break;
		}
}