#include "StdAfx.h"
#include "VehicleDisplay.h"
#include "ItemImage.h"
#include "InnerInterface.h"
#include "GLItemMan.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"
#include "InventoryWindow.h"
#include "CharacterWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVehicleDisplay::CVehicleDisplay () 
: m_pVehicleImage ( NULL )
{
}

CVehicleDisplay::~CVehicleDisplay ()
{
}

void  CVehicleDisplay::CreateSubControl ()
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, "VEHICLE_POWER_ICON_BOX_BOX" );
	pItemImage->CreateSubControl ();
	pItemImage->SetUseRender ( TRUE );
	pItemImage->SetVisibleSingle ( FALSE );
	RegisterControl ( pItemImage );
    m_pVehicleImage = pItemImage;

	CUIControl* pDummyControl = new CUIControl;
	pDummyControl->CreateSub ( this, "VEHICLE_POWER_ICON");
	RegisterControl ( pDummyControl );
	m_pDummyControl = pDummyControl;
}

void CVehicleDisplay::SetItem ( SNATIVEID sICONINDEX, const char* szTexture)
{
	if ( m_pVehicleImage )
	{
		m_pVehicleImage->SetItem ( sICONINDEX, szTexture );
		m_pVehicleImage->SetVisibleSingle ( TRUE );
	}
}

void CVehicleDisplay::ResetItem ()
{
	if ( m_pVehicleImage )
	{
		m_pVehicleImage->SetVisibleSingle ( FALSE );
		m_pVehicleImage->ResetItem ();
	}
}

void CVehicleDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	
	SITEMCUSTOM sItem =  GLGaeaClient::GetInstance().GetCharacter()->m_sVehicleNativeID;

	if ( m_sNativeID != sItem.sNativeID ) 
	{
		m_sNativeID = sItem.sNativeID;
		
		if ( m_sNativeID.IsValidNativeID() )
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( m_sNativeID );
			m_sVehicleStr = pItem->GetName();
			if ( !pItem )
			{
				GASSERT ( 0 && "등록되지 않은 ID입니다." );
				return ;
			}

			ResetItem ();	
			SetItem ( pItem->sBasicOp.sICONID, pItem->GetInventoryFile() );	
		}
		else
		{
			m_sVehicleStr = "";
			ResetItem ();
		}
	}

	int nTime = GLGaeaClient::GetInstance().GetCharacter()->m_sVehicle.m_nFull;

	if ( nTime <= 2 ) m_pDummyControl->SetVisibleSingle( true );
	else  m_pDummyControl->SetVisibleSingle( false );

	if ( CHECK_MOUSE_IN ( GetMessageEx () ) )
	{
		CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( m_sVehicleStr, NS_UITEXTCOLOR::WHITE );
	}
	if ( CHECK_MOUSEIN_LBUPLIKE ( GetMessageEx () ) )
	{
		if( GLGaeaClient::GetInstance().GetCharacter()->m_sVehicle.IsActiveValue() )
		{
			if ( GLTradeClient::GetInstance().Valid() ) return;
			
			if ( CInnerInterface::GetInstance().IsVisibleGroup( INVENTORY_WINDOW ) )	CInnerInterface::GetInstance().HideGroup ( INVENTORY_WINDOW );
			else	CInnerInterface::GetInstance().ShowGroupFocus( INVENTORY_WINDOW );
//			CInnerInterface::GetInstance().GetInventoryWindow()->SetVisiblePage (1)	;		
		}
	}
}