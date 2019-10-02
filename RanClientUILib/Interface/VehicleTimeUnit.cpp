#include "StdAfx.h"

#include "VehicleTimeUnit.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "InnerInterface.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVehicleTimeUnit::CVehicleTimeUnit ():
	m_fLEFT_TIME(0)
	,m_fLIFE_TIME(0)
{
}

CVehicleTimeUnit::~CVehicleTimeUnit ()
{
}

void CVehicleTimeUnit::CreateSubControl ()
{
	CBasicProgressBar* pProgressBar = new CBasicProgressBar;
	pProgressBar->CreateSub ( this, "MINIBAR_GAUGE_BACK" );
	pProgressBar->CreateOverImage ( "MINIBAR_GAUGE_GREEN" );
	pProgressBar->SetType ( CBasicProgressBar::VERTICAL );
	RegisterControl ( pProgressBar );
	m_pProgressBar = pProgressBar;
}

void CVehicleTimeUnit::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	m_fLIFE_TIME = 1000;
	m_fLEFT_TIME = float (GLGaeaClient::GetInstance().GetCharacter()->m_sVehicle.m_nFull);
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

		CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strTemp, NS_UITEXTCOLOR::WHITE);
	}
}