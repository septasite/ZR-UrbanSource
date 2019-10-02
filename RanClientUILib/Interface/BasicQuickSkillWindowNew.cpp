#include "StdAfx.h"
#include ".\skilltraytabNew.h"
#include ".\skilltraytab.h"
#include "BasicQuickSkillSlot.h"
#include "BasicQuickSkillWindowNew.h"
#include "BasicQuickSkillWindow.h"
#include "d3dfont.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "../EngineUILib/GUInterface/UIKeyCheck.h"


CBasicQuickSkillWindowNew::CBasicQuickSkillWindowNew(void)
	: TabLock ( TRUE )
{
}

CBasicQuickSkillWindowNew::~CBasicQuickSkillWindowNew(void)
{
}

void CBasicQuickSkillWindowNew::CreateSubControl()
{
	m_pBasicQuickSkillSlot = new CBasicQuickSkillSlot;
	m_pBasicQuickSkillSlot->CreateSub ( this, "BASIC_QUICK_SKILL_SLOT" );
	m_pBasicQuickSkillSlot->CreateSubControl ();
	m_pBasicQuickSkillSlot->SetUseSkillImageTwinkle( false ); // 스킬 종료시 깜빡이는 액션을 사용하지 않습니다.
	RegisterControl ( m_pBasicQuickSkillSlot );

	CUIControl* pSlotEnd = new CUIControl;
	pSlotEnd->CreateSub ( this, "BASIC_QUICK_SKILL_TRAY_SLOT_END_CLOSE_NEW" );
	pSlotEnd->SetControlNameEx ( "슬롯 엔드" );
    RegisterControl ( pSlotEnd );

	CBasicButton * pButton = new CBasicButton;
	pButton->CreateSub( this, "QUICK_SKILL_TRAY_OPEN_BUTTON_CLOSE_NEW", UI_FLAG_DEFAULT, QUICK_SKILL_TRAY_OPEN_BUTTON_CLOSE );
	pButton->CreateFlip( "QUICK_SKILL_TRAY_OPEN_BUTTON_CLOSE_NEW_F", CBasicButton::MOUSEIN_FLIP );
	pButton->SetUseGlobalAction ( TRUE );	
	RegisterControl( pButton );

	pButtonLock = new CBasicButton;
	pButtonLock->CreateSub( this, "QUICK_SKILL_TRAY_LOCK_BUTTON_CLOSE_NEW", UI_FLAG_DEFAULT, QUICK_SKILL_TRAY_LOCK_BUTTON_CLOSE );
	pButtonLock->CreateFlip( "QUICK_SKILL_TRAY_LOCK_BUTTON_CLOSE_NEW_F", CBasicButton::MOUSEIN_FLIP );
	pButtonLock->SetUseGlobalAction ( TRUE );
	pButtonLock->SetVisibleSingle ( FALSE );
	RegisterControl ( pButtonLock );
	SetFoldGroup( pButtonLock, TABBUTTON_FOLDGROUP_ID );

	pButtonUnLock = new CBasicButton;
	pButtonUnLock->CreateSub( this, "QUICK_SKILL_TRAY_UNLOCK_BUTTON_CLOSE_NEW", UI_FLAG_DEFAULT, QUICK_SKILL_TRAY_UNLOCK_BUTTON_CLOSE );
	pButtonUnLock->CreateFlip( "QUICK_SKILL_TRAY_UNLOCK_BUTTON_CLOSE_NEW_F", CBasicButton::MOUSEIN_FLIP );
	pButtonUnLock->SetUseGlobalAction ( TRUE );
	pButtonUnLock->SetVisibleSingle ( TRUE );
	RegisterControl ( pButtonUnLock );
	SetFoldGroup( pButtonUnLock, TABBUTTON_FOLDGROUP_ID );
}

