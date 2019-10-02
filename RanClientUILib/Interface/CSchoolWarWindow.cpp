#include "StdAfx.h"
#include "CSchoolWarWindow.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "d3dfont.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "CSwPRankingDisplay.h"
#include "CSwRankingDisplay.h"
#include "InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSchoolWarWindow::CSchoolWarWindow ()
	: m_pSwPRanking( NULL )
	, m_pSwRanking ( NULL )
	, m_pBackGround( NULL )
{
}

CSchoolWarWindow::~CSchoolWarWindow ()
{
}

void CSchoolWarWindow::CreateSubControl ()
{
	m_pBackGround = new CUIControl;
	m_pBackGround->CreateSub ( this, "SCHOOLWAR_WINDOW_BACKGROUND", UI_FLAG_DEFAULT );	
	m_pBackGround->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pBackGround );

	m_pSwPRanking = new CSwPRankingDisplay;
	m_pSwPRanking->CreateSub ( this, "SCHOOLWAR_PLAYER_WINDOW_REGION", UI_FLAG_XSIZE, PAGE_PLAYER );
	m_pSwPRanking->CreateSubControl ();
	m_pSwPRanking->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pSwPRanking );

	m_pSwRanking = new CSwRankingDisplay;
	m_pSwRanking->CreateSub ( this, "SCHOOLWAR_SCHOOL_WINDOW_REGION", UI_FLAG_XSIZE, PAGE_SCHOOL );
	m_pSwRanking->CreateSubControl ();
	m_pSwRanking->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pSwRanking );
}

void CSchoolWarWindow::SetGlobalPos(const D3DXVECTOR2& vPos)
{
	CUIGroup::SetGlobalPos( vPos );
}

void CSchoolWarWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( SCHOOL_WARS_WINDOW );
			}
		}
		break;
	}
}


void CSchoolWarWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}