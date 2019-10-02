#include "StdAfx.h"
#include "BasicPkLossDisplay.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "d3dfont.h"



CBasicPkLossDisplay::CBasicPkLossDisplay ()
	: m_pPkLossText ( NULL )
	, m_dwPkLossBACK(0)
{
}

CBasicPkLossDisplay::~CBasicPkLossDisplay ()
{
	m_dwPkLossBACK = 0;
}

void CBasicPkLossDisplay::CreateSubControl ()
{	
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicTextBox* pPkLossText = new CBasicTextBox;
	pPkLossText->CreateSub ( this, "BASIC_PKLOSS_DISPLAY_TEXT" );
    pPkLossText->SetFont ( pFont8 );
	pPkLossText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( pPkLossText );
	m_pPkLossText = pPkLossText;	
}

void CBasicPkLossDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	const DWORD& dwPkLoss = GLGaeaClient::GetInstance().GetCharacter()->m_dwPkLoss;

	if( m_dwPkLossBACK < dwPkLoss )
	{
		m_dwPkLossBACK = dwPkLoss;

		CUIGroup::Update( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		CString strPkLoss;
		strPkLoss.Format( "%d", m_dwPkLossBACK );	
		m_pPkLossText->SetOneLineText( strPkLoss, NS_UITEXTCOLOR::GOLD /*PLUSOPTION*/ );
	}
}