#include "StdAfx.h"
#include "QuestMain.h"
#include "DxFontMan.h"
#include "BasicLineBox.h"
#include "BasicTextBoxEx.h"
#include "BasicScrollBarEx.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "ItemSlot.h"
#include "BasicTextButton.h"
#include "GLQuestPlay.h"
#include "GLQuest.h"
#include "GLQuestMan.h"
#include "GLGaeaClient.h"
#include "InnerInterface.h"
//#include "QuestGiftView.h"
#include "../EngineUiLib/GUInterface/BasicButtonText.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const	float	CQuestMain::fANSWER_LINE_INTERVAL = 5.0f;
const	DWORD	CQuestMain::dwMINITE_BY_HOUR = 60;

CQuestMain::CQuestMain ()
{
}

CQuestMain::~CQuestMain ()
{
}

void	CQuestMain::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	//added by : geger009 | 12-03-2012 | add new interface quest window
	// quest title
	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_MAIN_DESC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxQuestStepDesc ( "QUEST_MAIN_TITLE_BACK_NEW" );
		RegisterControl ( pBasicLineBox );

		CBasicTextBoxEx* pTextBox = new CBasicTextBoxEx;
		pTextBox->CreateSub ( this, "QUEST_MAIN_TITLE_NEW", UI_FLAG_DEFAULT, QUEST_MAIN_TITLE );
		pTextBox->SetFont ( pFont9 );
		pTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_Y );
		pTextBox->SetVisibleSingle ( FALSE );
		RegisterControl ( pTextBox );
		m_pMainTitle = pTextBox;
	}

	//	텍스트 박스
	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_MAIN_DESC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxQuestStepDesc ( "QUEST_MAIN_DESC_BACK_NEW" );
		RegisterControl ( pBasicLineBox );

		CreateControl ( "QUEST_MAIN_DESC_TITLE_BACK_NEW" );
	
		CBasicTextBox* pTitle = CreateStaticControl ( "QUEST_MAIN_DESC_TITLE_NEW", pFont9, NS_UITEXTCOLOR::IDNAMECOLOR, TEXT_ALIGN_CENTER_Y );
		pTitle->AddText ( ID2GAMEWORD("QUEST_MAIN_DESC_TITLE") );
	
		CBasicTextBox* pTextBox = new CBasicTextBox;
		pTextBox->CreateSub ( this, "QUEST_MAIN_DESC_TEXTBOX_NEW", UI_FLAG_DEFAULT, QUEST_MAIN_DESC_TEXTBOX );
		pTextBox->SetFont ( pFont9 );
		pTextBox->SetTextAlign ( TEXT_ALIGN_BOTH_X );
		pTextBox->SetVisibleSingle ( FALSE );
		RegisterControl ( pTextBox );
		m_pDescText = pTextBox;

		int nTotalLine = pTextBox->GetVisibleLine ();

		//	스크롤바
		CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
		pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, QUEST_MAIN_DESC_SCROLLBAR );
		pScrollBar->CreateBaseScrollBar ( "QUEST_MAIN_DESC_SCROLLBAR_NEW" );
		pScrollBar->GetThumbFrame()->SetState ( 1, nTotalLine );
		RegisterControl ( pScrollBar );
		m_pDescScrollBar = pScrollBar;
	}

	//	조건
	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "QUEST_MAIN_CONDITION_BACK_NEW" );
		RegisterControl ( pBasicLineBox );

		CBasicTextBoxEx* pTextBox = new CBasicTextBoxEx;
		pTextBox->CreateSub ( this, "QUEST_MAIN_CONDITION_NEW", UI_FLAG_DEFAULT, QUEST_MAIN_CONDITION );
		pTextBox->SetFont ( pFont9 );
		RegisterControl ( pTextBox );
		m_pCondition = pTextBox;
	}

	{
		//	텍스트 박스
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_MAIN_DESC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxQuestStepDesc ( "QUEST_MAIN_TEXT_BACK_NEW" );
		RegisterControl ( pBasicLineBox );

		CBasicTextBoxEx* pTextBox = new CBasicTextBoxEx;
		pTextBox->CreateSub ( this, "QUEST_MAIN_TEXTBOX_NEW", UI_FLAG_DEFAULT, QUEST_MAIN_TEXTBOX );
		pTextBox->SetFont ( pFont9 );
		pTextBox->SetLineInterval ( fANSWER_LINE_INTERVAL );
		pTextBox->SetVisibleSingle ( FALSE );
		RegisterControl ( pTextBox );
		m_pMainText = pTextBox;

		int nTotalLine = pTextBox->GetVisibleLine ();

		//	스크롤바
		CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
		pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, QUEST_MAIN_SCROLLBAR );
		pScrollBar->CreateBaseScrollBar ( "QUEST_MAIN_SCROLLBAR_NEW" );
		pScrollBar->GetThumbFrame()->SetState ( 1, nTotalLine );
		RegisterControl ( pScrollBar );
		m_pMainScrollBar = pScrollBar;
	}

	//quest step
	{
		
		{
			CBasicLineBox* pBasicLineBox = new CBasicLineBox;
			pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_STEP_DESC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
			pBasicLineBox->CreateBaseBoxQuestRunDesc ( "QUEST_STEP_DESC_BACK_NEW" );
			RegisterControl ( pBasicLineBox );

			CreateControl ( "QUEST_STEP_DESC_TITLE_BACK_NEW" );
	
			CBasicTextBox* pTitle = CreateStaticControl ( "QUEST_STEP_DESC_TITLE_NEW", pFont9, NS_UITEXTCOLOR::IDNAMECOLOR, TEXT_ALIGN_CENTER_Y );
			pTitle->AddText ( ID2GAMEWORD("QUEST_MAIN_BUTTON",1) );

			CBasicTextBox* pTextBox = new CBasicTextBox;
			pTextBox->CreateSub ( this, "QUEST_STEP_DESC_TEXTBOX_NEW", UI_FLAG_DEFAULT, QUEST_STEP_DESC_TEXTBOX );
			pTextBox->SetFont ( pFont9 );		
			pTextBox->SetTextAlign ( TEXT_ALIGN_BOTH_X );
			pTextBox->SetVisibleSingle ( FALSE );
			RegisterControl ( pTextBox );
			m_pStepDescText = pTextBox;

			int nTotalLine = pTextBox->GetVisibleLine ();

			//	스크롤바
			CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
			pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, QUEST_STEP_DESC_SCROLLBAR );
			pScrollBar->CreateBaseScrollBar ( "QUEST_STEP_DESC_SCROLLBAR_NEW" );
			pScrollBar->GetThumbFrame()->SetState ( 1, nTotalLine );
			RegisterControl ( pScrollBar );
			m_pStepDescScrollBar = pScrollBar;
		}

		{
			CBasicLineBox* pBasicLineBox = new CBasicLineBox;
			pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_MAIN_DESC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
			pBasicLineBox->CreateBaseBoxQuestStepDesc ( "QUEST_STEP_TEXT_BACK_NEW" );
			RegisterControl ( pBasicLineBox );

			CBasicTextBoxEx* pTextBox = new CBasicTextBoxEx;
			pTextBox->CreateSub ( this, "QUEST_STEP_TEXTBOX_NEW", UI_FLAG_DEFAULT, QUEST_STEP_TEXTBOX );
			pTextBox->SetFont ( pFont9 );
			pTextBox->SetLineInterval ( fANSWER_LINE_INTERVAL );
			pTextBox->SetVisibleSingle ( FALSE );
			RegisterControl ( pTextBox );
			m_pRunText = pTextBox;

			int nTotalLine = pTextBox->GetVisibleLine ();

			//	스크롤바
			CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
			pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, QUEST_STEP_SCROLLBAR );
			pScrollBar->CreateBaseScrollBar ( "QUEST_STEP_SCROLLBAR_NEW" );
			pScrollBar->GetThumbFrame()->SetState ( 1, nTotalLine );
			RegisterControl ( pScrollBar );
			m_pRunScrollBar = pScrollBar;
		}
	}

	{	//	아이템 타이틀 BACK 이미지
		CreateControl ( "QUEST_MAIN_ITEM_TITLE_BACK_NEW" );

		CBasicTextBox* pTitle = CreateStaticControl ( "QUEST_MAIN_ITEM_TITLE_NEW", pFont9, NS_UITEXTCOLOR::IDNAMECOLOR, TEXT_ALIGN_CENTER_Y );
		pTitle->AddText ( ID2GAMEWORD("QUEST_MAIN_ITEM_TITLE") );

		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_MAIN_ITEM", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxQuestStepItem ( "QUEST_MAIN_ITEM_BACK_NEW" );
		RegisterControl ( pBasicLineBox );

		m_pItemSlot = CreateItemSlot ( "QUEST_MAIN_ITEMSLOT_NEW", QUEST_MAIN_ITEMSLOT );
	}

	//quest reward
	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_MAIN_DESC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxQuestStepDesc ( "QUEST_REWARD_BACK_NEW" );
		RegisterControl ( pBasicLineBox );

		CreateControl ( "QUEST_REWARD_TITLE_BACK_NEW" );
	
		CBasicTextBox* pTitle = CreateStaticControl ( "QUEST_REWARD_TITLE_NEW", pFont9, NS_UITEXTCOLOR::IDNAMECOLOR, TEXT_ALIGN_CENTER_Y );
		pTitle->AddText ( ID2GAMEWORD("QUEST_MAIN_BUTTON",4) );

		CBasicTextBox* pMapMoveTextBox = new CBasicTextBox;
		pMapMoveTextBox->CreateSub ( this, "QUEST_REWARD_TEXTBOX_NEW", UI_FLAG_XSIZE | UI_FLAG_YSIZE, QUEST_REWARD_TEXTBOX );
		pMapMoveTextBox->SetFont ( pFont9 );
		pMapMoveTextBox->SetTextAlign ( TEXT_ALIGN_BOTH_X );
		pMapMoveTextBox->SetVisibleSingle ( FALSE );
		RegisterControl ( pMapMoveTextBox );
		m_pRewardText = pMapMoveTextBox;

		int nTotalLine = pMapMoveTextBox->GetVisibleLine ();

		CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
		pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, QUEST_REWARD_SCROLLBAR );
		pScrollBar->CreateBaseScrollBar ( "QUEST_REWARD_SCROLLBAR_NEW" );
		pScrollBar->GetThumbFrame()->SetState ( 1, nTotalLine );
		RegisterControl ( pScrollBar );
		m_pRewardScrollBar = pScrollBar;
	}

	const int nAlignCenterBoth = TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y;

	{
		m_pButtonL = CreateButtonBlue ( "QUEST_MAIN_BUTTON_L_NEW", "QUEST_STEP_TEXT_POS_NEW", pFont9, nAlignCenterBoth ,QUEST_MAIN_BUTTON_L, "Give Up" );                
		m_pButtonCOMPLETE = CreateButtonBlue ( "QUEST_MAIN_BUTTON_COMPLETE_NEW", "QUEST_STEP_TEXT_POS_NEW", pFont9, nAlignCenterBoth ,QUEST_MAIN_BUTTON_COMPLETE, "Complete" );
		m_pButtonPrint = CreateButtonBlue ( "QUEST_STEP_BUTTON_PRINT_NEW", "QUEST_STEP_TEXT_POS_NEW", pFont9, nAlignCenterBoth ,QUEST_STEP_BUTTON_PRINT, "Print" );
		//m_pButtonPrint = CreateButtonBlue ( "QUEST_STEP_BUTTON_PRINT", "QUEST_STEP_TEXT_POS", pFont9, nAlignCenterBoth , QUEST_STEP_BUTTON_PRINT, "Listed on/released" );
		
	}
}

