#include "StdAfx.h"
#include "SkillTrayTabNew.h"
#include "BasicSkillTrayNew.h"
#include "BasicSkillTray.h"
#include "BasicQuickSkillSlot.h"
#include "BasicQuickSkillSlotEx.h"
#include "BasicQuickSkillWindowNew.h"
#include "BasicQuickSkillWindow.h"

#include "d3dfont.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "BasicTextButton.h"

#include "../EngineUILib/GUInterface/UIKeyCheck.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"

INT CSkillTrayTabNew::NEXT_INDEX_NEW[] = {1, 2, 3, 0};

CSkillTrayTabNew::CSkillTrayTabNew(void)
	: m_nTabIndex(0)
	, m_nCount(0)
	, pButtonRotate(NULL)
	, TabLock ( TRUE )
{
	memset( m_pSkillTray, 0, sizeof( CBasicSkillTray* ) * MAX_TAB_INDEX_NEW );
}

CSkillTrayTabNew::~CSkillTrayTabNew(void)
{
}

void CSkillTrayTabNew::CreateSubControl()
{
	CD3DFontPar * m_pFont8 = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT, 8, D3DFONT_SHADOW );

	CBasicSkillTrayNew * pSkillTray = new CBasicSkillTrayNew;
	pSkillTray->CreateSub( this, "BASIC_QUICK_SKILL_TRAY_NEW", UI_FLAG_DEFAULT, BASIC_QUICK_SKILL_TRAY_F1 );
	pSkillTray->CreateSubControl( 0 );
	RegisterControl( pSkillTray );
	m_pSkillTray[0] = pSkillTray;

	pSkillTray = new CBasicSkillTrayNew;
	pSkillTray->CreateSub( this, "BASIC_QUICK_SKILL_TRAY_NEW", UI_FLAG_DEFAULT, BASIC_QUICK_SKILL_TRAY_F2 );
	pSkillTray->CreateSubControl( 1 );
	pSkillTray->SetVisibleSingle( FALSE );
	RegisterControl( pSkillTray );
	m_pSkillTray[1] = pSkillTray;

	pSkillTray = new CBasicSkillTrayNew;
	pSkillTray->CreateSub( this, "BASIC_QUICK_SKILL_TRAY_NEW", UI_FLAG_DEFAULT, BASIC_QUICK_SKILL_TRAY_F3 );
	pSkillTray->CreateSubControl( 2 );
	pSkillTray->SetVisibleSingle( FALSE );
	RegisterControl( pSkillTray );
	m_pSkillTray[2] = pSkillTray;

	pSkillTray = new CBasicSkillTrayNew;
	pSkillTray->CreateSub( this, "BASIC_QUICK_SKILL_TRAY_NEW", UI_FLAG_DEFAULT, BASIC_QUICK_SKILL_TRAY_F4 );
	pSkillTray->CreateSubControl( 3 );
	pSkillTray->SetVisibleSingle( FALSE );
	RegisterControl( pSkillTray );
	m_pSkillTray[3] = pSkillTray;


	{
		CUIControl*	m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "QUICK_SKILL_TEXT_BUTTON14_NEW", UI_FLAG_DEFAULT );	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	}


