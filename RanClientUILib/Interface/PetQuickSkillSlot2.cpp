#include "StdAfx.h"
#include "PetQuickSkillSlot2.h"

#include "GLGaeaClient.h"
#include "PetSkillImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPetQuickSkillSlot2::CPetQuickSkillSlot2 ()
	: m_pSkillImage ( NULL )
	, m_pSkillMouseOver ( NULL )
	, m_pd3dDevice ( NULL )
{
}

CPetQuickSkillSlot2::~CPetQuickSkillSlot2 ()
{
}

void  CPetQuickSkillSlot2::CreateSubControl ()
{
	CreateSkillImage ();
	CreateMouseOver ();
}

void CPetQuickSkillSlot2::CreateSkillImage ()
{
	CPetSkillImage* pSkillImage = new CPetSkillImage;
	pSkillImage->CreateSub ( this, "PET_SKILL_IMAGE_B" );
	pSkillImage->CreateSubControl ();
	pSkillImage->SetUseRender ( TRUE );
	pSkillImage->SetVisibleSingle ( FALSE );
    RegisterControl ( pSkillImage );
	m_pSkillImage = pSkillImage;
}

void CPetQuickSkillSlot2::CreateMouseOver ()
{
	CUIControl* pSkillMouseOver = new CUIControl;
	pSkillMouseOver->CreateSub ( this, "PET_SKILL_MOUSE_OVER_B", UI_FLAG_DEFAULT, QUICK_SKILL_MOUSE_OVER );
	pSkillMouseOver->SetVisibleSingle ( TRUE );
	RegisterControl ( pSkillMouseOver );
	m_pSkillMouseOver = pSkillMouseOver;
}

void CPetQuickSkillSlot2::UpdateSlot( SNATIVEID sNativeID )
{	
	if ( !m_pSkillImage )
	{
		GASSERT ( 0 && "스킬 이미지가 만들어지지 않았습니다."  );
		return ;
	}

	if ( sNativeID != NATIVEID_NULL() )
	{
		m_pSkillImage->SetSkill ( sNativeID );
		m_pSkillImage->SetVisibleSingle ( TRUE );
		m_pSkillImage->SetSkillProcess ( sNativeID );
	}
	else
	{
		m_pSkillImage->SetVisibleSingle ( FALSE );
		m_pSkillImage->ResetSkill ();
	}	
}

void CPetQuickSkillSlot2::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	SNATIVEID sNativeID = GLGaeaClient::GetInstance().GetPetClient()->m_sActiveSkillID;
	UpdateSlot( sNativeID );
}

UIRECT CPetQuickSkillSlot2::GetAbsPosSkillImage ()
{	
	if ( !m_pSkillImage )
	{
		GASSERT ( 0 && "m_pSkillImage가 NULL입니다." );
		return UIRECT ();
	}
	
	return m_pSkillImage->GetGlobalPos();	
}