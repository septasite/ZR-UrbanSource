#include "StdAfx.h"
#include "CharacterWindowCharStatMark.h"
#include "../InnerInterface.h"
#include "../UITextControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterWindowCharStatMark::CCharacterWindowCharStatMark ()
	: m_pUpImage(NULL)
	, m_pDownImage(NULL)
{
}

CCharacterWindowCharStatMark::~CCharacterWindowCharStatMark ()
{
}

void CCharacterWindowCharStatMark::CreateSubControl ()
{
	m_pUpImage = new CUIControl;
	m_pUpImage->CreateSub ( this, "UPPER_ARROW", UI_FLAG_DEFAULT, MARK_IMAGE_UP );
	m_pUpImage->SetVisibleSingle( FALSE );
	RegisterControl ( m_pUpImage );

	m_pDownImage = new CUIControl;
	m_pDownImage->CreateSub ( this, "LOWER_ARROW", UI_FLAG_DEFAULT, MARK_IMAGE_DOWN );
	m_pDownImage->SetVisibleSingle( FALSE );
	RegisterControl ( m_pDownImage );
}

void CCharacterWindowCharStatMark::Update ( int x ,int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCharacterWindowCharStatMark::TranslateUIMessage ( UIGUID cID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( cID, dwMsg );
}

void CCharacterWindowCharStatMark::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle ( bVisible );
	if ( bVisible )
	{
		Reset();
	}
}

void CCharacterWindowCharStatMark::Reset()
{
	if ( !m_pUpImage || !m_pDownImage )	return;

	m_pUpImage->SetVisibleSingle( FALSE );
	m_pDownImage->SetVisibleSingle( FALSE );
}

void CCharacterWindowCharStatMark::ShowImage( bool bUp )
{
	if ( !m_pUpImage || !m_pDownImage )	return;
	Reset();

	m_pUpImage->SetVisibleSingle( bUp );
	m_pDownImage->SetVisibleSingle( !bUp );
}

bool CCharacterWindowCharStatMark::CheckValue( int nOrig, int nToCheck )
{
	if ( nToCheck == nOrig )
	{
		Reset();
		return false;
	}else{
		ShowImage( nToCheck > nOrig );
		return true;
	}

	return false;
}

bool CCharacterWindowCharStatMark::CheckValue( int nCheck )
{
	ShowImage( nCheck > 0 );
	return true;
}
bool CCharacterWindowCharStatMark::CheckValueFloat( float nOrig, float nToCheck )
{
	if ( nToCheck == nOrig )
	{
		Reset();
		return false;
	}else{
		ShowImage( nToCheck > nOrig );
		return true;
	}

	return false;
}

bool CCharacterWindowCharStatMark::CheckValueFloat( float nCheck )
{
	ShowImage( nCheck > 0 );
	return true;
}