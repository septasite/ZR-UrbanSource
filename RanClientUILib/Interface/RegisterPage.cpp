#include "StdAfx.h"
#include "RegisterPage.h"
#include "BasicTextButton.h"
#include "GameTextControl.h"
#include "BasicTextBoxEx.h"
#include "UITextControl.h"
#include "BasicLineBox.h"
#include "OuterInterface.h"
#include "ModalWindow.h"
#include "s_NetClient.h"
#include "RANPARAM.h"
#include "DxGlobalStage.h"
#include "DxInputString.h"
#include "DebugSet.h"

#include "../enginelib/Common/StringUtils.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUIlib/GUInterface/UIEditBoxMan.h"
#include "../EngineUIlib/GUInterface/UIKeyCheck.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int	CRegisterPage::nLIMIT_ID = 12;
int	CRegisterPage::nLIMIT_PW = 12;
int	CRegisterPage::nLIMIT_PW2 = 12;
int	CRegisterPage::nLIMIT_EMAIL = 30;
int	CRegisterPage::nLIMIT_CP = 7;

CRegisterPage::CRegisterPage ()
	: m_pRandTextBox(NULL)
	, m_nRandPassNumber(0)
	, m_nRPUpdateCnt(0)
{
	memset( m_szRandomString, 0, sizeof( m_szRandomString ) );
}

CRegisterPage::~CRegisterPage ()
{
}

void CRegisterPage::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	const int nBUTTONSIZE = CBasicTextButton::SIZE18;

	CBasicTextBox* pTextBox = NULL;
	pTextBox = CreateStaticControl ( "REGISTER_PAGE_ID", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ( "REGISTER_PAGE_IDPW", 0 ) );
	pTextBox = CreateStaticControl ( "REGISTER_PAGE_PW", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ( "REGISTER_PAGE_IDPW", 1 ) );
	pTextBox = CreateStaticControl ( "REGISTER_PAGE_PW2", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ( "REGISTER_PAGE_IDPW", 2 ) );
	pTextBox = CreateStaticControl ( "REGISTER_PAGE_EMAIL", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );
	pTextBox->SetOneLineText ( (char*)ID2GAMEWORD ( "REGISTER_PAGE_IDPW", 3 ) );


	m_pRandTextBox = CreateStaticControl ( "REGISTER_PAGE_CP", pFont9, NS_UITEXTCOLOR::WHITE, TEXT_ALIGN_LEFT );

	
	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "REGISTER_PAGE_ID_BACK" );
		RegisterControl ( pBasicLineBox );

		pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "REGISTER_PAGE_PW_BACK" );
		RegisterControl ( pBasicLineBox );

		
		pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "REGISTER_PAGE_PW2_BACK" );
		RegisterControl ( pBasicLineBox );

		
		pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "REGISTER_PAGE_EMAIL_BACK" );
		RegisterControl ( pBasicLineBox );

		pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_OUTER", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxOuter ( "REGISTER_PAGE_CP_BACK" );
		RegisterControl ( pBasicLineBox );

	}

	{
		CUIEditBoxMan* pEditBoxMan = new CUIEditBoxMan;
		pEditBoxMan->CreateSub ( this, "REGISTER_EDITMAN", UI_FLAG_DEFAULT, REGISTER_EDIT_MAN );
		pEditBoxMan->CreateEditBox ( REGISTER_EDIT_ID, "REGISTER_EDIT_ID", "REGISTER_CARRAT", TRUE, UINT_MAX, pFont9, nLIMIT_ID );
		pEditBoxMan->CreateEditBox ( REGISTER_EDIT_PW, "REGISTER_EDIT_PW", "REGISTER_CARRAT", TRUE, UINT_MAX, pFont9, nLIMIT_PW );
		pEditBoxMan->CreateEditBox ( REGISTER_EDIT_PW2, "REGISTER_EDIT_PW2", "REGISTER_CARRAT", TRUE, UINT_MAX, pFont9, nLIMIT_PW2 );
		pEditBoxMan->CreateEditBox ( REGISTER_EDIT_EMAIL, "REGISTER_EDIT_EMAIL", "REGISTER_CARRAT", TRUE, UINT_MAX, pFont9, nLIMIT_EMAIL );

		pEditBoxMan->CreateEditBox ( REGISTER_EDIT_CP, "REGISTER_EDIT_RP", "REGISTER_CARRAT", TRUE, UINT_MAX, pFont9, nLIMIT_CP );

		pEditBoxMan->SetHide ( REGISTER_EDIT_PW, TRUE );
		pEditBoxMan->SetHide ( REGISTER_EDIT_PW2, TRUE );
		RegisterControl( pEditBoxMan );
		m_pEditBoxMan = pEditBoxMan;
	}

	CBasicTextButton* pOKButton = new CBasicTextButton;
	pOKButton->CreateSub ( this, "BASIC_TEXT_BUTTON18", UI_FLAG_XSIZE, REGISTER_OK );
	pOKButton->CreateBaseButton ( "REGISTER_PAGE_OK", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "REGISTER_PAGE_OKCANCEL", 0 ) );
	pOKButton->SetShortcutKey ( DIK_RETURN, DIK_NUMPADENTER );
	RegisterControl ( pOKButton );

	CBasicTextButton* pQuitButton = new CBasicTextButton;
	pQuitButton->CreateSub ( this, "BASIC_TEXT_BUTTON18", UI_FLAG_XSIZE, REGISTER_CANCEL );
	pQuitButton->CreateBaseButton ( "REGISTER_PAGE_CANCEL", nBUTTONSIZE, CBasicButton::CLICK_FLIP, (char*)ID2GAMEWORD ( "REGISTER_PAGE_OKCANCEL", 1 ) );
	pQuitButton->SetShortcutKey ( DIK_ESCAPE );
	RegisterControl ( pQuitButton );

	//CreateControl ( "REGISTER_BOTTOM" );

	//LoadIDSaveButton ();
}	

