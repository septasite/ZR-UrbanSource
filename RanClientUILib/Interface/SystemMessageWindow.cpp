#include "StdAfx.h"
#include "SystemMessageWindow.h"
#include "BasicLineBox.h"
#include "../EngineUIlib/GUInterface/BasicTextBox.h"
#include "BasicTextButton.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GameTextControl.h"
#include "GLCharacter.h"
#include "GLGaeaClient.h"
#include "DxGlobalStage.h"
#include "InnerInterface.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSystemMessageWindow::CSystemMessageWindow () :
	m_pTextBox ( NULL ),
	m_fElapsedTime ( 0.0f )
{
}

CSystemMessageWindow::~CSystemMessageWindow ()
{
}

void CSystemMessageWindow::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 12, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicLineBox* pLineBox = new CBasicLineBox;
	pLineBox->CreateSub ( this, "TINNHAN_HETHONG_GIUA", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->BlackCatYBSystemMessage ( "KHUNG_TINNHAN_HETHONG" );
	pLineBox->ResetAlignFlag ();
	RegisterControl ( pLineBox );	

/*	pLineBox = new CBasicLineBox;
	pLineBox->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxSystemMessageUp ( "KHUNGCHU_TINNHAN_HETHONG" );
	pLineBox->ResetAlignFlag ();
	RegisterControl ( pLineBox );*/

	CBasicTextBox* pMapMoveTextBox = new CBasicTextBox;
	pMapMoveTextBox->CreateSub ( this, "TINNHAN_HETHONG_HOPCHU", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
    pMapMoveTextBox->SetFont ( pFont9 );
	pMapMoveTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	pMapMoveTextBox->ResetAlignFlag ();
	RegisterControl ( pMapMoveTextBox );
	m_pTextBox = pMapMoveTextBox;
}

void	CSystemMessageWindow::SetSystemMessage ( const CString& strMessage, const D3DCOLOR& dwColor )
{
	if ( m_pTextBox )
	{
		m_pTextBox->SetText ( strMessage, dwColor );

  		m_fElapsedTime = 6.0f;

		CInnerInterface::GetInstance().ShowGroupTop ( GetWndID (), true );
	}
}

void CSystemMessageWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	m_fElapsedTime -= fElapsedTime;
	ResetMessageEx ();
	if ( m_fElapsedTime <= 0.0f ) CInnerInterface::GetInstance().HideGroup ( GetWndID(), true );
}
