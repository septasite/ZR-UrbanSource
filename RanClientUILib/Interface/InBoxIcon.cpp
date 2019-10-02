#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\InBoxIcon.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "BasicLineBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CInBoxIcon::CInBoxIcon(void) :
	m_pInBoxIcon(NULL)
{
}

CInBoxIcon::~CInBoxIcon(void)
{
}
void CInBoxIcon::CreateSubControl ()
{
	m_pInBoxIcon = new CBasicButton;
	m_pInBoxIcon->CreateSub ( this, "POSTNOTIFY_BUTTON_IMAGE_DEFAULT", UI_FLAG_DEFAULT, InBoxIconOnMouse );
	m_pInBoxIcon->SetUseGlobalAction ( TRUE );
	RegisterControl ( m_pInBoxIcon );
}
void CInBoxIcon::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}
void CInBoxIcon::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
switch ( ControlID )
	{
	case InBoxIconOnMouse:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Mail System On Development.", NS_UITEXTCOLOR::WHITE  );
			}
		}
		break;
	}
}