void CRegisterPage::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
	if ( !pNetClient->IsOnline() )		//네트워크 연결이 끊어진 경우
	{
		if ( !COuterInterface::GetInstance().IsVisibleGroup ( MODAL_WINDOW_OUTER ) )
		{
			if( !COuterInterface::GetInstance().IsLoginCancel() )
			{
				DoModalOuter ( ID2GAMEEXTEXT ("REGISTERSTAGE_1"), MODAL_INFOMATION, OK, OUTER_MODAL_RECONNECT );
			}
		}
	}
	else
	{
		if (m_nRandPassNumber == -1 )
		{
			CString strTemp;
			StringCchCopy( m_szRandomString, 7, pNetClient->GetRandomString()  );
			strTemp.Format( "Captcha %s", m_szRandomString  );
			m_nRandPassNumber = 1;
			if( m_pRandTextBox ) m_pRandTextBox->SetOneLineText( strTemp );	
		}
		else
		{
			if( m_nRPUpdateCnt++ > 5 && m_nRandPassNumber == 0 )
			{
				pNetClient->SndRequestRandomKey();
				m_nRandPassNumber = -1;
				m_nRPUpdateCnt = 0;
			}
		}
	}

	//	탭 이동
	if ( m_pEditBoxMan )
	{
		CUIControl* pParent = m_pEditBoxMan->GetTopParent ();
		if ( !pParent )	pParent = this;	//	만약 이클래스가 최상위 컨트롤인 경우
		BOOL bFocus = ( pParent->IsFocusControl() );

		if ( bFocus )
		{
			if ( UIKeyCheck::GetInstance()->Check ( DIK_TAB, DXKEY_DOWN ) )
			{
				m_pEditBoxMan->GoNextTab ();
			}
		}
	}
}

