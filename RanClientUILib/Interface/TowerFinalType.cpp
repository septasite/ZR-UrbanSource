#include "StdAfx.h"
#include "TowerFinalType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTowerFinalType::CTowerFinalType () :
    m_bPLAY ( false )
	,m_fPlayedTime ( 0.0f)
{
}

CTowerFinalType::~CTowerFinalType ()
{
	m_fPlayedTime = 0.0f;
}

void CTowerFinalType::CreateSubControl ( CString strKeyword )
{

		m_pXControl= new CUIControl;
		m_pXControl->CreateSub ( this, strKeyword.GetString(),  UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pXControl->SetVisibleSingle ( FALSE );
		m_pXControl->SetTransparentOption ( TRUE );
		RegisterControl ( m_pXControl );

}

void	CTowerFinalType::START()
{
	m_fPlayedTime = 0.0f;
	m_fPlayedTime2 = 0.0f;
	m_bPLAY = true;
}

void	CTowerFinalType::RESET()
{
	m_bPLAY = false;
	m_fPlayedTime = 0.0f;
	m_pXControl->SetVisibleSingle ( FALSE );
	
}

void CTowerFinalType::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( ISPLAYING() )
	{
		m_fPlayedTime += fElapsedTime;
		m_fPlayedTime2 += fElapsedTime;

		if( m_pXControl->IsVisible() )
		{
			if (  m_fPlayedTime > 1.5f )
			{
				m_pXControl->SetVisibleSingle ( FALSE );
				m_fPlayedTime = 0.0f;
			}
			
			if( m_fPlayedTime2 > 5.0f )
			{
				RESET();
				m_fPlayedTime2 = 0.0f;
			}
		}
		else
		{
			 if ( m_fPlayedTime >= 0.5f )
			{				
				m_pXControl->SetVisibleSingle ( TRUE );
				m_fPlayedTime = 0.0f;
			}
		}
	}
}
