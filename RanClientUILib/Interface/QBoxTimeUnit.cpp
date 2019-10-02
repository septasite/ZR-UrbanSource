#include "StdAfx.h"

#include "QBoxTimeUnit.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "InnerInterface.h"
#include "UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CQBoxTimeUnit::CQBoxTimeUnit ():
	m_fLEFT_TIME(0)
	,m_fLIFE_TIME(0)
{
}

CQBoxTimeUnit::~CQBoxTimeUnit ()
{
}

void CQBoxTimeUnit::CreateSubControl ()
{
	CBasicProgressBar* pProgressBar = new CBasicProgressBar;
	pProgressBar->CreateSub ( this, "MINIBAR_GAUGE_BACK" );
	pProgressBar->CreateOverImage ( "MINIBAR_GAUGE_RED" );
	pProgressBar->SetType ( CBasicProgressBar::VERTICAL );
	RegisterControl ( pProgressBar );
	m_pProgressBar = pProgressBar;
}

void CQBoxTimeUnit::SetLeftTime ( const float& fLeftTime )
{
	m_fLEFT_TIME = fLeftTime;
}

void CQBoxTimeUnit::SetTime ( const float& fTime )
{
	m_fLIFE_TIME = fTime;
}

void CQBoxTimeUnit::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	const float fPercent = 0;

	if ( m_pProgressBar )
	{
		const float fPercent = m_fLEFT_TIME/m_fLIFE_TIME;
		m_pProgressBar->SetPercent ( fPercent );
	}

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( CHECK_MOUSE_IN ( GetMessageEx () ) )
	{
		CString strTemp;
		float fTime = ( m_fLEFT_TIME/m_fLIFE_TIME ) * 100 ;
		strTemp.Format( "%.2f%%", fTime);

		CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strTemp, NS_UITEXTCOLOR::WHITE );
	}
}