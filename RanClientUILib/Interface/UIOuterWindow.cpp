#include "StdAfx.h"
#include "./UIOuterWindow.h"
#include "./OuterInterface.h"
#include "./BasicLineBox.h"
#include "../EngineUIlib/GUInterface/BasicTextBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CUIOuterWindow::CUIOuterWindow ()
{
}

CUIOuterWindow::~CUIOuterWindow ()
{
}

void CUIOuterWindow::CreateBaseWindowBlackRed ( char* szWindowKeyword, char* szWindowName )
{
	CreateTitleNoShadow ( "BASIC_WINDOW_BLACK_TITLE", "BASIC_WINDOW_BLACK_TITLE_LEFT", "BASIC_WINDOW_BLACK_TITLE_MID", "BASIC_WINDOW_BLACK_TITLE_RIGHT", "BASIC_WINDOW_BLACK_TEXTBOX", szWindowName );
	CreateBody ( "BASIC_WINDOW_BLACK_BODY", "BASIC_WINDOW_BLACK_BODY_LEFT", "BASIC_WINDOW_BLACK_BODY_UP", "OUTER_WINDOW_BODY_MAIN", "BASIC_WINDOW_BLACK_BODY_DOWN", "BASIC_WINDOW_BLACK_BODY_RIGHT" );
	ResizeControl ( szWindowKeyword );

    WORD wFlag = GetAlignFlag ();
	wFlag &= ~UI_FLAG_XSIZE;
	wFlag &= ~UI_FLAG_YSIZE;
	SetAlignFlag ( wFlag );
}

CBasicTextBox*	CUIOuterWindow::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );
	return pStaticText;
}

CUIControl*	CUIOuterWindow::CreateControl ( char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}


void CUIOuterWindow::ResizeControl ( char* szWindowKeyword )
{
    CUIControl TempControl;
	TempControl.Create ( 1, szWindowKeyword );
	const UIRECT& rcParentOldPos = GetLocalPos ();
	const UIRECT& rcParentNewPos = TempControl.GetLocalPos ();
	AlignSubControl ( rcParentOldPos, rcParentNewPos );

	SetLocalPos ( D3DXVECTOR2 ( rcParentNewPos.left, rcParentNewPos.top ) );
}

void CUIOuterWindow::TranslateUIMessage( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindow::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case ET_CONTROL_BUTTON:
		{
			if( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				COuterInterface::GetInstance().HideGroup( GetWndID() );
			}
		}
		break;
	}
}