CItemSlot* CQuestMain::CreateItemSlot ( CString strKeyword, UIGUID ControlID )
{
	CItemSlot* pItemSlot = new CItemSlot;
	pItemSlot->CreateSub ( this, strKeyword.GetString (), UI_FLAG_DEFAULT, ControlID );
	pItemSlot->CreateSubControl ( GLQUESTPROG::INVEN_SIZEX, TRUE );
	RegisterControl ( pItemSlot );
	return pItemSlot;
}

CBasicTextButton* CQuestMain::CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE24;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicButtonText* CQuestMain::CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText )
{
	CBasicButtonText* pButton = new CBasicButtonText;
	pButton->CreateRanButtonBlue ( this, szButton, ControlID );
	pButton->CreateTextBox ( szTextBox, pFont, nAlign );
	pButton->SetOneLineText( strText.GetString() );
	RegisterControl ( pButton );

	return pButton;
}

CUIControl*	CQuestMain::CreateControl ( char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}


CBasicTextBox* CQuestMain::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CQuestMain::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle ( bVisible );
}

void CQuestMain::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	{
		CBasicScrollThumbFrame* const pThumbFrame = m_pDescScrollBar->GetThumbFrame ();

		const int nTotalLine = m_pDescText->GetTotalLine ();
		const int nLinePerOneView = m_pDescText->GetVisibleLine ();
		CDebugSet::ToView ( 1, 10, "보이는 라인 %d", nLinePerOneView );

		pThumbFrame->SetState ( nTotalLine, nLinePerOneView );
		if ( nLinePerOneView < nTotalLine )
		{
			const int nMovableLine = nTotalLine - nLinePerOneView;
			float fPercent = pThumbFrame->GetPercent ();
			int nPos = (int)floor(fPercent * nMovableLine);
			m_pDescText->SetCurLine ( nPos );			
		}
	}
	{
		CBasicScrollThumbFrame* const pThumbFrame = m_pMainScrollBar->GetThumbFrame ();

		const int nTotalLine = m_pMainText->GetTotalLine ();
		const int nLinePerOneView = m_pMainText->GetVisibleLine ();
		CDebugSet::ToView ( 1, 10, "보이는 라인 %d", nLinePerOneView );

		pThumbFrame->SetState ( nTotalLine, nLinePerOneView );
		if ( nLinePerOneView < nTotalLine )
		{
			const int nMovableLine = nTotalLine - nLinePerOneView;
			float fPercent = pThumbFrame->GetPercent ();
			int nPos = (int)floor(fPercent * nMovableLine);
			m_pMainText->SetCurLine ( nPos );			
		}
	}
	{
		CBasicScrollThumbFrame* const pThumbFrame = m_pRewardScrollBar->GetThumbFrame ();

		const int nTotalLine = m_pRewardText->GetTotalLine ();
		const int nLinePerOneView = m_pRewardText->GetVisibleLine ();
		CDebugSet::ToView ( 1, 10, "보이는 라인 %d", nLinePerOneView );

		pThumbFrame->SetState ( nTotalLine, nLinePerOneView );
		if ( nLinePerOneView < nTotalLine )
		{
			const int nMovableLine = nTotalLine - nLinePerOneView;
			float fPercent = pThumbFrame->GetPercent ();
			int nPos = (int)floor(fPercent * nMovableLine);
			m_pRewardText->SetCurLine ( nPos );			
		}
	}
}

