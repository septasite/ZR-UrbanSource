#include "StdAfx.h"
#include "TowerFinalDisplay.h"
#include "TowerFinalType.h"
#include "InnerInterface.h"
#include "GLGaeaClient.h"
#include "DxViewPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTowerFinalDisplay::CTowerFinalDisplay ()
{
}

CTowerFinalDisplay::~CTowerFinalDisplay ()
{
}

void CTowerFinalDisplay::CreateSubControl ()
{
	CString strKeyword[MAXTYPE] = 
	{
		"TOWER_FINAL_SG",
		"TOWER_FINAL_PHX",
		"TOWER_FINAL_MP",
		"TOWER_FINAL_TWO"
	};

	for ( int i = 0; i < MAXTYPE; ++i )
	{
		m_pQI_TYPE[i] = new CTowerFinalType;
		m_pQI_TYPE[i]->CreateSub ( this, strKeyword[i].GetString(), UI_FLAG_DEFAULT, TOWER_CAPTURED_SG + i );
		m_pQI_TYPE[i]->CreateSubControl ( strKeyword[i] );
		m_pQI_TYPE[i]->SetVisibleSingle ( FALSE );
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
	m_pPositionControl->CreateSub ( this, "TOWER_FINAL_POSITION" );
	m_pPositionControl->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pPositionControl );
}

bool	CTowerFinalDisplay::START ( UIGUID cID )
{
	if ( cID < TOWER_FINAL_SG || TOWER_FINAL_TWO < cID ) return false;
	
	int nIndex = cID - TOWER_FINAL_SG;
	m_pQI_TYPE[nIndex]->SetVisibleSingle ( TRUE );
	m_pQI_TYPE[nIndex]->START ();

	return true;
}

bool	CTowerFinalDisplay::RESET ( UIGUID cID )
{
	if ( cID < TOWER_FINAL_SG || TOWER_FINAL_TWO < cID ) return false;

	int nIndex = cID - TOWER_FINAL_SG;	
	m_pQI_TYPE[nIndex]->RESET ();

    return true;
}

bool	CTowerFinalDisplay::STOP ( UIGUID cID )
{
	if ( cID < TOWER_FINAL_SG || TOWER_FINAL_TWO < cID ) return false;

	int nIndex = cID - TOWER_FINAL_SG;	
	m_pQI_TYPE[nIndex]->STOP ();
	m_pQI_TYPE[nIndex]->SetVisibleSingle ( FALSE );

	return true;
}

void CTowerFinalDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
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
			STOP ( TOWER_FINAL_SG + i );
		}

		if ( m_QI_TYPE_KEEP[i]->IsVisible () )
		{
			m_QI_TYPE_KEEP[i]->SetGlobalPos ( vPos );

			bKEEPING = true;
		}
	}

	vScreenBack = vScreen;

	if ( !bPLAYING && !bKEEPING ) CInnerInterface::GetInstance().HideGroup ( GetWndID () );
}

void CTowerFinalDisplay::ALLSTOP ()
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

bool CTowerFinalDisplay::KEEP_START ( UIGUID cID )
{
	if ( cID < TOWER_FINAL_SG ||  TOWER_FINAL_TWO < cID ) return false;

	int nIndex = cID - TOWER_CAPTURED_SG;	

	m_QI_TYPE_KEEP[nIndex]->SetVisibleSingle ( TRUE );
	m_QI_TYPE_KEEP[nIndex]->SetDiffuseAlpha ( 50 );

	return true;
}

void CTowerFinalDisplay::KEEP_STOP ()
{
	for ( int i = 0; i < MAXTYPE; ++i )
	{
		m_QI_TYPE_KEEP[i]->SetVisibleSingle ( FALSE );
	}
}