#include "StdAfx.h"
#include "ProgressDisplayCtf.h"
#include "ProgressTypeCtf.h"
#include "InnerInterface.h"
#include "GLGaeaClient.h"
#include "DxViewPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const float fKeepTime = 5.0f;

CProgressDisplayCtf::CProgressDisplayCtf ()
{
}

CProgressDisplayCtf::~CProgressDisplayCtf ()
{
}

void CProgressDisplayCtf::CreateSubControl ()
{
	CString strKeyword[MAX_TYPE] = 
	{
		"PROGRESS_DISPLAY_CTF_TEXT_CAPTURED_BY_0",
		"PROGRESS_DISPLAY_CTF_TEXT_START",
		"PROGRESS_DISPLAY_CTF_TEXT_CAPTURED_BY_2",
		"PROGRESS_DISPLAY_CTF_SCHOOL_0",
		"PROGRESS_DISPLAY_CTF_SCHOOL_1",
		"PROGRESS_DISPLAY_CTF_SCHOOL_2",
		"PROGRESS_DISPLAY_CTF_TEXT_CAPTURED_BY_1",
		"PROGRESS_DISPLAY_CTF_TEXT_STOP"
	};

	m_pCtfBack_TYPE = new CProgressTypeCtf;
	m_pCtfBack_TYPE->CreateSub ( this, "PROGRESS_DISPLAY_CTF_BACK_1", UI_FLAG_DEFAULT, PROGRESS_DISPLAY_CTF_BACK_1 );
	m_pCtfBack_TYPE->CreateSubControl ( "PROGRESS_DISPLAY_CTF_BACK_1" );
	m_pCtfBack_TYPE->SetVisibleSingle ( FALSE );
	m_pCtfBack_TYPE->SetUseRender ( FALSE );
	m_pCtfBack_TYPE->STOP ();
	m_pCtfBack_TYPE->RESET ();		
	RegisterControl ( m_pCtfBack_TYPE );

	m_pCtfBack_KEEP = new CUIControl;
	m_pCtfBack_KEEP->CreateSub ( this, "PROGRESS_DISPLAY_CTF_BACK_1" );
	m_pCtfBack_KEEP->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pCtfBack_KEEP );

	for ( int i = 0; i < MAX_TYPE; ++i )
	{
		m_pCtfText_TYPE[i] = new CProgressTypeCtf;
		m_pCtfText_TYPE[i]->CreateSub ( this, strKeyword[i].GetString(), UI_FLAG_DEFAULT, CTF_CAPTURED_SG + i );
		m_pCtfText_TYPE[i]->CreateSubControl ( strKeyword[i] );
		m_pCtfText_TYPE[i]->SetVisibleSingle ( FALSE );
		m_pCtfText_TYPE[i]->SetUseRender ( FALSE );
		m_pCtfText_TYPE[i]->STOP ();
		m_pCtfText_TYPE[i]->RESET ();		
		RegisterControl ( m_pCtfText_TYPE[i] );

		m_pCtfText_KEEP[i] = new CUIControl;
		m_pCtfText_KEEP[i]->CreateSub ( this, strKeyword[i].GetString() );
		m_pCtfText_KEEP[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pCtfText_KEEP[i] );
	}
}

bool	CProgressDisplayCtf::START ( UIGUID cID )
{
	if ( cID < CTF_CAPTURED_SG || CTF_END < cID ) return false;

	int nIndex = cID - CTF_CAPTURED_SG;

	m_pCtfBack_TYPE->SetVisibleSingle( TRUE );
	m_pCtfBack_TYPE->START();

	m_pCtfText_TYPE[nIndex]->SetVisibleSingle ( TRUE );
    m_pCtfText_TYPE[nIndex]->START ();

	if( nIndex == 6 ){
		m_pCtfText_TYPE[4]->SetVisibleSingle ( TRUE );
		m_pCtfText_TYPE[4]->START ();
	} 
	else if( cID < CTF_ICO_CAPTURED_SG ){
		m_pCtfText_TYPE[nIndex+3]->SetVisibleSingle ( TRUE );
		m_pCtfText_TYPE[nIndex+3]->START ();
	}

	return true;
}

bool	CProgressDisplayCtf::RESET ( UIGUID cID )
{
	if ( cID < CTF_CAPTURED_SG || CTF_END < cID ) return false;

	int nIndex = cID - CTF_CAPTURED_SG;	
	m_pCtfBack_TYPE->RESET ();
	m_pCtfText_TYPE[nIndex]->RESET ();
	if( cID < CTF_ICO_CAPTURED_SG ) m_pCtfText_TYPE[nIndex+3]->RESET ();

    return true;
}

bool	CProgressDisplayCtf::STOP ()
{
	m_pCtfBack_TYPE->STOP ();
	m_pCtfBack_TYPE->SetVisibleSingle ( FALSE );

	for ( int i = 0; i < MAX_TYPE; ++i )
	{
		m_pCtfText_TYPE[i]->STOP ();
		m_pCtfText_TYPE[i]->SetVisibleSingle ( FALSE );
	}
	
	return true;
}

void CProgressDisplayCtf::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

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

	float fTime = 0.0f;

	if ( m_pCtfBack_TYPE->ISPLAYING() )
	{
		bPLAYING = true;
	}
	else
	{
		STOP ();
	}
	
	vScreenBack = vScreen;

	if ( !bPLAYING )	SetVisibleSingle( FALSE );
}