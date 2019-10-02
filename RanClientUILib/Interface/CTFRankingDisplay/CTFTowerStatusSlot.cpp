#include "StdAfx.h"
#include "CTFTowerStatusSlot.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../GameTextControl.h"
#include "../UITextControl.h"
#include "GLogicData.h"
#include "../BasicLineBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFTowerStatusSlot::CCTFTowerStatusSlot () :
	m_pName( NULL )
{
	for ( int i=0; i < 3; ++ i )
	{
		m_pSchool[i] = NULL;
	}
}

CCTFTowerStatusSlot::~CCTFTowerStatusSlot ()
{
}

void CCTFTowerStatusSlot::CreateSubControl ()
{
	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CTF_TOWER_SLOT_LINE" );
	RegisterControl ( pBasicLineBox );

	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	m_pName = CreateStaticControl ( "CTF_TOWER_SLOT_TEXT", "test", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_Y );
	
	CString strSchool[3] = 
	{
		"CTF_TOWER_SLOT_IMAGE_SCHOOL0",
		"CTF_TOWER_SLOT_IMAGE_SCHOOL1",
		"CTF_TOWER_SLOT_IMAGE_SCHOOL2"
	};

	for ( int i = 0; i < 3; ++ i )
	{
		m_pSchool[i] = CreateControl( strSchool[i].GetString() );
	}
}


void CCTFTowerStatusSlot::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCTFTowerStatusSlot::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );
}

void CCTFTowerStatusSlot::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );
}

CUIControl*	CCTFTowerStatusSlot::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CCTFTowerStatusSlot::CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	pStaticText->SetText( szText, dwColor );
	return pStaticText;
}

void CCTFTowerStatusSlot::DataUpdate( std::string strNAME, int nSCHOOL )
{
	DataReset();

	if ( nSCHOOL >= 0 && nSCHOOL < 3 )
	{
		if ( m_pSchool[nSCHOOL] )
			m_pSchool[nSCHOOL]->SetVisibleSingle( TRUE );
	}

	if ( m_pName )
	{
		m_pName->SetText( strNAME.c_str(), NS_UITEXTCOLOR::WHITE );
	}

}

void CCTFTowerStatusSlot::DataReset()
{
	for ( int i = 0; i < 3; ++ i )
	{
		if ( m_pSchool[i] )
			m_pSchool[i]->SetVisibleSingle( FALSE );
	}

	if ( m_pName )			m_pName->ClearText();
}