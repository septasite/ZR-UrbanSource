#include "StdAfx.h"
#include "PartyWindowCheckBox.h"

#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartyWindowCheckBox::CPartyWindowCheckBox ():
	m_pNormal(NULL),
	m_pFlip(NULL),
	m_pTextTitle(NULL),
	m_bCHECKED(FALSE)
{
}

CPartyWindowCheckBox::~CPartyWindowCheckBox ()
{
}

void CPartyWindowCheckBox::CreateSubControl()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, _DEFAULT_FONT_SHADOW_FLAG );
	
	m_bCHECKED = TRUE;

	m_pNormal = new CUIControl;
	m_pNormal->CreateSub ( this, "PARTY_WINDOW_CHECKBOX_OFF" );
	m_pNormal->SetTransparentOption( TRUE );
	m_pNormal->SetVisibleSingle(!m_bCHECKED);
	RegisterControl ( m_pNormal );
	
	m_pFlip = new CUIControl;
	m_pFlip->CreateSub ( this, "PARTY_WINDOW_CHECKBOX_ON" );
	m_pFlip->SetTransparentOption( TRUE );
	m_pFlip->SetVisibleSingle(m_bCHECKED);
	RegisterControl ( m_pFlip );
	
	m_pTextTitle = new CBasicTextBox;
	m_pTextTitle->CreateSub ( this, "PARTY_WINDOW_MAIN_CHECK_TEXT_TITLE_POS" );
	m_pTextTitle->SetFont ( pFont );
	m_pTextTitle->SetTextAlign ( TEXT_ALIGN_LEFT );	
	RegisterControl ( m_pTextTitle );
}

void CPartyWindowCheckBox::SetCheck()
{
	m_bCHECKED = !m_bCHECKED;

	m_pFlip->SetVisibleSingle(m_bCHECKED);
	m_pNormal->SetVisibleSingle(!m_bCHECKED);
}

int CPartyWindowCheckBox::SetTextTitle(CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextTitle ) return m_pTextTitle->AddTextNoSplit( strText, dwColor );
	return -1;
}