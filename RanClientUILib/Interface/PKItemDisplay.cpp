#include "StdAfx.h"
#include "PKItemDisplay.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "d3dfont.h"

#include "PKItemType.h"
#include "InnerInterface.h"
#include "DxViewPort.h"

CPKItemDisplay::CPKItemDisplay ()/* :
	m_pPkWinText ( NULL ),
	m_dwPkWinBACK(0) */
{
}

CPKItemDisplay::~CPKItemDisplay ()
{
	m_dwPkWinBACK = 0; 
}

void CPKItemDisplay::CreateSubControl ()
{	
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CString strKeyword[MAXTYPE] = 
	{
		"PK_ITEM_MONSTERKILL",
		"PK_ITEM_ULTRAKILL",
		"PK_ITEM_TRIPLEKILL",
		"PK_ITEM_DOUBLEKILL",

		"PK_ITEM_GODLIKE",
		"PK_ITEM_FIRSTBLOOD"
	};
/*	CBasicTextBox* pPkWinText = new CBasicTextBox;
	pPkWinText->CreateSub ( this, "BASIC_PKWIN_DISPLAY_TEXT" );
    pPkWinText->SetFont ( pFont8 );
	pPkWinText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( pPkWinText );
	m_pPkWinText = pPkWinText;	*/
   
		for ( int i = 0; i < MAXTYPE; ++i )
	{
	//	CBasicTextBox* pPkWinText = new CBasicTextBox;
		m_pQI_TYPE[i] = new CPKItemType;
		m_pQI_TYPE[i]->CreateSub ( this, strKeyword[i].GetString(), UI_FLAG_DEFAULT, FIRSTBLOOD + i );
		m_pQI_TYPE[i]->CreateSubControl ( strKeyword[i] );
		m_pQI_TYPE[i]->SetVisibleSingle ( FALSE );
	/*	m_pPkWinText[i]->CreateSub ( this,strKeyword[i].GetString(), UI_FLAG_DEFAULT, FIRSTBLOOD + i );
		RegisterControl ( m_pPkWinText[i] ); */
	//	m_pPkWinText[i]->SetVisibleSingle ( FALSE );
		m_pQI_TYPE[i]->SetUseRender ( FALSE );
		m_pQI_TYPE[i]->STOP ();
		m_pQI_TYPE[i]->RESET ();		
		RegisterControl ( m_pQI_TYPE[i] );
	

		m_QI_TYPE_KEEP[i] = new CUIControl;
		m_QI_TYPE_KEEP[i]->CreateSub ( this, strKeyword[i].GetString() );
		m_QI_TYPE_KEEP[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_QI_TYPE_KEEP[i] );
	}

	m_pPositionControl = new CUIControl;
	m_pPositionControl->CreateSub ( this, "PK_ITEM_POSITION" );
	m_pPositionControl->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pPositionControl );	

}

bool	CPKItemDisplay::START ( UIGUID cID )
{
	if ( cID < FIRSTBLOOD || GODLIKE < cID ) return false;
	
	int nIndex = cID - FIRSTBLOOD;
	const DWORD& dwPkWin = GLGaeaClient::GetInstance().GetCharacter()->m_dwPkWin;
	if( m_dwPkWinBACK < dwPkWin )
	{
		m_dwPkWinBACK = dwPkWin;

		CString strPkWin;
		strPkWin.Format( "%d", m_dwPkWinBACK );	
		m_pPkWinText[nIndex]->SetOneLineText( strPkWin, NS_UITEXTCOLOR::RED  );
		m_pPkWinText[nIndex]->SetVisibleSingle ( TRUE );
	} 
	m_pQI_TYPE[nIndex]->SetVisibleSingle ( TRUE );
	m_pQI_TYPE[nIndex]->START ();

	return true;
}

bool	CPKItemDisplay::RESET ( UIGUID cID )
{
	if ( cID < FIRSTBLOOD || GODLIKE < cID ) return false;

	int nIndex = cID - FIRSTBLOOD;	
	m_pQI_TYPE[nIndex]->RESET ();

    return true;
}

bool	CPKItemDisplay::STOP ( UIGUID cID )
{
	if ( cID < FIRSTBLOOD || GODLIKE < cID ) return false;

	int nIndex = cID - FIRSTBLOOD;	
	m_pQI_TYPE[nIndex]->STOP ();
	m_pQI_TYPE[nIndex]->SetVisibleSingle ( FALSE );

	return true;
}

void CPKItemDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

//	const DWORD& dwPkWin = GLGaeaClient::GetInstance().GetCharacter()->m_dwPkWin;

/*	if( m_dwPkWinBACK < dwPkWin )
	{
		m_dwPkWinBACK = dwPkWin; */

		CUIGroup::Update( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

/*		CString strPkWin;
		strPkWin.Format( "%d", m_dwPkWinBACK );	
		m_pPkWinText[nIndex]->SetOneLineText( strPkWin, NS_UITEXTCOLOR::RED /*PLUSOPTION );
		m_pPkWinText[nIndex]->SetVisibleSingle ( TRUE );
	} */

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	D3DXVECTOR3 vPos = GLGaeaClient::GetInstance().GetCharacter()->GetPosBodyHeight();

	static D3DXVECTOR3 vScreenBack;
	D3DXVECTOR3 vScreen = DxViewPort::GetInstance().ComputeVec3Project ( &vPos, NULL );

	// 마우스 움직임에 흔들림을 보정한다.
	if( abs( vScreenBack.x - vScreen.x ) < 1.0f )
	{
		vScreen.x = vScreenBack.x;
	}
	
	bool bPLAYING( false );
	bool bKEEPING( false );

	for ( int i = 0; i < MAXTYPE; ++i )
	{
		const UIRECT& rcOriginPos = m_pQI_TYPE[i]->GetGlobalPos ();

		D3DXVECTOR2 vPos;
		vPos.x = floor(vScreen.x - ( rcOriginPos.sizeX * 0.5f ));
		vPos.y = m_pPositionControl->GetGlobalPos().top;

		if ( m_pQI_TYPE[i]->ISPLAYING () )
		{
			m_pQI_TYPE[i]->SetGlobalPos ( vPos );

			bPLAYING = true;
		}
		else
		{
			STOP ( FIRSTBLOOD + i );
		}

		if ( m_QI_TYPE_KEEP[i]->IsVisible () )
		{
			m_QI_TYPE_KEEP[i]->SetGlobalPos ( vPos );

			bKEEPING = true;
		}
	}
//	SetPkRank();
	vScreenBack = vScreen;

	if ( !bPLAYING && !bKEEPING ) CInnerInterface::GetInstance().HideGroup ( GetWndID () );
}

void CPKItemDisplay::ALLSTOP ()
{
	for ( int i = 0; i < MAXTYPE; ++i )
	{
		m_pQI_TYPE[i]->STOP ();
		m_pQI_TYPE[i]->RESET ();
		m_pQI_TYPE[i]->SetVisibleSingle ( FALSE );

		m_QI_TYPE_KEEP[i]->SetVisibleSingle ( FALSE );
	}

	CInnerInterface::GetInstance().HideGroup ( GetWndID () );
}

bool CPKItemDisplay::KEEP_START ( UIGUID cID )
{
	if ( cID < FIRSTBLOOD || GODLIKE < cID ) return false;
	
	int nIndex = cID - FIRSTBLOOD;	
	
	
	const DWORD& dwPkWin = GLGaeaClient::GetInstance().GetCharacter()->m_dwPkWin;
	if( m_dwPkWinBACK < dwPkWin )
	{
		m_dwPkWinBACK = dwPkWin;

		CString strPkWin;
		strPkWin.Format( "%d", m_dwPkWinBACK );	
		m_pPkWinText[nIndex]->SetOneLineText( strPkWin, NS_UITEXTCOLOR::RED );
		m_pPkWinText[nIndex]->SetVisibleSingle ( TRUE );
	} 
	m_QI_TYPE_KEEP[nIndex]->SetVisibleSingle ( TRUE );
	m_QI_TYPE_KEEP[nIndex]->SetDiffuseAlpha ( 50 );

	return true;
}

void CPKItemDisplay::KEEP_STOP ()
{
	for ( int i = 0; i < MAXTYPE; ++i )
	{
		m_QI_TYPE_KEEP[i]->SetVisibleSingle ( FALSE );
	//	m_pPkWinText[i]->SetVisibleSingle ( FALSE );
	}
}
/*CBasicTextBox* CPKItemDisplay::CreateTextBox ( const char* szControl )
{
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, szControl );
    pTextBox->SetFont ( pFont8 );
	pTextBox->SetTextAlign ( TEXT_ALIGN_RIGHT );
	RegisterControl ( pTextBox );

	return pTextBox;
} */