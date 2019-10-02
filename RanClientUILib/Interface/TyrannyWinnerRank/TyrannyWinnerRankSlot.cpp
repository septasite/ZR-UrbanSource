#include "StdAfx.h"
#include "TyrannyWinnerRankSlot.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../GameTextControl.h"
#include "../UITextControl.h"
#include "../BasicLineBox.h"
#include "../../RanClientLib/G-Logic/GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTyrannyWinnerRankSlot::CTyrannyWinnerRankSlot () :
	m_pRankNum( NULL ),
	m_pRankName( NULL ),
	m_pSelf( NULL )
{
	for ( int i=0; i<3; ++i )
	{
		m_pRankSchool[i] = NULL;
	}

	for ( int i=0; i < GLCI_NUM_NEWSEX; ++ i )
	{
		m_pRankClass[i] = NULL;
	}
}

CTyrannyWinnerRankSlot::~CTyrannyWinnerRankSlot ()
{
}

void CTyrannyWinnerRankSlot::CreateSubControl ()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicLineBox* pLineBox = new CBasicLineBox;
	pLineBox->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxQuestList( "TW_RANKSLOT_LINE" );
	RegisterControl ( pLineBox );

	m_pSelf = new CUIControl;
	m_pSelf->CreateSub ( this, "TW_RANKSLOT_SELF", UI_FLAG_DEFAULT );	
	m_pSelf->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pSelf );

	CString strSchool[3] = 
	{
		"TW_RANKSLOT_IMAGE_SCHOOL0",
		"TW_RANKSLOT_IMAGE_SCHOOL1",
		"TW_RANKSLOT_IMAGE_SCHOOL2"
	};

	CString strClass[GLCI_NUM_NEWSEX] = 
	{
		"TW_RANKSLOT_IMAGE_BRAWLER_MALE",
		"TW_RANKSLOT_IMAGE_SWORDSMAN_MALE",
		"TW_RANKSLOT_IMAGE_ARCHER_FEMALE",
		"TW_RANKSLOT_IMAGE_SHAMAN_FEMALE",
		"TW_RANKSLOT_IMAGE_EXTREME_MALE",
		"TW_RANKSLOT_IMAGE_EXTREME_FEMALE",
		"TW_RANKSLOT_IMAGE_BRAWLER_FEMALE",
		"TW_RANKSLOT_IMAGE_SWORDSMAN_FEMALE",
		"TW_RANKSLOT_IMAGE_ARCHER_MALE",
		"TW_RANKSLOT_IMAGE_SHAMAN_MALE",
	};	

	for ( int i = 0; i < 3; ++ i )
	{
		m_pRankSchool[i] = CreateControl( strSchool[i].GetString() );
	}

	for ( int i=0; i < GLCI_NUM_NEWSEX; ++ i )
	{
		m_pRankClass[i] = CreateControl( strClass[i].GetString() );;
	}

	m_pRankNum = CreateStaticControl ( "TW_RANKSLOT_NUM_TEXT", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pRankName = CreateStaticControl ( "TW_RANKSLOT_NAME", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
}

CUIControl*	CTyrannyWinnerRankSlot::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CTyrannyWinnerRankSlot::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CTyrannyWinnerRankSlot::DataUpdate( int nNUM, std::string strNAME, int nSCHOOL, int nCLASS,  DWORD dwCHARID /*= UINT_MAX*/ )
{
	DataReset();

	if ( nSCHOOL < 0 || nSCHOOL >=3 )	return;
	if ( nCLASS < 0 || nCLASS >=GLCI_NUM_NEWSEX )	return;

	if ( m_pRankSchool[nSCHOOL] )
		m_pRankSchool[nSCHOOL]->SetVisibleSingle( TRUE );

	if ( m_pRankClass[nCLASS] )
		m_pRankClass[nCLASS]->SetVisibleSingle( TRUE );

	if ( m_pRankNum )
	{
		CString strTEXT;
		strTEXT.Format( "%d", nNUM );
		m_pRankNum->SetText( strTEXT.GetString(), NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pRankName )
	{
		m_pRankName->SetText( strNAME.c_str(), NS_UITEXTCOLOR::WHITE );
	}


	if ( dwCHARID != UINT_MAX )
	{
		DWORD dwCharID = GLGaeaClient::GetInstance().GetCharacter()->m_dwCharID;

		BOOL bSELF = ( dwCHARID == dwCharID );

		if ( m_pSelf )
			m_pSelf->SetVisibleSingle( bSELF );
	}
}

void CTyrannyWinnerRankSlot::DataReset()
{
	for ( int i = 0; i < 3; ++ i )
	{
		if ( m_pRankSchool[i] )
			m_pRankSchool[i]->SetVisibleSingle( FALSE );
	}

	for ( int i=0; i < GLCI_NUM_NEWSEX; ++ i )
	{
		if ( m_pRankClass[i] )
			m_pRankClass[i]->SetVisibleSingle( FALSE );
	}

	if ( m_pRankNum )	m_pRankNum->ClearText();
	if ( m_pRankName )	m_pRankName->ClearText();
}