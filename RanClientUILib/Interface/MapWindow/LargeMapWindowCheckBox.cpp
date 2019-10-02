#include "StdAfx.h"
#include "LargeMapWindowCheckBox.h"

#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLargeMapWindowCheckBox::CLargeMapWindowCheckBox ():
	m_pNormal(NULL),
	m_pFlip(NULL),
	m_pIcon(NULL),
	m_pText(NULL),
	m_bCHECKED(FALSE)
{
}

CLargeMapWindowCheckBox::~CLargeMapWindowCheckBox ()
{
}

void CLargeMapWindowCheckBox::CreateSubControl()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, _DEFAULT_FONT_SHADOW_FLAG );
	
	m_pNormal = new CUIControl;
	m_pNormal->CreateSub ( this, "MAP_WINDOW_CHECKBOX_OFF" );
	m_pNormal->SetTransparentOption( TRUE );
	m_pNormal->SetVisibleSingle(FALSE);
	RegisterControl ( m_pNormal );
	
	m_pFlip = new CUIControl;
	m_pFlip->CreateSub ( this, "MAP_WINDOW_CHECKBOX_ON" );
	m_pFlip->SetTransparentOption( TRUE );
	m_pFlip->SetVisibleSingle(TRUE);
	RegisterControl ( m_pFlip );

	
	m_pIcon = new CUIControl;
	m_pIcon->CreateSub ( this, "MAP_WINDOW_CROWLIST_ICON" );
	m_pIcon->SetTransparentOption( TRUE );
	m_pIcon->SetVisibleSingle(FALSE);
	RegisterControl ( m_pIcon );

	m_pText = new CBasicTextBox;
	m_pText->CreateSub ( this, "MAP_WINDOW_MAIN_CHECK_TEXT_POS" );
	m_pText->SetFont ( pFont );
	m_pText->SetTextAlign ( TEXT_ALIGN_LEFT );	
	RegisterControl ( m_pText );
	
	m_pTextTitle = new CBasicTextBox;
	m_pTextTitle->CreateSub ( this, "MAP_WINDOW_MAIN_CHECK_TEXT_TITLE_POS" );
	m_pTextTitle->SetFont ( pFont );
	m_pTextTitle->SetTextAlign ( TEXT_ALIGN_LEFT );	
	RegisterControl ( m_pTextTitle );

	m_bCHECKED = TRUE;
}

void CLargeMapWindowCheckBox::SetCheck()
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

void CLargeMapWindowCheckBox::ForceCheck()
{
	m_bCHECKED = TRUE;
	m_pFlip->SetVisibleSingle(TRUE);
	m_pNormal->SetVisibleSingle(FALSE);
}

void CLargeMapWindowCheckBox::ForceUnCheck()
{
	m_bCHECKED = FALSE;
	m_pFlip->SetVisibleSingle(FALSE);
	m_pNormal->SetVisibleSingle(TRUE);
}

void CLargeMapWindowCheckBox::SetText(CString strText, D3DCOLOR dwColor, SNATIVEID sNativeID )
{
	m_sNativeID = sNativeID;
	m_pText->AddTextNoSplit( strText, dwColor );
	m_pIcon->SetVisibleSingle(TRUE);
}

int CLargeMapWindowCheckBox::SetTextTitle(CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextTitle ) return m_pTextTitle->AddTextNoSplit( strText, dwColor );
	return -1;
}