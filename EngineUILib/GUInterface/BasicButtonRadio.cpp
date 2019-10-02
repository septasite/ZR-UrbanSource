#include "StdAfx.h"
#include "BasicButtonRadio.h"
#include "UIKeyCheck.h"
#include "BasicTextBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const float CBasicButtonRadio::fBUTTON_CLICK = 1.0f;

CBasicButtonRadio::CBasicButtonRadio():
	m_wFlipMode(NOT_READY),
	m_bDown(FALSE),
	m_bMouseIn(FALSE),
	m_bFlip ( FALSE ),
	m_bOnBack ( FALSE ),
	m_bUseDynamic ( FALSE ),
	m_bUseGlobalAction ( FALSE ),
	m_KeyCode ( NULL ),
	m_KeyCodeEx ( NULL ),
	m_pImageFlip ( NULL ),
	m_pMouseOver ( NULL ),
	m_pButtonText ( NULL )
{
}

CBasicButtonRadio::~CBasicButtonRadio()
{
}

void CBasicButtonRadio::CreateMouseOver ( char* KeyValue )
{	
	if ( m_wFlipMode == NOT_READY )
	{
		GASSERT ( 0 && "CreateFlip() 함수 이후에 호출해야 합니다." );
		return ;
	}
	
	CUIControl* pMouseOver = new CUIControl;
	pMouseOver->CreateSub ( this, KeyValue );
	pMouseOver->SetVisibleSingle ( FALSE );
	RegisterControl ( pMouseOver );
	m_pMouseOver = pMouseOver;
}

void CBasicButtonRadio::CreateRadioWithText ( CD3DFontPar* pFont, int nTextBoxSize, int nTextAlign )
{
	m_pImage = new CUIControl;
	m_pImage->CreateSub ( this,"BASIC_RADIO_BUTTON" );
	m_pImage->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pImage );

	m_pImageFlip = new CUIControl;
	m_pImageFlip->CreateSub ( this,"BASIC_RADIO_BUTTON_FLIP" );
	m_pImageFlip->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pImageFlip );

	std::string strTextBox[SIZE_TEXT_ALL] = 
	{
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_10",
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_20",
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_30",
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_40",
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_50",
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_60",
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_70",
		"BASIC_RADIO_BUTTON_FLIP_TEXTBOX_80",
	};

	m_pButtonText = new CBasicTextBox;
	m_pButtonText->CreateSub ( this, strTextBox[nTextBoxSize].c_str(), UI_FLAG_DEFAULT );
	m_pButtonText->SetFont ( pFont );
	m_pButtonText->SetTextAlign ( nTextAlign );	
	RegisterControl ( m_pButtonText );
}

void CBasicButtonRadio::Reset()
{
	CUIControl::Reset();
}

void CBasicButtonRadio::SetFlip ( BOOL bFlip )
{
	if ( m_pImageFlip ) 
		m_pImageFlip->SetVisibleSingle ( bFlip );

	if ( m_pMouseOver && bFlip )
	{
		m_pMouseOver->SetVisibleSingle ( FALSE );
	}

	if ( IsUseDynamic() )
	{
		CUIControl::SetDiffuse ( D3DCOLOR_ARGB ( 255, 255, 255, 255 ) );
		if ( m_bFlip )
		{
			CUIControl::SetDiffuse ( D3DCOLOR_ARGB ( 0, 255, 255, 255 ) );
			SetFlipPosition ();
		}
	}

	m_bFlip = bFlip;
}

void CBasicButtonRadio::TranslateMouseMessage ( DWORD dwMsg )
{	
	BOOL bMouseOver = FALSE;
	if ( CHECK_MOUSE_IN ( dwMsg ) )	bMouseOver = TRUE;
	if ( m_pMouseOver )	m_pMouseOver->SetVisibleSingle ( bMouseOver );

	if ( CHECK_MOUSE_IN_LBDOWNLIKE ( dwMsg ) )
	{
		SetFlip ( TRUE );
	}			
}

void CBasicButtonRadio::SetFlipPosition ()
{
	if ( m_pImageFlip )
	{
		if ( !IsFlip () )
		{
			const UIRECT& rcBackPos = GetGlobalPos ();
			m_pImageFlip->SetGlobalPos ( D3DXVECTOR2 ( rcBackPos.left + fBUTTON_CLICK, rcBackPos.top + fBUTTON_CLICK ) );
		}
	}
}

void CBasicButtonRadio::ResetFlipPosition ()
{
	if ( m_pImageFlip )
	{
		if ( IsFlip () )
		{
			const UIRECT& rcBackPos = GetGlobalPos ();
			m_pImageFlip->SetGlobalPos ( D3DXVECTOR2 ( rcBackPos.left, rcBackPos.top ) );
		}
	}
}

void CBasicButtonRadio::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( IsUseDynamic() )
	{
		ResetFlipPosition ();
	}

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_pMouseOver )	m_pMouseOver->SetVisibleSingle ( FALSE );
	
	if ( bFirstControl )
	{		
		CUIControl* pParent = GetTopParent ();
		BOOL bFocusControl = ( pParent && pParent->IsFocusControl() ) ? TRUE : FALSE;
		if ( bFocusControl || m_bUseGlobalAction )
		{
			TranslateMouseMessage ( GetMessageEx () );
		}

		if ( bFocusControl )
		{
			if ( m_KeyCode || m_KeyCodeEx )
			{
				if ( UIKeyCheck::GetInstance()->Check ( m_KeyCode, DXKEY_DOWN ) )
				{
					AddMessageEx ( UIMSG_KEY_FOCUSED );
				}

				if ( UIKeyCheck::GetInstance()->Check ( m_KeyCodeEx, DXKEY_DOWN ) )
				{
					AddMessageEx ( UIMSG_KEY_FOCUSED );
				}
			}
		}
	}
}

void CBasicButtonRadio::SetOneLineText ( CString strTemp, D3DCOLOR dwTextColor /*= NS_UITEXTUTIL::ENABLE*/ )
{
	if ( m_pButtonText ) m_pButtonText->SetOneLineText ( strTemp, dwTextColor );
}