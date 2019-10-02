#include "StdAfx.h"

#include "killTimeUnit.h"
#include "InnerInterface.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "d3dfont.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CkillTimeUnit::CkillTimeUnit ()
: m_pstrName( NULL )
,m_pKillstrName( NULL )
,m_pStrSlayed( NULL )
{
}

CkillTimeUnit::~CkillTimeUnit ()
{
}

void CkillTimeUnit::CreateSubControl (int nClassType,int m_nKillClassType , int nSchoolKilled , int nSchoolKiller)
{
	
	{
		CBasicLineBoxEx* m_pLineBoxBack = new CBasicLineBoxEx;
		m_pLineBoxBack->CreateSub ( this, "BASIC_LINE_BOX_EX_ESC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pLineBoxBack->CreateBaseBoxESCMenu ( "KILL_DISPLAY_BACK" );
		m_pLineBoxBack->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pLineBoxBack );
	}
	CString	strKillDisplayClass[GLCI_NUM_NEWEST] = 
	{
		"KILLDISPLAY_FIGHTER_M",
		"KILLDISPLAY_ARMS_M",
		"KILLDISPLAY_ARCHER_W",
		"KILLDISPLAY_SPIRIT_W",
		"KILLDISPLAY_EXTREME_M",
		"KILLDISPLAY_EXTREME_W",
		"KILLDISPLAY_FIGHTER_W",
		"KILLDISPLAY_ARMS_W",
		"KILLDISPLAY_ARCHER_M",
		"KILLDISPLAY_SPIRIT_M",
		"KILLDISPLAY_GUNNER_M",
		"KILLDISPLAY_GUNNER_W",
		"KILLDISPLAY_ASSASSIN_M",
		"KILLDISPLAY_ASSASSIN_W"	};

	CreateControl ( strKillDisplayClass[nClassType].GetString () );

	CString	strKillDisplaySchool[3] = 
	{
		"KILLDISPLAY_SCHOOL_0",
		"KILLDISPLAY_SCHOOL_1",
		"KILLDISPLAY_SCHOOL_2"	};

	CreateControl ( strKillDisplaySchool[nSchoolKilled].GetString () );

	CString	m_strKillDisplayClass[GLCI_NUM_NEWEST] = 
	{
		"MKILLDISPLAY_FIGHTER_M",
		"MKILLDISPLAY_ARMS_M",
		"MKILLDISPLAY_ARCHER_W",
		"MKILLDISPLAY_SPIRIT_W",
		"MKILLDISPLAY_EXTREME_M",
		"MKILLDISPLAY_EXTREME_W",
		"MKILLDISPLAY_FIGHTER_W",
		"MKILLDISPLAY_ARMS_W",
		"MKILLDISPLAY_ARCHER_M",
		"MKILLDISPLAY_SPIRIT_M",
		"MKILLDISPLAY_GUNNER_M",
		"MKILLDISPLAY_GUNNER_W",
		"MKILLDISPLAY_ASSASSIN_M",
		"MKILLDISPLAY_ASSASSIN_W"	};

	CreateControl ( m_strKillDisplayClass[m_nKillClassType].GetString () );

	CString	m_strKillDisplaySchool[3] = 
	{
		"MKILLDISPLAY_SCHOOL_0",
		"MKILLDISPLAY_SCHOOL_1",
		"MKILLDISPLAY_SCHOOL_2"	};

	CreateControl ( m_strKillDisplaySchool[nSchoolKiller].GetString () );


CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	//m_pKillstrName = CreateStaticControl ( "NAME_KILL_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
	//m_pKillstrName->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );

	CBasicTextBox* pKillstrName = new CBasicTextBox;
	pKillstrName->CreateSub( this, "NAME_KILL_TEXT" );
	pKillstrName->SetFont( pFont8 );
	pKillstrName->SetTextAlign( TEXT_ALIGN_RIGHT );
	pKillstrName->SetUseRender( TRUE );
	pKillstrName->SetDiffuseAlpha( 0 );
	pKillstrName->SetVisibleSingle( FALSE );
	RegisterControl( pKillstrName );
	m_pKillstrName = pKillstrName;

	CBasicTextBox* pstrName = new CBasicTextBox;
	pstrName->CreateSub( this, "M_NAME_KILL_TEXT" );
	pstrName->SetFont( pFont8 );
	pstrName->SetTextAlign( TEXT_ALIGN_LEFT );
	pstrName->SetUseRender( TRUE );
	pstrName->SetDiffuseAlpha( 0 );
	pstrName->SetVisibleSingle( FALSE );
	RegisterControl( pstrName );
	m_pstrName = pstrName;

	CBasicTextBox* pstrSlayed = new CBasicTextBox;
	pstrSlayed->CreateSub( this, "SLAYE_KILL_TEXT" );
	pstrSlayed->SetFont( pFont8 );
	pstrSlayed->SetTextAlign( TEXT_ALIGN_CENTER_X );
	pstrSlayed->SetUseRender( TRUE );
	pstrSlayed->SetDiffuseAlpha( 0 );
	pstrSlayed->SetVisibleSingle( FALSE );
	RegisterControl( pstrSlayed );
	m_pStrSlayed = pstrSlayed;

	//m_pstrName = CreateStaticControl ( "M_NAME_KILL_TEXT", pFont8, NS_UITEXTCOLOR::DEFAULT, TEXT_ALIGN_LEFT );
	//m_pstrName->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );

}

CUIControl*	CkillTimeUnit::CreateControl ( const char* szControl )
{
	pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

void CkillTimeUnit::SetLeftTime ( const float& fLeftTime )
{
	m_fLEFT_TIME = fLeftTime;
}

void CkillTimeUnit::Setkill ( const float& fLifeTime, const CString& strkillName , const CString& strMKillName, const CString& strSlayed )
{
	m_fLIFE_TIME = fLifeTime;

	m_pKillstrName->SetVisibleSingle(TRUE);
	m_pKillstrName->SetOneLineText(strMKillName,NS_UITEXTCOLOR::WHITE );
	m_pstrName->SetVisibleSingle(TRUE);
	m_pstrName->SetOneLineText(strkillName,NS_UITEXTCOLOR::WHITE );
	m_pStrSlayed->SetVisibleSingle(TRUE);
	m_pStrSlayed->SetOneLineText(strSlayed,NS_UITEXTCOLOR::GOLD);
}

void CkillTimeUnit::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

}