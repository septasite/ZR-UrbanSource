#include "StdAfx.h"
#include "CTFTowerScoreSlot.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../GameTextControl.h"
#include "../UITextControl.h"
#include "GLogicData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFTowerScoreSlot::CCTFTowerScoreSlot () :
	m_pName( NULL )
	, m_pSchoolText( NULL )
	, m_pDamageSG( NULL )
	, m_pDamageMP( NULL )
	, m_pDamagePHX( NULL )
{
	for ( int i=0; i < 3; ++ i )
	{
		m_pSchool[i] = NULL;
	}
}

CCTFTowerScoreSlot::~CCTFTowerScoreSlot ()
{
}

void CCTFTowerScoreSlot::CreateSubControl ()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	m_pName = CreateStaticControl ( "CTF_TOWER_TEXT_BASE_TOWER", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X || TEXT_ALIGN_CENTER_Y );
	m_pSchoolText = CreateStaticControl ( "CTF_TOWER_TEXT_BASE_HOLDER_TEXT", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X  || TEXT_ALIGN_CENTER_Y );
	m_pDamageSG = CreateStaticControl ( "CTF_TOWER_TEXT_BASE_DAMAGE_SG", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X  || TEXT_ALIGN_CENTER_Y) ;
	m_pDamageMP = CreateStaticControl ( "CTF_TOWER_TEXT_BASE_DAMAGE_MP", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X || TEXT_ALIGN_CENTER_Y );
	m_pDamagePHX = CreateStaticControl ( "CTF_TOWER_TEXT_BASE_DAMAGE_PHX", "", pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X || TEXT_ALIGN_CENTER_Y );	

	CString strSchool[3] = 
	{
		"CTF_TOWER_RANKSLOT_IMAGE_SCHOOL0",
		"CTF_TOWER_RANKSLOT_IMAGE_SCHOOL1",
		"CTF_TOWER_RANKSLOT_IMAGE_SCHOOL2"
	};

	for ( int i = 0; i < 3; ++ i )
	{
		m_pSchool[i] = CreateControl( strSchool[i].GetString() );
	}
}


void CCTFTowerScoreSlot::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCTFTowerScoreSlot::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );
}

void CCTFTowerScoreSlot::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );
}

CUIControl*	CCTFTowerScoreSlot::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CCTFTowerScoreSlot::CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	pStaticText->SetText( szText, dwColor );
	return pStaticText;
}

void CCTFTowerScoreSlot::DataUpdate( std::string strNAME, int nSCHOOL, LONGLONG llDamageSG, LONGLONG llDamageMP, LONGLONG llDamagePHX )
{
	DataReset();

	if ( nSCHOOL >= 0 && nSCHOOL < 3 )
	{
		if ( m_pSchool[nSCHOOL] )
			m_pSchool[nSCHOOL]->SetVisibleSingle( TRUE );

		if ( m_pSchoolText )
		{
			m_pSchoolText->SetText( GLCONST_CHAR::strSCHOOLNAME[nSCHOOL].c_str(), NS_UITEXTCOLOR::WHITE );
		}
	}

	if ( m_pName )
	{
		m_pName->SetText( strNAME.c_str(), NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pDamageSG )
	{
		CString strTEXT;
		strTEXT.Format( "%I64d", llDamageSG );
		m_pDamageSG->SetText( strTEXT.GetString(), NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pDamageMP )
	{
		CString strTEXT;
		strTEXT.Format( "%I64d", llDamageMP );
		m_pDamageMP->SetText( strTEXT.GetString(), NS_UITEXTCOLOR::WHITE );
	}

	if ( m_pDamagePHX )
	{
		CString strTEXT;
		strTEXT.Format( "%I64d", llDamagePHX );
		m_pDamagePHX->SetText( strTEXT.GetString(), NS_UITEXTCOLOR::WHITE );
	}
}

void CCTFTowerScoreSlot::DataReset()
{
	for ( int i = 0; i < 3; ++ i )
	{
		if ( m_pSchool[i] )
			m_pSchool[i]->SetVisibleSingle( FALSE );
	}

	if ( m_pName )			m_pName->ClearText();
	if ( m_pSchoolText )	m_pSchoolText->ClearText();
	if ( m_pDamageSG )		m_pDamageSG->ClearText();
	if ( m_pDamageMP )		m_pDamageMP->ClearText();
	if ( m_pDamagePHX )		m_pDamagePHX->ClearText();
}