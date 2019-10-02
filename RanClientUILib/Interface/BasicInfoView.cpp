#include "StdAfx.h"
#include "BasicInfoView.h"

#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "d3dfont.h"

#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBasicInfoView::CBasicInfoView () :
	m_pHP ( NULL ),
	m_pMP ( NULL ),
	m_pSP ( NULL ),
	m_pCP ( NULL ), //add cp
	m_pEXP ( NULL ),
	m_pHPText ( NULL ),
	m_pMPText ( NULL ),
	m_pSPText ( NULL ),
	m_pCPText ( NULL ), //add cp
	m_pEXPText ( NULL ),
	m_pHP0Text ( NULL ),
	m_pMP0Text ( NULL ),
	m_pSP0Text ( NULL ),
	m_pCP0Text ( NULL ), //add cp
	m_pEXP0Text ( NULL ),
	m_bFirstGap ( FALSE ),
	m_wHPBACK ( UINT_MAX ),
	m_wMPBACK ( UINT_MAX ),
	m_wSPBACK ( UINT_MAX ),
	m_wCPBACK ( UINT_MAX ), //add cp
	m_pLevelText ( NULL ),
	m_wLevelBACK(0),
	m_lEXPBACK( -1 )
{
}

CBasicInfoView::~CBasicInfoView ()
{
	m_wLevelBACK = 0;
}

CBasicTextBox* CBasicInfoView::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}

void CBasicInfoView::CreateSubControl ()
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	m_pHP = new CBasicProgressBar;
	m_pHP->CreateSub ( this, "BASIC_INFO_VIEW_HP" );
	m_pHP->CreateOverImage ( "BASIC_INFO_VIEW_HP_OVERIMAGE" );
	m_pHP->SetControlNameEx ( "HP Bar" );
	RegisterControl ( m_pHP );

	m_pMP = new CBasicProgressBar;
	m_pMP->CreateSub ( this, "BASIC_INFO_VIEW_MP" );
	m_pMP->CreateOverImage ( "BASIC_INFO_VIEW_MP_OVERIMAGE" );
	m_pMP->SetControlNameEx ( "MP Bar" );
	RegisterControl ( m_pMP );

	m_pSP = new CBasicProgressBar;
	m_pSP->CreateSub ( this, "BASIC_INFO_VIEW_SP" );
	m_pSP->CreateOverImage ( "BASIC_INFO_VIEW_SP_OVERIMAGE" );
	m_pSP->SetControlNameEx ( "SP Bar" );
	RegisterControl ( m_pSP );

	m_pCP = new CBasicProgressBar; //add cp
	m_pCP->CreateSub ( this, "BASIC_INFO_VIEW_CP" );
	m_pCP->CreateOverImage ( "BASIC_INFO_VIEW_CP_OVERIMAGE" );
	m_pCP->SetControlNameEx ( "CP Bar" );
	RegisterControl ( m_pCP );

	m_pEXP = new CBasicProgressBar;
	m_pEXP->CreateSub ( this, "BASIC_INFO_VIEW_EXP" );
	m_pEXP->CreateOverImage ( "BASIC_INFO_VIEW_EXP_OVERIMAGE" );
	m_pEXP->SetControlNameEx ( "EXP Bar" );
	RegisterControl ( m_pEXP );

	m_pHPText = new CBasicTextBox;
	m_pHPText->CreateSub ( this, "BASIC_INFO_VIEW_HP_TEXT", UI_FLAG_DEFAULT, HP_TEXT );
    m_pHPText->SetFont ( pFont8 );
	m_pHPText->SetTextAlign ( TEXT_ALIGN_RIGHT );
	m_pHPText->SetControlNameEx ( "HP Text" );	
	RegisterControl ( m_pHPText );

	m_pMPText = new CBasicTextBox;
	m_pMPText->CreateSub ( this, "BASIC_INFO_VIEW_MP_TEXT", UI_FLAG_DEFAULT, MP_TEXT );
    m_pMPText->SetFont ( pFont8 );
	m_pMPText->SetTextAlign ( TEXT_ALIGN_RIGHT );
	m_pMPText->SetControlNameEx ( "MP Text" );	
	RegisterControl ( m_pMPText );

	m_pSPText = new CBasicTextBox;
	m_pSPText->CreateSub ( this, "BASIC_INFO_VIEW_SP_TEXT", UI_FLAG_DEFAULT, SP_TEXT );
    m_pSPText->SetFont ( pFont8 );
	m_pSPText->SetTextAlign ( TEXT_ALIGN_RIGHT );
	m_pSPText->SetControlNameEx ( "SP Text" );	
	RegisterControl ( m_pSPText );

	m_pCPText = new CBasicTextBox; //add cp
	m_pCPText->CreateSub ( this, "BASIC_INFO_VIEW_CP_TEXT", UI_FLAG_DEFAULT, CP_TEXT );
    m_pCPText->SetFont ( pFont8 );
	m_pCPText->SetTextAlign ( TEXT_ALIGN_RIGHT );
	m_pCPText->SetControlNameEx ( "CP Text" );	
	RegisterControl ( m_pCPText );

	m_pEXPText = new CBasicTextBox;
	m_pEXPText->CreateSub ( this, "BASIC_INFO_VIEW_EXP_TEXT", UI_FLAG_DEFAULT, EXP_TEXT );
    m_pEXPText->SetFont ( pFont8 );
	m_pEXPText->SetTextAlign ( TEXT_ALIGN_RIGHT );
	m_pEXPText->SetControlNameEx ( "EXP Text " );	
	RegisterControl ( m_pEXPText );
	m_pHP0Text = CreateStaticControl 	( "BASIC_INFO_VIEW_HP0_TEXT", pFont8, TEXT_ALIGN_LEFT );
	m_pHP0Text->AddText 	( "HP", NS_UITEXTCOLOR::WHITE );

	m_pMP0Text = CreateStaticControl 	( "BASIC_INFO_VIEW_MP0_TEXT", pFont8, TEXT_ALIGN_LEFT );
	m_pMP0Text->AddText 	( "MP", NS_UITEXTCOLOR::WHITE );

	m_pSP0Text = CreateStaticControl 	( "BASIC_INFO_VIEW_SP0_TEXT", pFont8, TEXT_ALIGN_LEFT );
	m_pSP0Text->AddText 	( "SP", NS_UITEXTCOLOR::WHITE );

	m_pCP0Text = CreateStaticControl 	( "BASIC_INFO_VIEW_CP0_TEXT", pFont8, TEXT_ALIGN_LEFT );
	m_pCP0Text->AddText 	( "CP", NS_UITEXTCOLOR::WHITE );

	m_pEXP0Text = CreateStaticControl 	( "BASIC_INFO_VIEW_EXP0_TEXT", pFont8, TEXT_ALIGN_LEFT );
	m_pEXP0Text->AddText 	( "EXP", NS_UITEXTCOLOR::WHITE );
	
	CBasicTextBox* pLevelText = new CBasicTextBox;
	pLevelText->CreateSub ( this, "BASIC_LEVEL_DISPLAY_TEXT" );
    pLevelText->SetFont ( pFont8 );
	pLevelText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( pLevelText );
	m_pLevelText = pLevelText;	

}
void CBasicInfoView::SetHP ( DWORD dwNOW, DWORD dwMAX )
{
	GASSERT( m_pHPText && m_pHP );

	if ( m_wHPBACK != dwNOW )
	{
		m_wHPBACK = dwNOW;

		CString strTemp;
		strTemp.Format ( "%d", dwNOW );
		m_pHPText->SetOneLineText ( strTemp, NS_UITEXTCOLOR::WHITE );

		const float fPercent = float(dwNOW) / float(dwMAX);
		m_pHP->SetPercent ( fPercent );
	}
}

