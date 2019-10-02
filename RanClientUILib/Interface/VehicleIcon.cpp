#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\VehicleIcon.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "BasicLineBoxEx.h"

#include "ItemImage.h"
#include "ItemMove.h"
#include "GLItemMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVehicleIcon::CVehicleIcon(void) :
	m_pVehicleIcon(NULL)
{
}

CVehicleIcon::~CVehicleIcon(void)
{

}
void CVehicleIcon::CreateSubControl ()
{
	m_pVehicleIcon = new CBasicButton;
	m_pVehicleIcon->CreateSub ( this, "VEHICLE_HUNGRY_TYPE_HOVER", UI_FLAG_DEFAULT, VehicleIconOnMouse );
	m_pVehicleIcon->SetUseGlobalAction ( TRUE );
	RegisterControl ( m_pVehicleIcon );



	CString strVehicleType[VehicleType] =
	{
		"VEHICLE_HUNGRY_TYPE_HOVER",
		"VEHICLE_HUNGRY_TYPE_SCUTER",
		"VEHICLE_HUNGRY_TYPE_BT5",
		"VEHICLE_HUNGRY_TYPE_BT7",
		"VEHICLE_HUNGRY_TYPE_BT9",
		"VEHICLE_HUNGRY_TYPE_RARE",
	};
		
		for ( int i = 0; i < VehicleType; ++i )
		{
		m_pVehicleType[i] = new CUIControl;
		m_pVehicleType[i]->CreateSub ( this, strVehicleType[i].GetString() );
		m_pVehicleType[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pVehicleType[i] );
		}

		{
		CBasicProgressBar* pBoxGauge = new CBasicProgressBar;
		pBoxGauge->CreateSub ( this, "MINIBAR_GAUGE_BACK" );
		pBoxGauge->CreateOverImage ( "MINIBAR_GAUGE_RED"  );	
		pBoxGauge->SetType ( 1 );
		pBoxGauge->SetVisibleSingle ( TRUE );
		RegisterControl ( pBoxGauge );
		m_BoxGauge = pBoxGauge;	
		}
}

void CVehicleIcon::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	
	int nType = GLGaeaClient::GetInstance().GetCharacter()->m_sVehicle.m_emTYPE;
	m_pVehicleType[nType]->SetVisibleSingle ( TRUE );

	int nFull = GLGaeaClient::GetInstance().GetCharacter()->m_sVehicle.m_nFull;
	SetBattery( nFull );
}

void CVehicleIcon::SetBattery( int nNOW )
{
		m_BoxGauge->SetPercent( nNOW/1000.0f );
}

void CVehicleIcon::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
switch ( ControlID )
	{
	case VehicleIconOnMouse:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				int nFull = GLGaeaClient::GetInstance().GetCharacter()->m_sVehicle.m_nFull;
				CString strTemp;
				strTemp.Format( "Life : %.2f%%", nFull/10.0f );
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( strTemp, NS_UITEXTCOLOR::WHITE  );				
			

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( VEHICLE_WINDOW ) )
					{
						CInnerInterface::GetInstance().ShowGroupFocus ( VEHICLE_WINDOW );
					}
					else
					{
						CInnerInterface::GetInstance().HideGroup ( VEHICLE_WINDOW );
					}
				}
			}
		}
		break;
	}
}