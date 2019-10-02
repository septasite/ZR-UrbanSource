#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\AtteIcon.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "BasicLineBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CAtteIcon::CAtteIcon(void) :
	m_pAtteIcon(NULL)
{
}

CAtteIcon::~CAtteIcon(void)
{
}
void CAtteIcon::CreateSubControl ()
{
	m_pAtteIcon = new CBasicButton;
	m_pAtteIcon->CreateSub ( this, "STUDENTRECORD_NOTIFY_BUTTON_IMAGE", UI_FLAG_DEFAULT, AtteIconOnMouse );
	m_pAtteIcon->SetUseGlobalAction ( TRUE );
	RegisterControl ( m_pAtteIcon );
}
void CAtteIcon::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}
void CAtteIcon::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
switch ( ControlID )
	{
	case AtteIconOnMouse:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Attendance System", NS_UITEXTCOLOR::WHITE  );

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( ATTENDANCE_BOOK_WINDOW ) )
					{
						CInnerInterface::GetInstance().ShowGroupFocus ( ATTENDANCE_BOOK_WINDOW );
					}
					else
					{
						CInnerInterface::GetInstance().HideGroup ( ATTENDANCE_BOOK_WINDOW );
					}
				}
			}
		}
		break;
	}
}