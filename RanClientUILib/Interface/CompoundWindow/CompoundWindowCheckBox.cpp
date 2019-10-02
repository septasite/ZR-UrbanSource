#include "StdAfx.h"
#include "CompoundWindowCheckBox.h"

#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCompoundWindowCheckBox::CCompoundWindowCheckBox ()
	: m_pNormal( NULL )
	, m_pFlip( NULL )
	, m_pIcon( NULL )
	, m_pText( NULL )
	, m_bCHECKED( FALSE )
{
}

CCompoundWindowCheckBox::~CCompoundWindowCheckBox ()
{
}

void CCompoundWindowCheckBox::CreateSubControl()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	
	m_pNormal = new CUIControl;
	m_pNormal->CreateSub ( this, "COMPOUND_WINDOW_CHECKBOX_OFF" );
	m_pNormal->SetTransparentOption( TRUE );
	m_pNormal->SetVisibleSingle(FALSE);
	RegisterControl ( m_pNormal );
	
	m_pFlip = new CUIControl;
	m_pFlip->CreateSub ( this, "COMPOUND_WINDOW_CHECKBOX_ON" );
	m_pFlip->SetTransparentOption( TRUE );
	m_pFlip->SetVisibleSingle(TRUE);
	RegisterControl ( m_pFlip );

	/*m_pIcon = new CUIControl;
	m_pIcon->CreateSub ( this, "COMPOUND_WINDOW_ICON" );
	m_pIcon->SetTransparentOption( TRUE );
	m_pIcon->SetVisibleSingle(FALSE);
	RegisterControl ( m_pIcon );*/

	m_pText = new CBasicTextBox;
	m_pText->CreateSub ( this, "COMPOUND_WINDOW_MAIN_CHECK_TEXT_POS" );
	m_pText->SetFont ( pFont );
	m_pText->SetTextAlign ( TEXT_ALIGN_LEFT );	
	RegisterControl ( m_pText );
	
	m_pTextTitle = new CBasicTextBox;
	m_pTextTitle->CreateSub ( this, "COMPOUND_WINDOW_MAIN_CHECK_TEXT_TITLE_POS" );
	m_pTextTitle->SetFont ( pFont );
	m_pTextTitle->SetTextAlign ( TEXT_ALIGN_LEFT );	
	RegisterControl ( m_pTextTitle );

	ForceCheck();
}

void CCompoundWindowCheckBox::SetCheck()
{
	m_bCHECKED = !m_bCHECKED;

	if ( !m_bCHECKED )
	{
		m_pFlip->SetVisibleSingle(FALSE);
		m_pNormal->SetVisibleSingle(TRUE);
	}
	else
	{
		m_pFlip->SetVisibleSingle(TRUE);
		m_pNormal->SetVisibleSingle(FALSE);
	}
}

void CCompoundWindowCheckBox::ForceCheck()
{
	m_bCHECKED = TRUE;
	m_pFlip->SetVisibleSingle(TRUE);
	m_pNormal->SetVisibleSingle(FALSE);
}

void CCompoundWindowCheckBox::ForceUnCheck()
{
	m_bCHECKED = FALSE;
	m_pFlip->SetVisibleSingle(FALSE);
	m_pNormal->SetVisibleSingle(TRUE);
}

void CCompoundWindowCheckBox::SetText(CString strText, D3DCOLOR dwColor )
{
	m_pText->AddTextNoSplit( strText, dwColor );
	m_pIcon->SetVisibleSingle(TRUE);
}

int CCompoundWindowCheckBox::SetTextTitle(CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextTitle ) return m_pTextTitle->AddTextNoSplit( strText, dwColor );
	return -1;
}