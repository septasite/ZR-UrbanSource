#include "StdAfx.h"
#include "LargeMapWindowRadio.h"

#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLargeMapWindowRadio::CLargeMapWindowRadio ():
	m_pNormal(NULL),
	m_pFlip(NULL),
	m_pText(NULL)
{
}

CLargeMapWindowRadio::~CLargeMapWindowRadio ()
{
}

void CLargeMapWindowRadio::CreateSubControl()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	
	m_pNormal = new CUIControl;
	m_pNormal->CreateSub ( this, "MAP_WINDOW_RADIO_OFF_TEXTUREINFO" );
	m_pNormal->SetTransparentOption( TRUE );
	RegisterControl ( m_pNormal );
	
	m_pFlip = new CUIControl;
	m_pFlip->CreateSub ( this, "MAP_WINDOW_RADIO_ON_TEXTUREINFO" );
	m_pFlip->SetTransparentOption( TRUE );
	RegisterControl ( m_pFlip );

	m_pText = new CBasicTextBox;
	m_pText->CreateSub ( this, "MAP_WINDOW_MAIN_RADIO_TEXT_POS" );
	m_pText->SetFont ( pFont );
	m_pText->SetTextAlign ( TEXT_ALIGN_LEFT );	
	RegisterControl ( m_pText );
}

void CLargeMapWindowRadio::SetRadioOn(BOOL bFLIP)
{
	m_pNormal->SetVisibleSingle(FALSE);
	m_pFlip->SetVisibleSingle(FALSE);

	if ( bFLIP ) m_pFlip->SetVisibleSingle(TRUE);
	else m_pNormal->SetVisibleSingle(TRUE);
}

int CLargeMapWindowRadio::SetRadioText(CString strText)
{
	if ( m_pText ) return m_pText->AddTextNoSplit( strText, NS_UITEXTCOLOR::WHITE );
	return -1;
}