void CBasicQuickSkillWindowNew::CheckMouseState ()
{
	const DWORD dwMsg = GetMessageEx ();
	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{	
		if( UIMSG_LB_DUP & dwMsg )
		{
			// 윈도우를 디폴트 포지션으로 이동
			AddMessageEx( UIMSG_BASIC_LBDUP_WINDOW_NEW );
			return ;
		}
		
		if ( dwMsg & UIMSG_LB_DOWN )
		{
			CInnerInterface::GetInstance().SkillTabCloseNew = FALSE;

			//	단독 컨트롤로 등록하고,
			SetExclusiveControl();	

			//	최초 포지션 갭을 기록한다.
			if ( !m_bFirstGap )
			{
				UIRECT rcPos = GetGlobalPos ();
				m_vGap.x = m_PosX - rcPos.left;
				m_vGap.y = m_PosY - rcPos.top;
				m_bFirstGap = TRUE;
			}
		}
		else if ( CHECK_LB_UP_LIKE ( dwMsg ) )
		{
			//	단독 컨트롤을 해제하고
			ResetExclusiveControl();
			//	최초 포지션갭을 해제한다.
			m_bFirstGap = FALSE;				
		}
	}
	//	컨트롤 영역밖에서 버튼을 떼는 경우가 발생하더라도
	else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
	{								
		//	단독 컨트롤을 해제하고,
		ResetExclusiveControl();
		//	최초 포지션갭을 해제한다.
		m_bFirstGap = FALSE;					
	}
}
void CBasicQuickSkillWindowNew::Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( TabLock )
	{
		m_bCHECK_MOUSE_STATE = false;
	}
	m_PosX = x;
	m_PosY = y;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( IsExclusiveSelfControl() )
	{
		SetGlobalPos ( D3DXVECTOR2 ( x - m_vGap.x, y - m_vGap.y ) );
	}
}
void CBasicQuickSkillWindowNew::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( !m_bCHECK_MOUSE_STATE )
	{
		CheckMouseState ();
		m_bCHECK_MOUSE_STATE = true;
	}

	switch ( ControlID )
	{
	case QUICK_SKILL_TRAY_OPEN_BUTTON_CLOSE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					CInnerInterface::GetInstance().HideGroup ( GetWndID () );
					CInnerInterface::GetInstance().SkillTabOpenNew = TRUE;
					CInnerInterface::GetInstance().ShowGroupFocus ( QUICK_SKILL_TRAY_TAB_NEW_WINDOW, true );
				}
			}
		}
		break;
	case QUICK_SKILL_TRAY_LOCK_BUTTON_CLOSE:
	case QUICK_SKILL_TRAY_UNLOCK_BUTTON_CLOSE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE( dwMsg ) )
				{
					if ( pButtonLock->IsVisible() )
					{
						pButtonLock->SetVisibleSingle ( FALSE );
						pButtonUnLock->SetVisibleSingle ( TRUE );
						CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetUnlock();
						CInnerInterface::GetInstance().GetSkillTrayTab()->SetUnlock();
						CInnerInterface::GetInstance().GetBasicQuickSkillWindow()->SetUnlock();
						TabLock = TRUE;
					}else
					{
						pButtonLock->SetVisibleSingle ( TRUE );
						pButtonUnLock->SetVisibleSingle ( FALSE );
						CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetLock();
						CInnerInterface::GetInstance().GetSkillTrayTab()->SetLock();
						CInnerInterface::GetInstance().GetBasicQuickSkillWindow()->SetLock();
						TabLock = FALSE;
					}
				}
			}
		}
		break;
	}
}
void CBasicQuickSkillWindowNew::SetLock()
{
	pButtonLock->SetVisibleSingle ( TRUE );
	pButtonUnLock->SetVisibleSingle ( FALSE );
	TabLock = FALSE;
}
void CBasicQuickSkillWindowNew::SetUnlock()
{
	pButtonLock->SetVisibleSingle ( FALSE );
	pButtonUnLock->SetVisibleSingle ( TRUE );
	TabLock = TRUE;
}