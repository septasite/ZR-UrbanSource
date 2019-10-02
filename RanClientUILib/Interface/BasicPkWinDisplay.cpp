#include "StdAfx.h"
#include "BasicPkWinDisplay.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "d3dfont.h"



CBasicPkWinDisplay::CBasicPkWinDisplay ()
	: m_pPkWinText ( NULL )
	, m_dwPkWinBACK(0)
{
}

CBasicPkWinDisplay::~CBasicPkWinDisplay ()
{
	m_dwPkWinBACK = 0;
}

void CBasicPkWinDisplay::CreateSubControl ()
{	
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicTextBox* pPkWinText = new CBasicTextBox;
	pPkWinText->CreateSub ( this, "BASIC_PKWIN_DISPLAY_TEXT" );
    pPkWinText->SetFont ( pFont8 );
	pPkWinText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( pPkWinText );
	m_pPkWinText = pPkWinText;	
}

void CBasicPkWinDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	const DWORD& dwPkWin = GLGaeaClient::GetInstance().GetCharacter()->m_dwPkWin;

	if( m_dwPkWinBACK < dwPkWin )
	{
		m_dwPkWinBACK = dwPkWin;

		CUIGroup::Update( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		CString strPkWin;
		strPkWin.Format( "%d", m_dwPkWinBACK );	
		m_pPkWinText->SetOneLineText( strPkWin, NS_UITEXTCOLOR::GOLD /*PLUSOPTION*/ );
	}
}