#include "StdAfx.h"
#include "BasicRebornDisplay.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "d3dfont.h"



CBasicRebornDisplay::CBasicRebornDisplay ()
	: m_pRebornText ( NULL )
	, m_nRebornBACK(0)
{
}

CBasicRebornDisplay::~CBasicRebornDisplay ()
{
	m_nRebornBACK = 0;
}

void CBasicRebornDisplay::CreateSubControl ()
{	
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW );

	CBasicTextBox* pRebornText = new CBasicTextBox;
	pRebornText->CreateSub ( this, "BASIC_REBORN_DISPLAY_TEXT" );
    pRebornText->SetFont ( pFont8 );
	pRebornText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( pRebornText );
	m_pRebornText = pRebornText;	
}

void CBasicRebornDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	const int& nChaReborn = GLGaeaClient::GetInstance().GetCharacter()->m_nChaReborn;

	if( m_nRebornBACK < nChaReborn )
	{
		m_nRebornBACK = nChaReborn;

		CUIGroup::Update( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		//CString strReborn;
		//strReborn.Format( "%d", m_nRebornBACK );	
		//m_pRebornText->SetOneLineText( strReborn, NS_UITEXTCOLOR::GOLD /*PLUSOPTION*/ );
	}
}