void CQuestMain::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case QUEST_MAIN_BUTTON_L:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_BUTTON_GIVEUP );
			}
		}
		break;

	case QUEST_STEP_BUTTON_PRINT:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_BUTTON_PRINT_STEP );
			}
		}
		break;
	
	case QUEST_MAIN_BUTTON_COMPLETE:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_BUTTON_COMPLETE );
			}
		}
		break;

	case QUEST_MAIN_ITEMSLOT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nPosX = m_pItemSlot->GetItemIndex ();
				if ( nPosX < 0 ) return ;
				SINVENITEM sInvenItem = GetItem ( nPosX );
				{				
					if ( sInvenItem.sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO_SIMPLE ( sInvenItem.sItemCustom );
					}
				}
			}
		}
		break;

	case QUEST_MAIN_TEXTBOX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DUP & dwMsg )
				{
					AddMessageEx ( UIMSG_BUTTON_GO_QUESTSTEP );
				}
			}
		}
		break;
	}
}

bool	CQuestMain::LoadQuestMain ( DWORD dwQuestID )
{
	if ( dwQuestID == NATIVEID_NULL().dwID ) return false;

	m_dwQuestID = dwQuestID;
	
	GLQuestPlay& cQuestPlay = GLGaeaClient::GetInstance().GetCharacter ()->m_cQuestPlay;
	GLQUESTPROG* pQuestProg = cQuestPlay.FindProc ( dwQuestID );
	if ( !pQuestProg ) return false;

	GLQUEST* pQuest = GLQuestMan::GetInstance().Find ( dwQuestID );
	if ( !pQuest ) return false;	

	const DWORD dwSTEP = pQuestProg->m_dwSTEP;
	GLQUEST_STEP* pQuestStep = pQuest->GetSTEP ( dwSTEP );	

	//quest title
	{
		m_pMainTitle->SetVisibleSingle ( TRUE );
		m_pMainTitle->SetText( (char*)pQuest->GetTITLE(), NS_UITEXTCOLOR::GREENYELLOW );
	}

	//	설명
	{
		m_pDescText->SetVisibleSingle ( TRUE );
		m_pDescText->SetText( pQuest->m_strCOMMENT.c_str(), NS_UITEXTCOLOR::WHITE );
		m_pDescScrollBar->GetThumbFrame()->SetPercent ( 0.0f );
	}

	//	조건
	{
		m_pCondition->ClearText ();				
		CString strCombine;		
		CString strConditionLine1, strConditionLine2;

		if ( pQuest->m_dwLimitTime )
		{
			const DWORD dwLimitTime = pQuest->m_dwLimitTime;
			const DWORD dwLimitHour = dwLimitTime / dwMINITE_BY_HOUR;
			const DWORD dwLimitMinute = dwLimitTime % dwMINITE_BY_HOUR;

			const float fLapsTime = pQuestProg->m_fLAPSTIME;
			const DWORD dwLapsTime = ((DWORD)fLapsTime) / dwMINITE_BY_HOUR;	// 초->분단위
            const DWORD dwLapsHour = dwLapsTime / dwMINITE_BY_HOUR;
			const DWORD dwLapsMinute = dwLapsTime % dwMINITE_BY_HOUR;

			CString strLimitTime;
			if ( dwLimitHour )
			{
				strLimitTime.Format ( "%d%s %d%s",
                    dwLimitHour, ID2GAMEWORD("QUEST_CONDITION_TIME_UNIT",0),	// 2, 3
					dwLimitMinute, ID2GAMEWORD("QUEST_CONDITION_TIME_UNIT",1) );
			}
			else
			{
				strLimitTime.Format ( "%d%s",
					dwLimitMinute, ID2GAMEWORD("QUEST_CONDITION_TIME_UNIT",1) );
			}

			CString strLapsTime;
			if ( dwLapsHour )
			{
				strLapsTime.Format ( "%d%s %d%s",
                    dwLapsHour, ID2GAMEWORD("QUEST_CONDITION_TIME_UNIT",0),	// 2, 3
					dwLapsMinute, ID2GAMEWORD("QUEST_CONDITION_TIME_UNIT",1) );
			}
			else
			{
				strLapsTime.Format ( "%d%s",
					dwLapsMinute, ID2GAMEWORD("QUEST_CONDITION_TIME_UNIT",1) );
			}

			strConditionLine1.Format ( "%s : [%s/%s]", 
				ID2GAMEWORD("QUEST_MAIN_CONDITION",0), strLapsTime, strLimitTime );			
		}

		if ( pQuest->m_dwLimitPartyMemNum )
		{
			if ( strConditionLine1.GetLength () )
				strCombine.Format ( ", %s : %d", ID2GAMEWORD("QUEST_MAIN_CONDITION",1), pQuest->m_dwLimitPartyMemNum );
			else
				strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_MAIN_CONDITION",1), pQuest->m_dwLimitPartyMemNum );
			strConditionLine1 += strCombine;			
		}

		//	첫번째 줄
		if ( strConditionLine1.GetLength () )
		{
			strCombine.Format ( "%s - %s", ID2GAMEWORD("QUEST_CONDITION"), strConditionLine1 );
			m_pCondition->AddText ( strCombine, NS_UITEXTCOLOR::IDNAMECOLOR );
		}

		//	두번째 줄
		if ( pQuest->m_bNonDie )
		{
			strConditionLine2 = ID2GAMEWORD("QUEST_MAIN_CONDITION",2);
			if ( strConditionLine1.GetLength () )	//	윗 라인이 있을 경우
			{
				std::string strCondition = ID2GAMEWORD("QUEST_CONDITION");
				std::string strBlank ( strCondition.size(), ' ' );

				strCombine.Format ( "%s - %s", strBlank.c_str(), strConditionLine2 );				
			}
			else
			{
				strCombine.Format ( "%s - %s", ID2GAMEWORD("QUEST_CONDITION"), strConditionLine2 );				
			}

			m_pCondition->AddText ( strCombine, NS_UITEXTCOLOR::IDNAMECOLOR );
		}
	}

	//	진행 상황
	{
		m_pMainText->SetVisibleSingle ( TRUE );
		enum
		{
			QUEST_CHECK = 0,
			QUEST_CHECK_F
		};

		static	CString strCheckKeyword[] =
		{
			"QUEST_CHECK",
			"QUEST_CHECK_F"
		};

		m_pMainText->ClearText ();
		GLQUEST::VECQSTEP& vecProgStep = pQuest->m_vecProgStep;
		for ( int i = 0; i < (int)vecProgStep.size(); ++i )
		{
			const GLQUEST_STEP& sQuestStep = vecProgStep[i];

			D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
			int nImageType = QUEST_CHECK;
			if ( i < (int)dwSTEP )
			{
				dwColor = NS_UITEXTCOLOR::DARKGRAY;
				nImageType = QUEST_CHECK_F;
			}
			else if ( i == (int)dwSTEP )
			{
				dwColor = NS_UITEXTCOLOR::GOLD;
			}

			int nIndex = m_pMainText->AddText ( sQuestStep.GetTITLE (), dwColor );
			m_pMainText->SetTextImage ( nIndex, strCheckKeyword[nImageType] );
		}

		CBasicScrollThumbFrame* const pThumbFrame = m_pMainScrollBar->GetThumbFrame ();

		const int nTotalLine = m_pMainText->GetTotalLine ();
		const int nLinePerOneView = m_pMainText->GetVisibleLine ();		
		pThumbFrame->SetState ( nTotalLine, nLinePerOneView );


		m_pMainText->SetCurLine ( 0 );
		pThumbFrame->SetPercent ( 0.0f );
		const int nCount = m_pMainText->GetCount () - 1;
		if ( nLinePerOneView < nTotalLine )
		{			
			float fPercent = (float)dwSTEP / (float)nCount;
			pThumbFrame->SetPercent ( fPercent );
		}
	}

	//	아이템 설정
	{
		//	클리어
		for ( int i = 0; i < GLQUESTPROG::INVEN_SIZEX; ++i )
		{
			UnLoadItem ( i );
		}

		GLInventory::CELL_MAP *ItemList = pQuestProg->m_sINVENTORY.GetItemList ();

		if ( ItemList->size () > (GLQUESTPROG::INVEN_SIZEX * GLQUESTPROG::INVEN_SIZEY) )
		{
			GASSERT ( 0 && "인터페이스 사이즈보다, 데이타크기가 큽니다." );
			return false;
		}

		GLInventory::CELL_MAP_ITER iter = ItemList->begin();
		GLInventory::CELL_MAP_ITER iter_end = ItemList->end();

		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;
			SITEMCUSTOM &ref_ItemCustom = pInvenItem->sItemCustom;
			SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_ItemCustom.sNativeID );
			if ( !pItemData )	continue;

			LoadItem ( *pInvenItem );
		}
	}

	//quest reward
	{
		m_pRewardText->SetVisibleSingle ( TRUE );
		m_pRewardText->ClearText ();

		GLQUEST* pQuest = GLQuestMan::GetInstance().Find ( dwQuestID );
		if ( !pQuest )
		{
			CDebugSet::ToLogFile ( "quest id = %d 의 정보를 가져오지 못하였습니다.", dwQuestID );
			return false;
		}

		//	보상치가 없으면 아무것도 표시하지 않음
		if ( !(pQuest->m_dwGiftEXP || pQuest->m_dwGiftMONEY ||
				pQuest->m_dwGiftELEMENT || pQuest->m_dwGiftLIFEPOINT ||
				pQuest->m_dwGiftSKILLPOINT || pQuest->m_dwGiftSTATSPOINT ||
				pQuest->m_vecGiftITEM.size () || pQuest->m_vecGiftSKILL.size ()) )
		{
			return false;
		}

		{
			m_pRewardText->AddText ( ID2GAMEWORD("QUEST_GIFT",9), NS_UITEXTCOLOR::GREENYELLOW );

			CString strCombine;

			if ( pQuest->m_dwGiftEXP )
			{
				strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",0), pQuest->m_dwGiftEXP );
				m_pRewardText->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );
			}
			if ( pQuest->m_dwGiftMONEY )
			{
				strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",1), pQuest->m_dwGiftMONEY );
				m_pRewardText->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );
			}
			if ( pQuest->m_dwGiftELEMENT )
			{
				strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",2), pQuest->m_dwGiftELEMENT );
				m_pRewardText->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );
			}
			if ( pQuest->m_dwGiftLIFEPOINT )
			{
				strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",3), pQuest->m_dwGiftLIFEPOINT );
				m_pRewardText->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );
			}
			if ( pQuest->m_dwGiftSKILLPOINT )
			{
				strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",5), pQuest->m_dwGiftSKILLPOINT );
				m_pRewardText->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );
			}
			if ( pQuest->m_dwGiftSTATSPOINT )
			{
				strCombine.Format ( "%s : %d", ID2GAMEWORD("QUEST_GIFT",6), pQuest->m_dwGiftSTATSPOINT );
				m_pRewardText->AddText ( strCombine, NS_UITEXTCOLOR::WHITE );
			}

			if ( pQuest->m_vecGiftITEM.size () )
			{
				CString strItem = ID2GAMEWORD("QUEST_GIFT",7);
				strItem += " : ";
				INVENQARRAY_ITER iter = pQuest->m_vecGiftITEM.begin ();
				INVENQARRAY_ITER iter_end = pQuest->m_vecGiftITEM.end ();
				for ( ; iter != iter_end; )
				{
					SITEMCUSTOM& sItemCustom = (*iter);
					SITEM* pItem = GLItemMan::GetInstance().GetItem ( sItemCustom.sNativeID );
					if ( !pItem ) continue;
					strItem += pItem->GetName ();

					++iter;
					if ( iter == iter_end ) break;
					strItem += ", ";
				}
				m_pRewardText->AddText ( strItem, NS_UITEXTCOLOR::WHITE );
			}

			if ( pQuest->m_vecGiftSKILL.size () )
			{
				CString strSkill = ID2GAMEWORD("QUEST_GIFT",8);
				strSkill += " : ";
				DWQARRAY_ITER iter = pQuest->m_vecGiftSKILL.begin ();
				DWQARRAY_ITER iter_end = pQuest->m_vecGiftSKILL.end ();
				for ( ; iter != iter_end; )
				{
					DWORD dwID = (*iter);									
					PGLSKILL pSKILL = GLSkillMan::GetInstance().GetData ( SNATIVEID(dwID) );
					if ( !pSKILL ) continue;
					strSkill += pSKILL->GetName();

					++iter;
					if ( iter == iter_end ) break;
					strSkill += ", ";
				}
				m_pRewardText->AddText ( strSkill, NS_UITEXTCOLOR::WHITE );
			}
		}
		CBasicScrollThumbFrame* const pThumbFrame = m_pRewardScrollBar->GetThumbFrame ();

		const int nTotalLine = m_pRewardText->GetTotalLine ();
		const int nLinePerOneView = m_pRewardText->GetVisibleLine ();		
		pThumbFrame->SetState ( nTotalLine, nLinePerOneView );


		m_pRewardText->SetCurLine ( 0 );
		pThumbFrame->SetPercent ( 0.0f );
		const int nCount = m_pRewardText->GetCount () - 1;
		if ( nLinePerOneView < nTotalLine )
		{			
			float fPercent = (float)dwSTEP / (float)nCount;
			pThumbFrame->SetPercent ( fPercent );
		}
	}

	//	우선순위가 중요함.
	//	완료가 포기에 우선한다.
	//	만약, 퀘스트가 완료되었다면, 포기는 뿌릴 필요가 없다.
	m_pButtonCOMPLETE->SetVisibleSingle ( FALSE );
	m_pButtonL->SetVisibleSingle ( FALSE );
	
	if ( pQuestProg->CheckCOMPLETE() )	//	완료버튼을 눌러야 하는 퀘스트
	{		
		m_pButtonCOMPLETE->SetVisibleSingle ( TRUE );
		return true;
	}	
	else if ( pQuest->IsGIVEUP () )	//	포기 퀘스트
	{
		m_pButtonL->SetVisibleSingle ( TRUE );
		return true;
	}

	return true;
}

