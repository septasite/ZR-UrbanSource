#include "StdAfx.h"
#include "CTFRankSelf.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../GameTextControl.h"
#include "../UITextControl.h"
#include "../BasicLineBox.h"

#include "../RanClientLib/G-Logic/GLCaptureTheField/GLCaptureTheFieldData.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFRankSelf::CCTFRankSelf () :
	m_pRankNum( NULL )
	, m_pRankName( NULL )
	, m_pRankDamage( NULL )
	, m_pRankKill( NULL )
	, m_pRankDeath( NULL )
{
	for ( int i=0; i < 3; ++ i )
	{
		m_pRankSchool[i] = NULL;
	}

	for ( int i=0; i < GLCI_NUM_NEWEST; ++ i )
	{
		m_pRankClass[i] = NULL;
	}
}

CCTFRankSelf::~CCTFRankSelf ()
{
}

void CCTFRankSelf::CreateSubControl ()
{
	CBasicLineBox* pBasicLineBox = new CBasicLineBox;
	pBasicLineBox->CreateSub( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pBasicLineBox->CreateBaseBoxQuestList( "CTF_RESULT_LINE" );
	RegisterControl ( pBasicLineBox );

	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	m_pRankNum = CreateStaticControl ( "CTF_RESULT_TEXT_BASE_RANK", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X || TEXT_ALIGN_CENTER_Y );
	m_pRankName = CreateStaticControl ( "CTF_RESULT_TEXT_BASE_NAME", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X  || TEXT_ALIGN_CENTER_Y );
	m_pRankDamage = CreateStaticControl ( "CTF_RESULT_TEXT_BASE_DAMAGE", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X  || TEXT_ALIGN_CENTER_Y) ;
	m_pRankKill = CreateStaticControl ( "CTF_RESULT_TEXT_BASE_KILL", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X || TEXT_ALIGN_CENTER_Y );
	m_pRankDeath = CreateStaticControl ( "CTF_RESULT_TEXT_BASE_DEATH", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X || TEXT_ALIGN_CENTER_Y );	

	CString strSchool[3] = 
	{
		"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL0",
		"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL1",
		"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL2"
	};

	CString strClass[GLCI_NUM_NEWEST] = 
	{
		"CTF_RESULT_RANKSLOT_IMAGE_BRAWLER_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SWORDSMAN_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ARCHER_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SHAMAN_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_EXTREME_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_EXTREME_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_BRAWLER_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SWORDSMAN_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ARCHER_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SHAMAN_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SCIENTIST_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_SCIENTIST_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ASSASSIN_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_ASSASSIN_FEMALE",
		"CTF_RESULT_RANKSLOT_IMAGE_TRICKER_MALE",
		"CTF_RESULT_RANKSLOT_IMAGE_TRICKER_FEMALE",
	};	

	for ( int i = 0; i < 3; ++ i )
	{
		m_pRankSchool[i] = CreateControl( strSchool[i].GetString() );
	}
							
	for ( int i=0; i < GLCI_NUM_NEWEST; ++ i )
	{
		m_pRankClass[i] = CreateControl( strClass[i].GetString() );;
	}
}


void CCTFRankSelf::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCTFRankSelf::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );
}

void CCTFRankSelf::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );
}

CUIControl*	CCTFRankSelf::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CCTFRankSelf::CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	pStaticText->SetText( szText, dwColor );
	return pStaticText;
}

void CCTFRankSelf::DataUpdate( int nNUM, std::string strNAME, int nSCHOOL, int nCLASS, LONGLONG llDAMAGE, int nKILL, int nDEATH )
{
	if ( nSCHOOL < 0 || nSCHOOL >=3 )	return;
	if ( nCLASS < 0 || nCLASS >=GLCI_NUM_NEWEST )	return;

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

	if ( m_pRankDamage )
	{
		CString strTEXT;
		strTEXT.Format( "%I64d", llDAMAGE );
		m_pRankDamage->SetText( strTEXT.GetString(), NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pRankKill )
	{
		CString strTEXT;
		strTEXT.Format( "%d", nKILL );
		m_pRankKill->SetText( strTEXT.GetString(), NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pRankDeath )
	{
		CString strTEXT;
		strTEXT.Format( "%d", nDEATH );
		m_pRankDeath->SetText( strTEXT.GetString(), NS_UITEXTCOLOR::WHITE );
	}
}

void CCTFRankSelf::DataReset()
{
	for ( int i = 0; i < 3; ++ i )
	{
		if ( m_pRankSchool[i] )
			m_pRankSchool[i]->SetVisibleSingle( FALSE );
	}

	for ( int i=0; i < GLCI_NUM_NEWEST; ++ i )
	{
		if ( m_pRankClass[i] )
			m_pRankClass[i]->SetVisibleSingle( FALSE );
	}

	if ( m_pRankNum )		m_pRankNum->ClearText();
	if ( m_pRankName )		m_pRankName->ClearText();
	if ( m_pRankDamage )	m_pRankDamage->ClearText();
	if ( m_pRankKill )		m_pRankKill->ClearText();
	if ( m_pRankDeath )		m_pRankDeath->ClearText();
}

void CCTFRankSelf::RefreshRanking()
{
	DataReset();

	const SCTF_RANK_SELF& sMyRank = GLGaeaClient::GetInstance().m_CaptureTheFieldSelfRank;

	if ( sMyRank.bVALID )
	{
		CString strNAME = GLGaeaClient::GetInstance().GetCharacter()->m_szName;
		DataUpdate( sMyRank.wRanking, strNAME.GetString(), sMyRank.cSCHOOL, sMyRank.cCLASS, sMyRank.llDAMAGE, sMyRank.wKillNum, sMyRank.wDeathNum );
	}
}