#include "StdAfx.h"
#include "d3dfont.h"
#include "SkillWindow.h"
#include "BasicTextButton.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "GameTextControl.h"
#include "DxGlobalStage.h"
#include <set>
#include "SkillPage.h"
#include "BasicLineBox.h"
#include "BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "SkillSlot.h"
#include "InnerInterface.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSkillWindow::CSkillWindow ()
	: m_pRestPoint ( NULL )
	, m_dwSkillPointBACK ( 0 )
	, m_pHelp(NULL)
{
	memset ( m_pPage, 0, sizeof ( m_pPage ) );
	memset ( m_pPageButton, 0, sizeof ( m_pPageButton ) );
}

CSkillWindow::~CSkillWindow ()
{
}

CBasicTextButton*	 CSkillWindow::CreateButton ( char* szButton, UIGUID ControlID, char* szText )
{
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, 
									CBasicTextButton::SIZE24, 
									CBasicButton::CLICK_FLIP, 
									szText,
									_DEFAULT_FONT_SHADOW_EX_FLAG );
	pTextButton->SetFlip ( TRUE );
	RegisterControl ( pTextButton );

	return pTextButton;
}

void CSkillWindow::SetVisiblePage ( int nPage )
{
	if ( nPage < SKILL_WINDOW_PAGE0 || SKILL_WINDOW_PAGE3 < nPage )
	{
		GASSERT ( 0 && "¿µ¿ªÀ» ³Ñ¾ûØ­´Â ÆäÀÌÁöÀÔ´Ï´Ù." );
		return ;
	}

	//	¸®¼Â
	for ( int i = 0; i < nMAXPAGE; i++ )
	{
		m_pPage[i]->SetVisibleSingle ( FALSE );
		m_pPageButton[i]->SetFlipYellow ( FALSE );
	}

	int nIndex = nPage - SKILL_WINDOW_PAGE0;
	m_pPage[nIndex]->SetVisibleSingle ( TRUE );
	m_pPageButton[nIndex]->SetFlipYellow ( TRUE );
}

