#include "StdAfx.h"
#include "TowerDownType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTowerDownType::CTowerDownType () :
    m_bPLAY ( false )
{
}

CTowerDownType::~CTowerDownType ()
{
}

void CTowerDownType::CreateSubControl ( CString strKeyword )
{
	float fBEGIN_TIME = 0.0f;
	float fEND_TIME = 2.2f;
	
		m_pXControl= new CUIControl;
		m_pXControl->CreateSub ( this, strKeyword.GetString(),  UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pXControl->SetVisibleSingle ( FALSE );
		m_pXControl->SetTransparentOption ( TRUE );
		RegisterControl ( m_pXControl );

		m_fBEGIN_TIME = fBEGIN_TIME;
		m_fEND_TIME = fEND_TIME;
}

void	CTowerDownType::START()
{
	RESET ();
	m_bPLAY = true;
}

void	CTowerDownType::RESET()
{
	m_bPLAY = false;
	m_fPlayedTime = 0.0f;
	m_pXControl->SetVisibleSingle ( FALSE );
	
}

void CTowerDownType::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( ISPLAYING() )
	{
		m_fPlayedTime += fElapsedTime;

		bool bIsVISIBLE = false;

			if ( m_fBEGIN_TIME <= m_fPlayedTime && m_fPlayedTime <= m_fEND_TIME )
			{
				if ( !m_pXControl->IsVisible() ) 
				m_pXControl->SetFadeTime( 0.1f );
				m_pXControl->SetFadeIn ();
			}
			else if ( m_fEND_TIME < m_fPlayedTime )
			{				
				m_pXControl->SetFadeTime( 2.2f );
				m_pXControl->SetFadeOut ();
			}
			if ( m_pXControl->IsVisible () ) bIsVISIBLE = true;
			if ( m_fPlayedTime < m_fBEGIN_TIME ) bIsVISIBLE = true;	//	아직 시작도 되지 않은 것이면...

		if ( !bIsVISIBLE )
		{
			STOP ();
		}
	}
}