// #ifndef CH_PARAM // 중국 인터페이스 변경
	CBasicButton * pButton = new CBasicButton;
	pButton->CreateSub( this, "QUICK_SKILL_TRAY_CLOSE_NEW_BUTTON", UI_FLAG_DEFAULT, QUICK_SKILL_TRAY_CLOSE_NEW_BUTTON );
	pButton->CreateFlip( "QUICK_SKILL_TRAY_CLOSE_NEW_BUTTON_F", CBasicButton::MOUSEIN_FLIP );
	pButton->SetUseGlobalAction ( TRUE );	
	RegisterControl( pButton );

	pButtonRotate = new CBasicButton;
	pButtonRotate->CreateSub( this, "QUICK_SKILL_TRAY_ROTATE_NEW_BUTTON", UI_FLAG_DEFAULT, QUICK_SKILL_TRAY_ROTATE_NEW_BUTTON );
	pButtonRotate->CreateFlip( "QUICK_SKILL_TRAY_ROTATE_NEW_BUTTON_F", CBasicButton::MOUSEIN_FLIP );
	pButtonRotate->SetUseGlobalAction ( TRUE );
	pButtonRotate->SetVisibleSingle(TRUE);
	RegisterControl( pButtonRotate );

	m_pPageNumber = new CBasicTextBox;
	m_pPageNumber->CreateSub ( this, "NEW_SKILL_PAGE_NUMBER_NEW", UI_FLAG_DEFAULT, TEXT_BUTTON_CLICK );
	m_pPageNumber->SetFont ( m_pFont8 );
	m_pPageNumber->SetTextAlign ( TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pPageNumber->AddText ( ID2GAMEWORD( "SKILL_TAB_INFO", 0 ) );
	RegisterControl ( m_pPageNumber );

	pButtonLock = new CBasicButton;
	pButtonLock->CreateSub( this, "QUICK_SKILL_TRAY_LOCK_BUTTON_NEW", UI_FLAG_DEFAULT, QUICK_SKILL_TRAY_LOCK_BUTTON );
	pButtonLock->CreateFlip( "QUICK_SKILL_TRAY_LOCK_BUTTON_NEW_F", CBasicButton::MOUSEIN_FLIP );
	pButtonLock->SetUseGlobalAction ( TRUE );
	pButtonLock->SetVisibleSingle ( FALSE );
	RegisterControl ( pButtonLock );
	SetFoldGroup( pButtonLock, TABBUTTON_FOLDGROUP_ID );

	pButtonUnLock = new CBasicButton;
	pButtonUnLock->CreateSub( this, "QUICK_SKILL_TRAY_UNLOCK_BUTTON_NEW", UI_FLAG_DEFAULT, QUICK_SKILL_TRAY_UNLOCK_BUTTON );
	pButtonUnLock->CreateFlip( "QUICK_SKILL_TRAY_UNLOCK_BUTTON_NEW_F", CBasicButton::MOUSEIN_FLIP );
	pButtonUnLock->SetUseGlobalAction ( TRUE );
	pButtonUnLock->SetVisibleSingle ( TRUE );
	RegisterControl ( pButtonUnLock );
	SetFoldGroup( pButtonUnLock, TABBUTTON_FOLDGROUP_ID );


	m_pBasicQuickSkillSlot = new CBasicQuickSkillSlot;
	m_pBasicQuickSkillSlot->CreateSub ( this, "BASIC_QUICK_SKILL_SLOT" );
	m_pBasicQuickSkillSlot->CreateSubControl ();
	m_pBasicQuickSkillSlot->SetUseSkillImageTwinkle( false ); // 스킬 종료시 깜빡이는 액션을 사용하지 않습니다.
	RegisterControl ( m_pBasicQuickSkillSlot );

// #endif
}