void CSkillWindow::CreateSubControl ()
{
	EMCHARCLASS emCharClass = DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass;
	const int nCLASSTYPE = CharClassToIndex ( emCharClass );
	int newClassType = nCLASSTYPE;

	//if ( nCLASSTYPE > GLCI_EXTREME_W ) newClassType = nCLASSTYPE - GLCI_NUM_EX;
	//add class
	//removed

	int nSkillCountAll[EMSKILL_PC_CLASSNUM] = { 0, 0, 0, 0, 0, 0 };

	SNATIVEID sNativeIDArrayAll[EMSKILL_PC_CLASSNUM][GLSkillMan::MAX_CLASSSKILL];
	{	//	½ºÅ³ Á¤·Ä ( µûÍÞ ¼ø¼­ )		
		for ( int i = 0; i < EMSKILL_PC_CLASSNUM; i ++ )
		{
			for ( int j = 0; j < GLSkillMan::MAX_CLASSSKILL; j++ )
			{
				sNativeIDArrayAll[i][j] = NATIVEID_NULL();
			}
		}

		SortSkill ( emCharClass, sNativeIDArrayAll, nSkillCountAll );
	}

	//?????¶?
	{	// Xám Ðen Background
		CBasicLineBoxEx* pBasicLineBoxEx = new CBasicLineBoxEx;
		pBasicLineBoxEx->CreateSub ( this, "BLACKCATYB_XAM_DEN_GIUA", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBoxEx->BlackCatYBXamDenBox ( "CUASO_KYNANG_BG" );
		RegisterControl ( pBasicLineBoxEx );
	}
	{	// Xám Ðen Background
		CBasicLineBoxEx* pBasicLineBoxEx = new CBasicLineBoxEx;
		pBasicLineBoxEx->CreateSub ( this, "BLACKCATYB_XAM_DEN_GIUA", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBoxEx->BlackCatYBXamDenBox ( "CUASO_KYNANG_BG_DIEM" );
		RegisterControl ( pBasicLineBoxEx );
	}
/*	{
		m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "RNSKILL_WINDOW_WHITE", UI_FLAG_DEFAULT);	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	}*/

	{	//	ÅÇ ¹öÆ°
		//const CString strClassTextKeyword[GLCI_NUM_EX] = 
		//add class
		const CString strClassTextKeyword[GLCI_NUM_NEWEST] = 
		{
			"SKILL_TAB_TITLE_FIGHTER",
			"SKILL_TAB_TITLE_ARMS",
			"SKILL_TAB_TITLE_ARCHER",
			"SKILL_TAB_TITLE_SPIRIT",
			"SKILL_TAB_TITLE_EXTREME",
			"SKILL_TAB_TITLE_EXTREME",
			"SKILL_TAB_TITLE_FIGHTER",
			"SKILL_TAB_TITLE_ARMS",
			"SKILL_TAB_TITLE_ARCHER",
			"SKILL_TAB_TITLE_SPIRIT",
			"SKILL_TAB_TITLE_SCIENCE",
			"SKILL_TAB_TITLE_SCIENCE",
			"SKILL_TAB_TITLE_ASSASIN",
			"SKILL_TAB_TITLE_ASSASIN",
			"SKILL_TAB_TITLE_TRICKER",
			"SKILL_TAB_TITLE_TRICKER",
		};
		
		CString strClassText = strClassTextKeyword[newClassType ];

		CString	strPageKeyword[nMAXPAGE] = 
		{
			"KYNANG_TAB_1",
			"KYNANG_TAB_2",
			"KYNANG_TAB_3",
			"KYNANG_TAB_4",
		};		

		for ( int i = 0; i < nMAXPAGE; i++ )
		{	
			CString strCombine;
			strCombine.Format ( "%s",(char*)ID2GAMEWORD ( strClassText.GetString(), i ));
							
			CString strTemp;
			strTemp.Format ( "%s", strCombine );
			m_pPage[i] = CreateSkillPage ( SKILL_WINDOW_PAGE0 + i, sNativeIDArrayAll[i], nSkillCountAll[i] );
			m_pPageButton[i] = CreateTextButton ( strPageKeyword[i].GetString (), KYNANG_TAB_1 + i, strTemp );
		}	
	}

	{	//	½ºÅ³Æ÷ÀÎÆ® ÀÜ·® Ç¥½Ã
		D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;
		CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
		int	nTextAlign = TEXT_ALIGN_LEFT;

		CBasicTextBox* pTextBox = CreateStaticControl ( "KYNANG_DONG_DIEM_CHU", pFont9, dwColor, nTextAlign );
		pTextBox->AddText ( (char*)ID2GAMEWORD ( "SKILL_WINDOW_REST_POINT_STATIC" ), NS_UITEXTCOLOR::WHITE );
		
/*/		CBasicLineBox* pLineBox = new CBasicLineBox;
		pLineBox->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pLineBox->CreateBaseBoxSkill ( "RNSKILL_SKILL_POINT_REGION" );
		RegisterControl ( pLineBox );*/

		m_pRestPoint = CreateStaticControl ( "KYNANG_DONG_DIEM_SO", pFont9, dwColor, TEXT_ALIGN_CENTER_X );		
		CString strTemp;
		strTemp.Format ( "0" );
		m_pRestPoint->AddText ( strTemp );
	}

		CreateButton ( "KYNANG_RESET_BUTTON", RNSKILL_WINDOW_RESET_BUTTON, "0 Reset Points" );
		CreateButton ( "KYNANG_ADJUST_BUTTON", RNSKILL_WINDOW_ADJUST_BUTTON, "0 Adjust Points" );
	
	{
		m_pHelp = new CBasicButton;
		m_pHelp->CreateSub ( this, "CUASO_KYNANG_GIUPDO_BUTTON" , UI_FLAG_DEFAULT, SKILL_WINDOW_HELP_BUTTON );
		m_pHelp->CreateFlip ( "CUASO_KYNANG_GIUPDO_BUTTON_OVER", CBasicButton::MOUSEIN_FLIP );
		m_pHelp->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pHelp );
	}

	SetVisiblePage ( SKILL_WINDOW_PAGE0 );
}

CBasicTextButton*  CSkillWindow::CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText, _DEFAULT_FONT_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CSkillPage*	CSkillWindow::CreateSkillPage ( UIGUID ControlID, SNATIVEID sNativeIDArray[GLSkillMan::MAX_CLASSSKILL], int nSkillCount )
{
	CSkillPage* pSkillPage = new CSkillPage;
	pSkillPage->CreateSub ( this, "KHUVUC_TRANG_KYNANG", UI_FLAG_DEFAULT, ControlID );
	pSkillPage->CreateSubControl ( sNativeIDArray, nSkillCount );
	RegisterControl ( pSkillPage );
	return pSkillPage;
}

void CSkillWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( SKILL_WINDOW );
			}
		}
		break;
	case KYNANG_TAB_1:
	case KYNANG_TAB_2:
	case KYNANG_TAB_3:	
	case KYNANG_TAB_4:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_DOWN )
				{
					int nIndex = ControlID - KYNANG_TAB_1;
					SetVisiblePage ( SKILL_WINDOW_PAGE0 + nIndex );
				}
			}
		}
		break;
	case SKILL_WINDOW_HELP_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CString strTemp;
				strTemp.Format( "%s", ID2GAMEINTEXT("SKILL_WINDOW_QUESTION_BUTTON_MESSAGE"));
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO_SPLIT( strTemp.GetString(), NS_UITEXTCOLOR::DARKLBUE );
			}
		}
		break;
	}
    
	if ( SKILL_WINDOW_PAGE0 <= ControlID && ControlID <= SKILL_WINDOW_PAGE3 )
	{
		int nIndex = ControlID - SKILL_WINDOW_PAGE0;
		int nSkillIndex = m_pPage[nIndex]->GetSkillIndex ();		

		if ( CHECK_MOUSE_IN ( dwMsg ) )
		{			
			if ( nSkillIndex < 0 ) return;
			SNATIVEID sNativeID = m_pPage[nIndex]->GetSkillID ( nSkillIndex );
			if ( sNativeID != NATIVEID_NULL() )
			{
				{
					if ( dwMsg & UIMSG_MOUSEIN_BUTTON || dwMsg & UIMSG_MOUSEIN_BUTTON2 )
					{
						dwMsg &= ~UIMSG_TOTOPPARENT;
						dwMsg &= ~UIMSG_MOUSEIN_BUTTON;
						SetMessageEx ( dwMsg );

						if ( dwMsg & UIMSG_LEVEL_UP )
						{							
							dwMsg &= ~UIMSG_LEVEL_UP;
							SetMessageEx ( dwMsg );
							CInnerInterface::GetInstance().RESET_INFO ();
						}						
						
						CInnerInterface::GetInstance().SHOW_SKILL_INFO ( sNativeID, TRUE );

					}
					else if ( dwMsg & UIMSG_MOUSEIN_SKILLIMAGE )
					{
						CInnerInterface::GetInstance().SHOW_SKILL_INFO ( sNativeID, FALSE );
					}
				}
			}
		}
	}
}