void CBasicInfoView::SetMP ( DWORD dwNOW, DWORD dwMAX )
{
	GASSERT( m_pMPText && m_pMP );

	if ( m_wMPBACK != dwNOW )
	{
		m_wMPBACK = dwNOW;

		CString strTemp;
		strTemp.Format ( "%d", dwNOW );
		m_pMPText->SetOneLineText ( strTemp, NS_UITEXTCOLOR::WHITE );

		const float fPercent = float(dwNOW) / float(dwMAX);
		m_pMP->SetPercent ( fPercent );
	}
}

void CBasicInfoView::SetSP ( DWORD dwNOW, DWORD dwMAX )
{
	GASSERT( m_pSPText && m_pSP );

	if ( m_wSPBACK != dwNOW )
	{
		m_wSPBACK = dwNOW;
        
		CString strTemp;
		strTemp.Format ( "%d", dwNOW );
		m_pSPText->SetOneLineText ( strTemp, NS_UITEXTCOLOR::WHITE );

		const float fPercent = float(dwNOW) / float(dwMAX);
		m_pSP->SetPercent ( fPercent );
	}
}

void CBasicInfoView::SetCP ( DWORD dwNOW, DWORD dwMAX ) //add cp
{
	GASSERT( m_pCPText && m_pCP );

	if ( m_wCPBACK != dwNOW )
	{
		m_wCPBACK = dwNOW;
        
		CString strTemp;
		strTemp.Format ( "%d", dwNOW );
		m_pCPText->SetOneLineText ( strTemp, NS_UITEXTCOLOR::WHITE );

		const float fPercent = float(dwNOW) / float(dwMAX);
		m_pCP->SetPercent ( fPercent );
	}
}

void CBasicInfoView::SetEXP( LONGLONG lNOW, LONGLONG lMAX )
{
	GASSERT( m_pEXPText && m_pEXP );

	if ( m_lEXPBACK != lNOW )
	{
		m_lEXPBACK = lNOW;

		CString strTemp;
		float fPercent(0.0f);
		if( lNOW )
		{
			fPercent = float(lNOW) / float(lMAX);	
		}

		strTemp.Format ( "%2.2f%%", fPercent * 100.0f );
		m_pEXPText->SetOneLineText ( strTemp, NS_UITEXTCOLOR::WHITE );

		m_pEXP->SetPercent ( fPercent );
	}
}

