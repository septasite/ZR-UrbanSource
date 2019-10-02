#include "StdAfx.h"
#include "CTFRankPlayerBase.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../GameTextControl.h"
#include "../UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFRankPlayerBase::CCTFRankPlayerBase () /*:*/
{
}

CCTFRankPlayerBase::~CCTFRankPlayerBase ()
{
}

void CCTFRankPlayerBase::CreateSubControl ()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CreateStaticControl ( "CTF_RESULT_TEXT_BASE_RANK", (char*)ID2GAMEWORD ( "CTF_RESULT_TEXT_BASE", 0 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_RESULT_TEXT_BASE_SCHOOL", (char*)ID2GAMEWORD ( "CTF_RESULT_TEXT_BASE", 1 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_RESULT_TEXT_BASE_CLASS", (char*)ID2GAMEWORD ( "CTF_RESULT_TEXT_BASE", 2 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_RESULT_TEXT_BASE_NAME", (char*)ID2GAMEWORD ( "CTF_RESULT_TEXT_BASE", 3 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_RESULT_TEXT_BASE_DAMAGE", (char*)ID2GAMEWORD ( "CTF_RESULT_TEXT_BASE", 4 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_RESULT_TEXT_BASE_KILL", (char*)ID2GAMEWORD ( "CTF_RESULT_TEXT_BASE", 5 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );
	CreateStaticControl ( "CTF_RESULT_TEXT_BASE_DEATH", (char*)ID2GAMEWORD ( "CTF_RESULT_TEXT_BASE", 6 ), pFont8, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_CENTER_X );	
}


void CCTFRankPlayerBase::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCTFRankPlayerBase::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );
}

void CCTFRankPlayerBase::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

}

CBasicTextBox* CCTFRankPlayerBase::CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	pStaticText->SetText( szText, dwColor );
	return pStaticText;
}
