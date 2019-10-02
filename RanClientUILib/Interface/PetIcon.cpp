#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\PetIcon.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "BasicLineBoxEx.h"

#include "ItemImage.h"
#include "ItemMove.h"
#include "PetQuickSkillSlot.h"
#include "GLItemMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPetIcon::CPetIcon(void) :
	m_pPetIcon(NULL)
{
}

CPetIcon::~CPetIcon(void)
{

}
void CPetIcon::CreateSubControl ()
{
	m_pPetIcon = new CBasicButton;
	m_pPetIcon->CreateSub ( this, "PET_HUNGRY_TYPE_SIBERIAN", UI_FLAG_DEFAULT, PetIconOnMouse );
	m_pPetIcon->SetUseGlobalAction ( TRUE );
	RegisterControl ( m_pPetIcon );



	CString strPetType[PetType] =
	{
		"PET_HUNGRY_TYPE_SIBERIAN",
		"PET_HUNGRY_TYPE_TURTLE",
		"PET_HUNGRY_TYPE_TIGER",
		"PET_HUNGRY_TYPE_BEAR",
		"PET_HUNGRY_TYPE_OWL",
		"PET_HUNGRY_TYPE_BIRD",
		"PET_HUNGRY_TYPE_CRAZYMONKEY",
		"PET_HUNGRY_TYPE_SKELETON",
		"PET_HUNGRY_TYPE_MONKEY",
		"PET_HUNGRY_TYPE_FAIRY",
		"PET_HUNGRY_TYPE_FOX",
		"PET_HUNGRY_TYPE_LEOPARD",
		"PET_HUNGRY_TYPE_DINOSAUR",

	};
		
		for ( int i = 0; i < PetType; ++i )
		{
		m_pPetType[i] = new CUIControl;
		m_pPetType[i]->CreateSub ( this, strPetType[i].GetString() );
		m_pPetType[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pPetType[i] );
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

void CPetIcon::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	
	int nType = GLGaeaClient::GetInstance().GetPetClient()->m_emTYPE;
	m_pPetType[nType]->SetVisibleSingle ( TRUE );

	int nFull = GLGaeaClient::GetInstance().GetPetClient()->m_nFull;
	SetSatiety( nFull );
}

void CPetIcon::SetSatiety( int nNOW )
{
		m_BoxGauge->SetPercent( nNOW/1000.0f );
}

void CPetIcon::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
switch ( ControlID )
	{
	case PetIconOnMouse:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				int nFull = GLGaeaClient::GetInstance().GetPetClient()->m_nFull;
				CString strTemp;
				strTemp.Format( "Life : %.2f%%", nFull/10.0f );
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( strTemp, NS_UITEXTCOLOR::WHITE  );				
			

				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( PET_WINDOW ) )
					{
						CInnerInterface::GetInstance().ShowGroupFocus ( PET_WINDOW );
					}
					else
					{
						CInnerInterface::GetInstance().HideGroup ( PET_WINDOW );
					}
				}
			}
		}
		break;
	}
}