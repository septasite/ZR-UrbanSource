#include "StdAfx.h"
#include "PartySlotDisplay.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"
#include "../RanClientUILib/Interface/BasicLineBox.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"

#include "../../EngineLib/DxCommon/DxFontMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartySlotDisplay::CPartySlotDisplay ()
{
}

CPartySlotDisplay::~CPartySlotDisplay ()
{
}

void CPartySlotDisplay::CreateSubControl ()
{
	CBasicLineBox* pLineBoxCombo = new CBasicLineBox;
	pLineBoxCombo->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBoxCombo->CreateBaseBoxMiniParty ( "PARTYDISPLAY_SLOT_BACK_HIGH" );
	RegisterControl ( pLineBoxCombo );

	CBasicLineBox* pLineBoxComboLow = new CBasicLineBox;
	pLineBoxComboLow->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBoxComboLow->CreateBaseBoxMiniParty ( "PARTYDISPLAY_SLOT_BACK_LOW" );
	RegisterControl ( pLineBoxComboLow );
}

CUIControl*	CPartySlotDisplay::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CPartySlotDisplay::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}