void CRegisterPage::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindow::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case REGISTER_OK:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				SetMessageEx( dwMsg &= ~UIMSG_KEY_FOCUSED ); // Focus 문제로 메세지 삭제
				
				CString strID = m_pEditBoxMan->GetEditString ( REGISTER_EDIT_ID );
				CString strPW = m_pEditBoxMan->GetEditString ( REGISTER_EDIT_PW );
				CString strPW2 = m_pEditBoxMan->GetEditString ( REGISTER_EDIT_PW2 );
				CString strEM = m_pEditBoxMan->GetEditString ( REGISTER_EDIT_EMAIL );
				CString strRP;
				strRP = m_pEditBoxMan->GetEditString ( REGISTER_EDIT_CP );


				if ( !strID.GetLength () || !strPW.GetLength () || !strPW2.GetLength () )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTERSTAGE_4" ) );
					return ;
				}
				
				if ( !strEM.GetLength () )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTERSTAGE_5" ) );
					return ;
				}
				
				if( !strRP.GetLength () )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTERSTAGE_6" ) );
					return ;
				}
				
				if ( !CheckString ( strID ) )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTER_PAGE_ID_ERROR" ) );
					return ;
				}

				if ( !CheckString ( strPW ) )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTER_PAGE_PW_ERROR" ) );
					return ;
				}
				
				if ( !CheckString ( strPW2 ) )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTER_PAGE_PW2_ERROR" ) );
					return ;
				}		
				
				if ( !CheckEmail ( strEM ) )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTER_PAGE_EM_ERROR" ) );
					return ;
				}	

				if ( !CheckString ( strRP ) )
				{
					DoModalOuter ( ID2GAMEEXTEXT ( "REGISTER_PAGE_CP_ERROR" ) );
					return ;
				}
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
				
				CString strCheck;
				strCheck.Format("%s",m_szRandomString);
				if ( strCheck == strRP )
				{
					 pNetClient->SndRegister( strID, strPW, strPW2, strEM, strRP );									 DoModalOuter ( ID2GAMEEXTEXT ("REGISTERSTAGE_7") );
				}
				else
				{
					DoModalOuter ( ID2GAMEEXTEXT ("REGISTER_PAGE_CP_ERROR"), MODAL_INFOMATION, OK, OUTER_MODAL_REGISTERTOLOGIN );
				}
			}
		}
		break;

	case REGISTER_CANCEL:
		{
			if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
				if( pNetClient->IsOnline() == true )
				{
					pNetClient->CloseConnect();
					COuterInterface::GetInstance().SetCancelToLogin();
				}

				COuterInterface::GetInstance().ToSelectServerPage ( GetWndID () );
			}
		}
		break;
	};
}
BOOL CRegisterPage::CheckEmail( CString strTemp )
{	
	strTemp = strTemp.Trim();

	// 문자열 체크 - 들어가면 안되는 특수문자 : ~!@#$%^&*+|":?><\=`',.;[]{}()
	if( !STRUTIL::isValidEmailAddress( strTemp.GetString() ) )
	{
		DoModalOuter ( ID2GAMEEXTEXT ( "REGISTERSTAGE_5" ), MODAL_INFOMATION, OK );		
		return FALSE;
	}

    return TRUE;
}

BOOL CRegisterPage::CheckString( CString strTemp )
{	
	strTemp = strTemp.Trim();

	// 문자열 체크 - 들어가면 안되는 특수문자 : ~!@#$%^&*+|":?><\=`',.;[]{}()
	if( STRUTIL::CheckString( strTemp ) )
	{
		DoModalOuter ( ID2GAMEEXTEXT ( "REGISTERSTAGE_4" ), MODAL_INFOMATION, OK );		
		return FALSE;
	}

    return TRUE;
}

void CRegisterPage::ResetAll ()
{
	m_pEditBoxMan->EndEdit ();

	m_pEditBoxMan->ClearEdit ( REGISTER_EDIT_ID );
	m_pEditBoxMan->ClearEdit ( REGISTER_EDIT_PW );
	m_pEditBoxMan->ClearEdit ( REGISTER_EDIT_PW2 );
	m_pEditBoxMan->ClearEdit ( REGISTER_EDIT_EMAIL );

	m_pEditBoxMan->ClearEdit ( REGISTER_EDIT_CP );

	m_nRandPassNumber = 0;
	m_szRandomString[7] = 0;
	m_nRPUpdateCnt = 0;


	m_pEditBoxMan->Init();
	m_pEditBoxMan->BeginEdit();

	if( m_pEditBoxMan->IsMODE_NATIVE() )
	{
		m_pEditBoxMan->DoMODE_TOGGLE();
	}
}

void CRegisterPage::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle( bVisible );

	if ( bVisible )
	{

		ResetAll();

		if( m_pRandTextBox ) m_pRandTextBox->ClearText();
	}
	else
	{
		m_pEditBoxMan->EndEdit ();

		CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient();
		pNetClient->ResetRandomPassNumber();
	}
}

CBasicButton* CRegisterPage::CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, CBasicButton::RADIO_FLIP );
	pButton->SetControlNameEx ( szButton );
	RegisterControl ( pButton );

	return pButton;
}

void CRegisterPage::SetCharToEditBox( TCHAR cKey )
{
	if( !m_pEditBoxMan ) return;
	
	CString strTemp;

	UIGUID nID = m_pEditBoxMan->GetBeginEditBox();

	strTemp = m_pEditBoxMan->GetEditString( nID );
	strTemp += cKey;

	m_pEditBoxMan->SetEditString( nID, strTemp );
}

void CRegisterPage::DelCharToEditBox()
{
	if( !m_pEditBoxMan ) return;

	CString strTemp;

	UIGUID nID = m_pEditBoxMan->GetBeginEditBox();

	strTemp = m_pEditBoxMan->GetEditString( nID );
	INT nLenth = strTemp.GetLength();
	strTemp = strTemp.Left( nLenth - 1 );

	m_pEditBoxMan->SetEditString( nID, strTemp );
}

void CRegisterPage::GoNextTab()
{
	if( m_pEditBoxMan )
		m_pEditBoxMan->GoNextTab();
}