//quest step load function
bool	CQuestMain::LoadQuestStep ( DWORD dwQuestID )
{
	if ( dwQuestID == NATIVEID_NULL().dwID ) return false;

	GLQuestPlay& cQuestPlay = GLGaeaClient::GetInstance().GetCharacter ()->m_cQuestPlay;
	GLQUESTPROG* pQuestProg = cQuestPlay.FindProc ( dwQuestID );
	if ( !pQuestProg ) return false;

	GLQUEST* pQuest = GLQuestMan::GetInstance().Find ( dwQuestID );
	if ( !pQuest ) return false;	

	const DWORD dwSTEP = pQuestProg->m_dwSTEP;
	GLQUEST_STEP* pQuestStep = pQuest->GetSTEP ( dwSTEP );

	GLQUESTPROG_STEP& sSTEP_PROG = pQuestProg->m_sSTEP_PROG;	

	//	설명
	{
		m_pStepDescText->SetVisibleSingle ( TRUE );
		m_pStepDescText->SetText ( pQuestStep->GetCOMMENT (), NS_UITEXTCOLOR::WHITE );
		m_pStepDescScrollBar->GetThumbFrame()->SetPercent ( 0.0f );
	}

	//	진행 상황
	{
		m_pRunText->SetVisibleSingle ( TRUE );
		enum
		{
			QUEST_CHECK = 0,
			QUEST_CHECK_F
		};

		static	CString strCheckKeyword[] =
		{
			"QUEST_CHECK",
			"QUEST_CHECK_F"
		};

		m_pRunText->ClearText ();
		if ( pQuestStep->IsNEED_NPCTALK() )
		{
			D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
			int nImageType = QUEST_CHECK;
			if ( sSTEP_PROG.m_bTALK )
			{
				dwColor = NS_UITEXTCOLOR::DARKGRAY;
				nImageType = QUEST_CHECK_F;
			}

			int nIndex = m_pRunText->AddText ( pQuestStep->m_strOBJ_NPCTALK.c_str (), dwColor );
			m_pRunText->SetTextImage ( nIndex, strCheckKeyword[nImageType] );
		}
		
		if ( pQuestStep->IsNEED_QITEM() )
		{
			D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
			int nImageType = QUEST_CHECK;
			if ( sSTEP_PROG.m_bQITEM )
			{
				dwColor = NS_UITEXTCOLOR::DARKGRAY;
				nImageType = QUEST_CHECK_F;
			}
			int nIndex = m_pRunText->AddText ( pQuestStep->m_strOBJ_MOBGEN_QITEM.c_str (), dwColor );
			m_pRunText->SetTextImage ( nIndex, strCheckKeyword[nImageType] );
		}

		if ( pQuestStep->IsNEED_MOBKILL() )
		{
			D3DCOLOR dwColor = NS_UITEXTCOLOR::GOLD;
			int nImageType = QUEST_CHECK;
			if ( sSTEP_PROG.m_bMOBKILL_ALL )
			{
				dwColor = NS_UITEXTCOLOR::DARKGRAY;
				nImageType = QUEST_CHECK_F;
			}

			CString strCombine;
			strCombine.Format ( "%s [%d/%d]",
				pQuestStep->m_strOBJ_MOBKILL.c_str (),
				sSTEP_PROG.m_dwNUM_MOBKILL,
				pQuestStep->m_dwNUM_MOBKILL );
			int nIndex = m_pRunText->AddText ( strCombine, dwColor );
			m_pRunText->SetTextImage ( nIndex, strCheckKeyword[nImageType] );
		}

		if ( pQuestStep->IsNEED_NPCGUARD() )
		{
			D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
			int nImageType = QUEST_CHECK;
			if ( sSTEP_PROG.m_bNPCGUARD_DEATH )
			{
				dwColor = NS_UITEXTCOLOR::DARKGRAY;
				nImageType = QUEST_CHECK_F;
			}
			int nIndex = m_pRunText->AddText ( pQuestStep->m_strOBJ_NPCGUARD.c_str (), dwColor );
			m_pRunText->SetTextImage ( nIndex, strCheckKeyword[nImageType] );
		}
		
		if ( pQuestStep->IsNEED_REACHZONE() )
		{
			D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
			int nImageType = QUEST_CHECK;
			if ( sSTEP_PROG.m_bREACH_ZONE )
			{
				dwColor = NS_UITEXTCOLOR::DARKGRAY;
				nImageType = QUEST_CHECK_F;
			}
			int nIndex = m_pRunText->AddText ( pQuestStep->m_strOBJ_REACH_ZONE.c_str (), dwColor );
			m_pRunText->SetTextImage ( nIndex, strCheckKeyword[nImageType] );
		}

		if ( pQuestStep->IsNEED_DEFENSEZONE() )
		{
			D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
			int nImageType = QUEST_CHECK;
			if ( sSTEP_PROG.m_bDEFENSE_ZONE_COMPLETE )
			{
				dwColor = NS_UITEXTCOLOR::DARKGRAY;
				nImageType = QUEST_CHECK_F;
			}
			int nIndex = m_pRunText->AddText ( pQuestStep->m_strOBJ_DEFENSE_ZONE.c_str (), dwColor );
			m_pRunText->SetTextImage ( nIndex, strCheckKeyword[nImageType] );
		}		
	}
	//	우선순위가 중요함.
	if( pQuestStep->IsNEED_QITEM() || pQuestStep->IsNEED_MOBKILL() ) m_pButtonPrint->SetVisibleSingle( TRUE );
	else	m_pButtonPrint->SetVisibleSingle( FALSE );

	return true;
}

void CQuestMain::LoadItem ( SINVENITEM& ref_InvenItem )
{	
	int nPosX = ref_InvenItem.wPosX;
//	int nPosY = ref_InvenItem.wPosY;
	m_pItemSlot->SetItemImage ( nPosX, ref_InvenItem );
}


SINVENITEM& CQuestMain::GetItem ( int nPosX )
{
	return m_pItemSlot->GetItemImage ( nPosX );
}

void CQuestMain::UnLoadItem ( int nPosX )
{
	m_pItemSlot->ResetItemImage ( nPosX );
}