void CSkillWindow::GetSkillIndexRange ( EMCHARCLASS emCharClass, int* pnBeginIndex, int* pnEndIndex )
{	
	//	??? ??
	int nBeginIndex = 0;
	int nEndIndex = 0;

	switch ( emCharClass )
	{
	case GLCC_FIGHTER_M:
	case GLCC_FIGHTER_W:
		{
			nBeginIndex = EMSKILL_FIGHTER_01;
			nEndIndex = EMSKILL_FIGHTER_04;
		}
		break;

	case GLCC_ARMS_M:
	case GLCC_ARMS_W:
		{
			nBeginIndex = EMSKILL_ARMS_01;
			nEndIndex = EMSKILL_ARMS_04;
		}
		break;

	case GLCC_ARCHER_M:
	case GLCC_ARCHER_W:
		{
			nBeginIndex = EMSKILL_ARCHER_01;
			nEndIndex = EMSKILL_ARCHER_04;
		}
		break;

	case GLCC_SPIRIT_M:
	case GLCC_SPIRIT_W:
		{
			nBeginIndex = EMSKILL_SPIRIT_01;
			nEndIndex = EMSKILL_SPIRIT_04;
		}
		break;	

	case GLCC_EXTREME_M:
	case GLCC_EXTREME_W:
		{
			nBeginIndex = EMSKILL_EXTREME_01;
			nEndIndex = EMSKILL_EXTREME_04;
		}
		break;
		//add class
	case GLCC_SCIENCE_M:
	case GLCC_SCIENCE_W:
		{
			nBeginIndex = EMSKILL_SCIENCE_01;
			nEndIndex = EMSKILL_SCIENCE_04;
		}
		break;

	case GLCC_ASSASSIN_M:
	case GLCC_ASSASSIN_W:
		{
			nBeginIndex = EMSKILL_ASSASSIN_01;
			nEndIndex = EMSKILL_ASSASSIN_04;
		}
		break;
	case GLCC_TESTING_M:
	case GLCC_TESTING_W:
		{
			nBeginIndex = EMSKILL_MAGICIAN_01;
			nEndIndex = EMSKILL_MAGICIAN_04;
		}
		break;
	};

	*pnBeginIndex = nBeginIndex;
	*pnEndIndex = nEndIndex;
}

