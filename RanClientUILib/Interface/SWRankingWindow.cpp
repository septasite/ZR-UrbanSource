#include "StdAfx.h"
#include "SWRankingWindow.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "InnerInterface.h"
#include "GLGaeaClient.h"
#include "BasicLineBox.h"
#include "GLChar.h"
#include "SWRankingSlot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSWRankingWindow::CSWRankingWindow ():
	m_pRank ( NULL ),
	m_pName ( NULL ),
	m_pKill ( NULL ),
	m_pDeath ( NULL )
{
	memset( m_pSWRankingSlot, 0, sizeof(m_pSWRankingSlot) );
}

CSWRankingWindow::~CSWRankingWindow ()
{
}

void CSWRankingWindow::CreateSubControl ()
{	
	int nTextAlign = TEXT_ALIGN_LEFT;
	D3DCOLOR dwFontColor = NS_UITEXTCOLOR::DEFAULT;

	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, _DEFAULT_FONT_SHADOW_FLAG );

	m_bg_white = new CUIControl;
	m_bg_white->CreateSub ( this, "SW_RANKING_WINDOW_REGION", UI_FLAG_DEFAULT);	
	m_bg_white->SetVisibleSingle ( TRUE );
	RegisterControl ( m_bg_white );

	m_pBackLine1 = new CBasicLineBox;
	m_pBackLine1->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pBackLine1->CreateBaseBoxSkill ( "SW_RANKING_WINDOW_SLOT_BACK" );
	RegisterControl ( m_pBackLine1 );

	CBasicTextBox* pTextBox = NULL;
	pTextBox = CreateStaticControl ( "SW_RANKING_WINDOW_RANK_TEXT", pFont, NS_UITEXTCOLOR::DEFAULT, nTextAlign );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ("SW_RANKING_STATIC", 0)  );
	
	pTextBox = CreateStaticControl ( "SW_RANKING_WINDOW_NAME_TEXT", pFont, NS_UITEXTCOLOR::DEFAULT, nTextAlign );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ("SW_RANKING_STATIC", 3)  );

	pTextBox = CreateStaticControl ( "SW_RANKING_WINDOW_KILL_TEXT", pFont, NS_UITEXTCOLOR::DEFAULT, nTextAlign );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ("SW_RANKING_STATIC", 4)  );

	pTextBox = CreateStaticControl ( "SW_RANKING_WINDOW_DEATH_TEXT", pFont, NS_UITEXTCOLOR::DEFAULT, nTextAlign );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ("SW_RANKING_STATIC", 5)  );

	m_pRank = new CBasicTextBox;
	m_pRank->CreateSub ( this, "SW_RANKING_RANK_TEXT" );
	m_pRank->SetFont ( pFont );
	m_pRank->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pRank );	

	m_pName = new CBasicTextBox;
	m_pName->CreateSub ( this, "SW_RANKING_NAME_TEXT" );
	m_pName->SetFont ( pFont );
	m_pName->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pName ); 

	m_pKill = new CBasicTextBox;
	m_pKill->CreateSub ( this, "SW_RANKING_KILL_TEXT" );
	m_pKill->SetFont ( pFont );
	m_pKill->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pKill );	

	m_pDeath = new CBasicTextBox;
	m_pDeath->CreateSub ( this, "SW_RANKING_DEATH_TEXT" );
	m_pDeath->SetFont ( pFont );
	m_pDeath->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pDeath );

	/*m_pDWRankingText = new CBasicTextBox;
	m_pDWRankingText->CreateSub ( this, "DW_RANKING_WINDOW_TEXT" );
	m_pDWRankingText->SetFont ( pFont );
	m_pDWRankingText->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pDWRankingText );	*/

	CString strRankingKeyword[10] = 
	{
		"SW_RANKING_SLOT_01",
		"SW_RANKING_SLOT_02",
		"SW_RANKING_SLOT_03",
		"SW_RANKING_SLOT_04",
		"SW_RANKING_SLOT_05",
		"SW_RANKING_SLOT_06",
		"SW_RANKING_SLOT_07",
		"SW_RANKING_SLOT_08",
		"SW_RANKING_SLOT_09",
		"SW_RANKING_SLOT_10",
	};

	for ( int i = 0; i < 10; i++ )
	{
		CSWRankingSlot* pSWRankingSlot = new CSWRankingSlot;
		pSWRankingSlot->CreateSub ( this, strRankingKeyword[i].GetString (), UI_FLAG_DEFAULT, SW_RANKING_SLOT_01 + i );
		pSWRankingSlot->CreateSubControl ();
		RegisterControl ( pSWRankingSlot );
		m_pSWRankingSlot[i] = pSWRankingSlot;
	}
}

void CSWRankingWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if( !IsVisible() )	return ;
	int nRankNum = GLGaeaClient::GetInstance().m_vecSwPRank.size();
	/*if ( !m_pDWRankingText ) return;

	m_pDWRankingText->ClearText();
	
	int nRankNum = GLGaeaClient::GetInstance().m_vecDWRank.size();

	CString strKill;
	CString strDeath;
	CString strRank;
	CString strName;

	DW_RANK_VEC& vecDWRank = GLGaeaClient::GetInstance().m_vecDWRank;

	/*for ( int i = 0; i < nRankNum; ++i )
	{
	strRank.Format( "%2d" ,vecDWRank[i].wPlayerRanking );
	m_pRank->AddText( strRank, NS_UITEXTCOLOR::WHITE );
	
	strName.Format( "%s" ,vecDWRank[i].szPlayerName );
	m_pName->AddText( strName, NS_UITEXTCOLOR::WHITE );
	
	strKill.Format( "%d" ,vecDWRank[i].wKillNum );
	m_pKill->AddText( strKill, NS_UITEXTCOLOR::WHITE );

	strDeath.Format( "%d" ,vecDWRank[i].wDeathNum );
	m_pDeath->AddText( strDeath, NS_UITEXTCOLOR::WHITE );	
	}

	for ( int i = 0; i < nRankNum; ++i )
	{
		strKill.Format( "%2d		%s			%d		%d"
					,vecDWRank[i].wPlayerRanking
					,vecDWRank[i].szPlayerName
					,vecDWRank[i].wKillNum
					,vecDWRank[i].wDeathNum );

		m_pDWRankingText->AddText( strKill, NS_UITEXTCOLOR::WHITE );
	}*/

	for ( int i = 0; i < 10; i++ ) 
	{
		m_pSWRankingSlot[i]->SetVisibleSingle ( TRUE );
	}

	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CSWRankingWindow::SetRanking ( CSWRankingSlot* pSWRankingSlot, PGLCHARCLIENT *pChar, const int nSlotNumber, CString strName, int nSchoolType, int nClassType, int nKill, int nDeath )
{	
	pSWRankingSlot->SetNumber( nSlotNumber ); 
	pSWRankingSlot->SetPlayerName ( strName );
	pSWRankingSlot->SetSchool ( nSchoolType );
	//pSWRankingSlot->SetClass ( nClassType );
	pSWRankingSlot->SetScore ( nKill, nDeath );
}

void CSWRankingWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( SW_RANKING_WINDOW );
			}
		}
		break;
	case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( GetWndID () );
				CInnerInterface::GetInstance().ShowGroupBottom ( COMPETITION_NOTIFY_BUTTON );
			}
		}
		break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}