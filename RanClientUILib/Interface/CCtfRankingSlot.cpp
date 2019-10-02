#include "StdAfx.h"
#include "CCtfRankingSlot.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"
#include "InnerInterface.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"

#include "../EngineLib/DxCommon/DxFontMan.h"
#include "BasicTextBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCtfRankingSlot::CCtfRankingSlot ()
	:	m_pCTFBaseRank			( NULL )
	,	m_pCTFBaseCharName		( NULL )
	,	m_pCTFBaseKill			( NULL )
	,	m_pCTFBaseDeath			( NULL )
	,	m_pCTFBaseHeal			( NULL )
	,	m_pCTFBaseResu			( NULL )
	,	m_pCTFBaseContrib		( NULL )
	,	m_pCTFBaseDamage		( NULL )
{
	memset( m_pSchoolMark, 0, sizeof ( CUIControl* ) * nSCHOOLMARK );
	memset ( m_pClassImg, 0, sizeof( CUIControl* ) * GLCI_NUM_NEWEST-2 );
}

CCtfRankingSlot::~CCtfRankingSlot ()
{
}

void CCtfRankingSlot::CreateSubControl ( D3DCOLOR dwColor )
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );
	int	nTextAlign = TEXT_ALIGN_CENTER_X;

	{
		m_pCTFBaseRank		= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_RANK", pFont, dwColor, nTextAlign );
		m_pCTFBaseCharName	= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_NAME", pFont, dwColor, nTextAlign );
		m_pCTFBaseKill		= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_KILL", pFont, dwColor, nTextAlign );
		m_pCTFBaseDeath		= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_DEATH", pFont, dwColor, nTextAlign );
		m_pCTFBaseHeal		= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_HEAL", pFont, dwColor, nTextAlign );
		m_pCTFBaseResu		= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_REBIRTH", pFont, dwColor, nTextAlign );
		m_pCTFBaseContrib	= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_CONTRIBUTION", pFont, dwColor, nTextAlign );
		m_pCTFBaseDamage	= CreateStaticControl ( "CTF_RESULT_RANKSLOT_TEXT_BASE_DAMAGE", pFont, dwColor, nTextAlign );
	}

	{
		CString strSchoolMark[] = 
		{
			"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL0",
			"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL1",
			"CTF_RESULT_RANKSLOT_IMAGE_SCHOOL2"
		};

		for ( int i = 0; i < nSCHOOLMARK; ++i )
		{
			m_pSchoolMark[i] = CreateControl ( strSchoolMark[i].GetString(), nTextAlign );
			m_pSchoolMark[i]->SetVisibleSingle ( FALSE );
		}
	}

	CString strTemp;
	for ( int i = 0 ; i < GLCI_NUM_NEWEST-2; ++i ) 
	{
		strTemp.Format ( "CTF_RESULT_ICON_CLASS_IMAGE%d",i); 	
		m_pClassImg[i] = new CUIControl;
		m_pClassImg[i]->CreateSub ( this, strTemp, UI_FLAG_DEFAULT, ICON_CLASS_IMAGE0 + i );	
		m_pClassImg[i]->SetVisibleSingle ( FALSE );
		m_pClassImg[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_pClassImg[i] );
	}
	
}

CUIControl*	CCtfRankingSlot::CreateControl ( char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CUIControl*	CCtfRankingSlot::CreateControl ( const char* szControl, WORD wAlignFlag )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, wAlignFlag );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBoxEx* CCtfRankingSlot::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBoxEx* pStaticText = new CBasicTextBoxEx;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CCtfRankingSlot::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCtfRankingSlot::Init( WORD wRank, WORD wSchool, DWORD dwClass, const CString& strName, DWORD dwDamage, DWORD dwHeal, DWORD dwKill, DWORD dwDeath, WORD wResu, bool bMyRank )
{
	D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
	if(bMyRank) dwColor = NS_UITEXTCOLOR::GREENYELLOW;

	m_pCTFBaseRank->ClearText();
	m_pCTFBaseCharName->ClearText();
	m_pCTFBaseDamage->ClearText();
	m_pCTFBaseHeal->ClearText();
	m_pCTFBaseKill->ClearText();
	m_pCTFBaseDeath->ClearText();
	m_pCTFBaseResu->ClearText();
	m_pCTFBaseContrib->ClearText();

	for(int i=0;i<nSCHOOLMARK;i++)
		m_pSchoolMark[i]->SetVisibleSingle(FALSE);
	for ( int i = 0 ; i < GLCI_NUM_NEWEST-2; ++i ) 
		m_pClassImg[i]->SetVisibleSingle(FALSE);

	CString strTemp;
	strTemp.Format("%d",wRank);

	m_pCTFBaseRank->SetText(strTemp, dwColor);
	m_pCTFBaseCharName->SetText(strName, dwColor);

	if( dwDamage == 0 )	m_pCTFBaseDamage->SetText("-", dwColor);
	else 
	{
		strTemp.Format("%d",dwDamage);	
		m_pCTFBaseDamage->SetText(strTemp, dwColor);
	}

	if( dwHeal == 0 )	m_pCTFBaseHeal->SetText("-", dwColor);
	else 
	{
		strTemp.Format("%d",dwHeal);	
		m_pCTFBaseHeal->SetText(strTemp, dwColor);
	}

	if( dwKill == 0 )	m_pCTFBaseKill->SetText("-", dwColor);
	else 
	{
		strTemp.Format("%d",dwKill);	
		m_pCTFBaseKill->SetText(strTemp, dwColor);
	}
	
	if( dwDeath == 0 )	m_pCTFBaseDeath->SetText("-", dwColor);
	else 
	{
		strTemp.Format("%d",dwDeath);	
		m_pCTFBaseDeath->SetText(strTemp, dwColor);
	}

	if( wResu == 0 )	m_pCTFBaseResu->SetText("-", dwColor);
	else 
	{
		strTemp.Format("%d",wResu);		
		m_pCTFBaseResu->SetText(strTemp, dwColor);
	}

	float fKDR1 = 0.0f;
	fKDR1 = (float) ( dwKill + wResu ) / ( max( 1,dwDeath ) );
	strTemp.Format("%2.2f:1",fKDR1);		
	m_pCTFBaseContrib->SetText(strTemp, dwColor);

	m_pSchoolMark[wSchool]->SetVisibleSingle ( TRUE );
	m_pClassImg[dwClass]->SetVisibleSingle ( TRUE );
}