void CSkillTrayTabNew::Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
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

	if ( CInnerInterface::GetInstance().IsVisibleGroup( MODAL_WINDOW ) ) return ;

	INT nOldIndex = GetTabIndex();
	INT nNewIndex( nOldIndex );

	if( UIKeyCheck::GetInstance()->Check( DIK_F1, DXKEY_DOWN ) )	
	{
		nNewIndex = 0;
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabIndex( 0 );
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabTextIndex( 0 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabIndex( 0 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabTextIndex( 0 );
	}
	if( UIKeyCheck::GetInstance()->Check( DIK_F2, DXKEY_DOWN ) )	
	{
		nNewIndex = 1;
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabIndex( 1 );
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabTextIndex( 1 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabIndex( 1 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabTextIndex( 1 );
	}
	if( UIKeyCheck::GetInstance()->Check( DIK_F3, DXKEY_DOWN ) )	
	{
		nNewIndex = 2;
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabIndex( 2 );
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabTextIndex( 2 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabIndex( 2 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabTextIndex( 2 );
	}

	if( UIKeyCheck::GetInstance()->Check( DIK_F4, DXKEY_DOWN ) )	
	{
		nNewIndex = 3;
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabIndex( 3 );
		CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetTabTextIndex( 3 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabIndex( 3 );
		CInnerInterface::GetInstance().GetSkillTrayTab()->SetTabTextIndex( 3 );
	}


	if( nNewIndex == nOldIndex ) return ;
	else
	{
		m_pSkillTray[nOldIndex]->SetVisibleSingle( FALSE );
		m_pSkillTray[nNewIndex]->SetVisibleSingle( TRUE );
		SetTabIndex( nNewIndex );
	}
}
void CSkillTrayTabNew::CheckMouseState ()
{
	const DWORD dwMsg = GetMessageEx ();
	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{
		if( UIMSG_LB_DUP & dwMsg )
		{
			// 윈도우를 디폴트 포지션으로 이동
			AddMessageEx( UIMSG_BASIC_LBDUP_NEW );
			return ;
		}	
		if ( dwMsg & UIMSG_LB_DOWN )
		{
			CInnerInterface::GetInstance().SkillTabOpenNew = FALSE;
			CInnerInterface::GetInstance().RotateSkillTab = FALSE;

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
void CSkillTrayTabNew::SetTabTextIndex ( INT nIndex )
{
	if( nIndex == 0 )
	{
		m_pPageNumber->ClearText();
		m_pPageNumber->AddText ( ID2GAMEWORD( "SKILL_TAB_INFO", 0 ) );
	}
	else if ( nIndex == 1 )
	{
		m_pPageNumber->ClearText();
		m_pPageNumber->AddText ( ID2GAMEWORD( "SKILL_TAB_INFO", 1 ) );
	}
	else if ( nIndex == 2 )
	{
		m_pPageNumber->ClearText();
		m_pPageNumber->AddText ( ID2GAMEWORD( "SKILL_TAB_INFO", 2 ) );
	}
	else if ( nIndex == 3 )
	{
		m_pPageNumber->ClearText();
		m_pPageNumber->AddText ( ID2GAMEWORD( "SKILL_TAB_INFO", 3 ) );
	}

}
void CSkillTrayTabNew::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( !m_bCHECK_MOUSE_STATE )
	{
		CheckMouseState ();
		m_bCHECK_MOUSE_STATE = true;
	}

	switch ( ControlID )
	{
	case TEXT_BUTTON_CLICK:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE( dwMsg ) )
				{
					INT nIndex = GetTabIndex();
					INT nNextIndex = NEXT_INDEX_NEW[nIndex];

					m_pSkillTray[nIndex]->SetVisibleSingle( FALSE );
					m_pSkillTray[nNextIndex]->SetVisibleSingle( TRUE );

					SetTabIndex( nNextIndex );
				}
			}
		}
		break;
	case QUICK_SKILL_TRAY_CLOSE_NEW_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					CInnerInterface::GetInstance().HideGroup ( GetWndID () );
					CInnerInterface::GetInstance().SkillTabCloseNew = TRUE;
					CInnerInterface::GetInstance().ShowGroupFocus ( BASIC_QUICK_SKILL_NEW_WINDOW, true );
				}
			}
		}
		break;
	case QUICK_SKILL_TRAY_ROTATE_NEW_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					CInnerInterface::GetInstance().HideGroup ( GetWndID () );
					CInnerInterface::GetInstance().RotateSkillTabNew = TRUE;
					CInnerInterface::GetInstance().ShowGroupFocus ( QUICK_SKILL_TRAY_TAB_WINDOW, true );
				}
			}

		}
		break;
	case QUICK_SKILL_TRAY_LOCK_BUTTON:
	case QUICK_SKILL_TRAY_UNLOCK_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE( dwMsg ) )
				{
					if ( pButtonLock->IsVisible() )
					{
						pButtonLock->SetVisibleSingle ( FALSE );
						pButtonUnLock->SetVisibleSingle ( TRUE );
						TabLock = TRUE;
						CInnerInterface::GetInstance().GetBasicQuickSkillWindowNew()->SetUnlock();
						CInnerInterface::GetInstance().GetBasicQuickSkillWindow()->SetUnlock();
						CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetUnlock();
						CInnerInterface::GetInstance().GetSkillTrayTab()->SetUnlock();
					}else{
						pButtonLock->SetVisibleSingle ( TRUE );
						pButtonUnLock->SetVisibleSingle ( FALSE );
						TabLock = FALSE;
						CInnerInterface::GetInstance().GetBasicQuickSkillWindowNew()->SetLock();
						CInnerInterface::GetInstance().GetBasicQuickSkillWindow()->SetLock();
						CInnerInterface::GetInstance().GetSkillTrayTabNew()->SetLock();
						CInnerInterface::GetInstance().GetSkillTrayTab()->SetLock();
					}
				}
			}
		}
		break;
	case BASIC_QUICK_SKILL_TRAY_F1:
	case BASIC_QUICK_SKILL_TRAY_F2:
	case BASIC_QUICK_SKILL_TRAY_F3:
	case BASIC_QUICK_SKILL_TRAY_F4:
		{
			if( dwMsg & UIMSG_MOUSEIN_SKILLSLOT )
			{
				AddMessageEx ( UIMSG_MOUSEIN_SKILLSLOT );
			}
		}
		break;
	}
}
void CSkillTrayTabNew::SetLock()
{
	pButtonLock->SetVisibleSingle ( TRUE );
	pButtonUnLock->SetVisibleSingle ( FALSE );
	TabLock = FALSE;
}
void CSkillTrayTabNew::SetUnlock()
{
	pButtonLock->SetVisibleSingle ( FALSE );
	pButtonUnLock->SetVisibleSingle ( TRUE );
	TabLock = TRUE;
}
void CSkillTrayTabNew::SetVisibleSingle( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		m_pSkillTray[0]->SetVisibleSingle( FALSE );
		m_pSkillTray[1]->SetVisibleSingle( FALSE );
		m_pSkillTray[2]->SetVisibleSingle( FALSE );
		m_pSkillTray[3]->SetVisibleSingle( FALSE );

		INT nIndex = GetTabIndex();
		m_pSkillTray[nIndex]->SetVisibleSingle( TRUE );
	}
}

void CSkillTrayTabNew::SetShotcutText ( DWORD nID, CString& strTemp )
{
	m_pSkillTray[0]->SetShotcutText( nID, strTemp );
	m_pSkillTray[1]->SetShotcutText( nID, strTemp );
	m_pSkillTray[2]->SetShotcutText( nID, strTemp );
	m_pSkillTray[3]->SetShotcutText( nID, strTemp );

}