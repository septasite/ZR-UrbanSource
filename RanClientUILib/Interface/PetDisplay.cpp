#include "StdAfx.h"
#include "PetDisplay.h"
#include "ItemImage.h"
#include "InnerInterface.h"
#include "GLItemMan.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"
#include "InventoryWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPetDisplay::CPetDisplay () 
: m_pPetImage ( NULL )
{
}

CPetDisplay::~CPetDisplay ()
{
}

void  CPetDisplay::CreateSubControl ()
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, "PET_HUNGRY_ICON_BOX_BOX" );
	pItemImage->CreateSubControl ();
	pItemImage->SetUseRender ( TRUE );
	pItemImage->SetVisibleSingle ( FALSE );
	RegisterControl ( pItemImage );
    m_pPetImage = pItemImage;

	CUIControl* pDummyControl = new CUIControl;
	pDummyControl->CreateSub ( this, "PET_HUNGRY_ICON");
	RegisterControl ( pDummyControl );
	m_pDummyControl = pDummyControl;
}

void CPetDisplay::SetItem ( SNATIVEID sICONINDEX, const char* szTexture)
{
	if ( m_pPetImage )
	{
		m_pPetImage->SetItem ( sICONINDEX, szTexture );
		m_pPetImage->SetVisibleSingle ( TRUE );
	}
}

void CPetDisplay::ResetItem ()
{
	if ( m_pPetImage )
	{
		m_pPetImage->SetVisibleSingle ( FALSE );
		m_pPetImage->ResetItem ();
	}
}

void CPetDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	
	SITEMCUSTOM sItem =  GLGaeaClient::GetInstance().GetCharacter()->m_sPetCardNativeID;

	if ( m_sNativeID != sItem.sNativeID ) 
	{
		m_sNativeID = sItem.sNativeID;
		
		if ( m_sNativeID.IsValidNativeID() )
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( m_sNativeID );
			m_sPetStr = pItem->GetName();
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
			m_sPetStr = "";
			ResetItem ();
		}
	}

	int nTime = GLGaeaClient::GetInstance().GetPetClient()->m_nFull;

	if ( nTime <= 2 ) m_pDummyControl->SetVisibleSingle( true );
	else  m_pDummyControl->SetVisibleSingle( false );

	if ( CHECK_MOUSE_IN ( GetMessageEx () ) )
	{
		CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( m_sPetStr, NS_UITEXTCOLOR::WHITE );
	}
	if ( CHECK_MOUSEIN_LBUPLIKE ( GetMessageEx () ) )
	{
		if( GLGaeaClient::GetInstance().GetPetClient()->IsVALID() )
		{
			if ( GLTradeClient::GetInstance().Valid() ) return;
			
			if ( CInnerInterface::GetInstance().IsVisibleGroup( PET_WINDOW ) )		CInnerInterface::GetInstance().HideGroup ( PET_WINDOW );
			else	CInnerInterface::GetInstance().ShowGroupFocus( PET_WINDOW );		
		}
	}
}