void CBasicInfoView::CheckMouseState ()
{
	const DWORD dwMsg = GetMessageEx ();
	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{
		if( UIMSG_LB_DUP & dwMsg )
		{
			// 윈도우를 디폴트 포지션으로 이동
			AddMessageEx( UIMSG_BASICINFOVIEW_LBDUP );
			SetDiffuse ( D3DCOLOR_ARGB ( 0xFF, 0xFF, 0xFF, 0xFF ) );
			return ;
		}
		
		if ( dwMsg & UIMSG_LB_DOWN )
		{
			//	단독 컨트롤로 등록하고,
			SetExclusiveControl();	

			//	최초 포지션 갭을 기록한다.
			if ( !m_bFirstGap )
			{
				UIRECT rcPos = GetGlobalPos ();
				m_vGap.x = m_PosX - rcPos.left;
				m_vGap.y = m_PosY - rcPos.top;
				m_bFirstGap = TRUE;

				SetDiffuse ( D3DCOLOR_ARGB ( 0xB4, 0xFF, 0xFF, 0xFF ) );
			}
		}
		else if ( CHECK_LB_UP_LIKE ( dwMsg ) )
		{
			//	단독 컨트롤을 해제하고
			ResetExclusiveControl();
			//	최초 포지션갭을 해제한다.
			m_bFirstGap = FALSE;				

			SetDiffuse ( D3DCOLOR_ARGB ( 0xFF, 0xFF, 0xFF, 0xFF ) );
		}
	}
	//	컨트롤 영역밖에서 버튼을 떼는 경우가 발생하더라도
	else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
	{								
		//	단독 컨트롤을 해제하고,
		ResetExclusiveControl();
		//	최초 포지션갭을 해제한다.
		m_bFirstGap = FALSE;					

		SetDiffuse ( D3DCOLOR_ARGB ( 0xFF, 0xFF, 0xFF, 0xFF ) );
	}
}


void CBasicInfoView::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	m_bCHECK_MOUSE_STATE = false;

	m_PosX = x;
	m_PosY = y;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( IsExclusiveSelfControl() )
	{
		SetGlobalPos ( D3DXVECTOR2 ( x - m_vGap.x, y - m_vGap.y ) );
	}

	const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();
	SetHP ( sCharData.m_sHP.dwNow, sCharData.m_sHP.dwMax );
	SetMP ( sCharData.m_sMP.dwNow, sCharData.m_sMP.dwMax );
	SetSP ( sCharData.m_sSP.dwNow, sCharData.m_sSP.dwMax );
	SetCP ( sCharData.m_sCP.dwNow, sCharData.m_sCP.dwMax );//add cp
	SetEXP ( sCharData.m_sExperience.lnNow, sCharData.m_sExperience.lnMax );
	const WORD& wLevel = GLGaeaClient::GetInstance().GetCharacter()->m_wLevel;

	if( m_wLevelBACK < wLevel )
	{
		m_wLevelBACK = wLevel;

		CUIGroup::Update( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		CString strLevel;
		strLevel.Format( "Lv.%d", m_wLevelBACK );	
		m_pLevelText->SetOneLineText( strLevel, NS_UITEXTCOLOR::WHITE );
	}
}

void CBasicInfoView::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( !m_bCHECK_MOUSE_STATE )
	{
		CheckMouseState ();
		m_bCHECK_MOUSE_STATE = true;
	}

	switch ( ControlID )
	{
	case HP_TEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();

				CString strText;
				strText.Format ( "%d/%d", sCharData.m_sHP.dwNow, sCharData.m_sHP.dwMax );
	
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strText, NS_UITEXTCOLOR::DEFAULT );
			}
		}
		break;

	case MP_TEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();

				CString strText;
				strText.Format ( "%d/%d", sCharData.m_sMP.dwNow, sCharData.m_sMP.dwMax );
	
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strText, NS_UITEXTCOLOR::DEFAULT );
			}
		}
		break;

	case SP_TEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();

				CString strText;
				strText.Format ( "%d/%d", sCharData.m_sSP.dwNow, sCharData.m_sSP.dwMax );
	
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strText, NS_UITEXTCOLOR::DEFAULT );
			}
		}
		break;

	case CP_TEXT: //add cp
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();

				CString strText;
				strText.Format ( "%d/%d", sCharData.m_sCP.dwNow, sCharData.m_sCP.dwMax );
	
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strText, NS_UITEXTCOLOR::DEFAULT );
			}
		}
		break;

	case EXP_TEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();

				CString strText;
				strText.Format( "%I64d/%I64d", sCharData.m_sExperience.lnNow, sCharData.m_sExperience.lnMax );

				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strText, NS_UITEXTCOLOR::DEFAULT );
			}
		}
		break;

/*	case LEVEL_TEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();

				CString strText;
				strText.Format( "%d", sCharData.m_wLevel );

				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strText, NS_UITEXTCOLOR::DEFAULT );
			}
		}
		break; */

	}
}