#include "StdAfx.h"
#include "CTFTowerScoreBase.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../GameTextControl.h"
#include "../UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFTowerScoreBase::CCTFTowerScoreBase () /*:*/
{
}

CCTFTowerScoreBase::~CCTFTowerScoreBase ()
{
}

void CCTFTowerScoreBase::CreateSubControl ()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CreateStaticControl ( "CTF_TOWER_TEXT_BASE_TOWER", (char*)ID2GAMEWORD ( "CTF_TOWER_TEXT_BASE", 0 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_TOWER_TEXT_BASE_HOLDER", (char*)ID2GAMEWORD ( "CTF_TOWER_TEXT_BASE", 1 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_TOWER_TEXT_BASE_DAMAGE_SG", (char*)ID2GAMEWORD ( "CTF_TOWER_TEXT_BASE", 2 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_TOWER_TEXT_BASE_DAMAGE_MP", (char*)ID2GAMEWORD ( "CTF_TOWER_TEXT_BASE", 3 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );	
	CreateStaticControl ( "CTF_TOWER_TEXT_BASE_DAMAGE_PHX", (char*)ID2GAMEWORD ( "CTF_TOWER_TEXT_BASE", 4 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );	
}


void CCTFTowerScoreBase::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCTFTowerScoreBase::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );
}

void CCTFTowerScoreBase::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

}

CBasicTextBox* CCTFTowerScoreBase::CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	pStaticText->SetText( szText, dwColor );
	return pStaticText;
}