void CSkillWindow::SortSkill ( EMCHARCLASS emCharClass, SNATIVEID sNativeIDArrayAll[EMSKILL_PC_CLASSNUM][GLSkillMan::MAX_CLASSSKILL], int nSkillCountAll[EMSKILL_PC_CLASSNUM] )
{
	int nBeginIndex = 0;
	int nEndIndex = 0;

	//	½ºÅ³ Index °¡Á®¿À?E
	GetSkillIndexRange ( emCharClass, &nBeginIndex, &nEndIndex );
	
	//	
	WORD wClass, wIndex;
	GLSkillMan::GetInstance().GetMaxSkill ( wClass, wIndex );

	for ( int i = nBeginIndex; i <= nEndIndex; i++ )
	{
		int nSkillCount = 0;
		SNATIVEID sNativeIDArray[GLSkillMan::MAX_CLASSSKILL];
		for ( int k = 0; k < GLSkillMan::MAX_CLASSSKILL; k++ )
		{
			sNativeIDArray[k] = NATIVEID_NULL();
		}
		
		//	Á¸ÀçÇÏ´Â ½ºÅ³ »Ì¾Æ¿À?E
		for ( int j = 0; j < wIndex; j++ )
		{
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( i, j );
			if ( pSkill )
			{
				sNativeIDArray[nSkillCount] = SNATIVEID(i,j);
				nSkillCount++;

				SCHARSKILL* pCharSkill = GLGaeaClient::GetInstance().GetCharacter()->GETLEARNED_SKILL ( SNATIVEID(i,j));
				if ( pCharSkill )
				{
					for ( int nLevel = 0; nLevel < pCharSkill->wLevel; nLevel++ )
					{
						SKILL::SLEARN_LVL sLVL = pSkill->m_sLEARN.sLVL_STEP[nLevel];
					}
				}
			}
		}

		//	±×·¹ÀÌµåº° Á¤·Ä
		//	¹öºúØÒÆ®
		SNATIVEID sTempID;
		for ( int x = 0; x < nSkillCount; x++ )
		for ( int y = 0; y < nSkillCount; y++ )
		{
			PGLSKILL pA = GLSkillMan::GetInstance().GetData ( sNativeIDArray[x].wMainID, sNativeIDArray[x].wSubID );
			PGLSKILL pB = GLSkillMan::GetInstance().GetData ( sNativeIDArray[y].wMainID, sNativeIDArray[y].wSubID );
			if ( pA->m_sBASIC.dwGRADE < pB->m_sBASIC.dwGRADE )
			{
				sTempID = sNativeIDArray[x];
				sNativeIDArray[x] = sNativeIDArray[y];
				sNativeIDArray[y] = sTempID;
			}
		}

        const int nIndex = i - nBeginIndex;
		nSkillCountAll[nIndex] = nSkillCount;
		memmove( sNativeIDArrayAll[nIndex], sNativeIDArray, sizeof ( SNATIVEID ) * GLSkillMan::MAX_CLASSSKILL );
	}
}

CUIControl*	CSkillWindow::CreateControl ( char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}


CBasicTextBox* CSkillWindow::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );

	return pStaticText;
}

void CSkillWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_pRestPoint )
	{
		const DWORD dwSkillPoint = GLGaeaClient::GetInstance().GetCharacter ()->m_dwSkillPoint;
		if ( dwSkillPoint != m_dwSkillPointBACK )
		{
			CString strTemp;
			strTemp.Format ( "%d", dwSkillPoint );
			m_pRestPoint->SetText ( strTemp );
			m_dwSkillPointBACK = dwSkillPoint;
		}
	}
}