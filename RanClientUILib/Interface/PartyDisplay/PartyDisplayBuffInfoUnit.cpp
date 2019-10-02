#include "StdAfx.h"

#include "PartyDisplayBuffInfoUnit.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "../RanClientUILib/Interface/SkillImage33.h"
#include "../RanClientUILib/Interface/InnerInterface.h"
#include "../RanClientUILib/Interface/UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartyDisplayBuffInfoUnit::CPartyDisplayBuffInfoUnit ()
{
}

CPartyDisplayBuffInfoUnit::~CPartyDisplayBuffInfoUnit ()
{
}

void CPartyDisplayBuffInfoUnit::CreateSubControl ()
{
	CSkillImage33* pSkillImage = new CSkillImage33;
	pSkillImage->CreateSub ( this, "PARTYDISPLAYBUFF_IMAGE" );	
	pSkillImage->SetUseRender ( TRUE );
	RegisterControl ( pSkillImage );
	m_pSkillImage = pSkillImage;
}

void CPartyDisplayBuffInfoUnit::SetLeftTime ( const float& fLeftTime )
{
	m_fLEFT_TIME = fLeftTime;
}

void CPartyDisplayBuffInfoUnit::SetSkill ( const DWORD& dwID, const float& fLifeTime, const CString& strSkillName )
{
	m_fLIFE_TIME = fLifeTime;
	m_pSkillImage->SetSkill ( dwID );
	m_pSkillImage->SetVisibleSingle ( TRUE );

	m_strSkillName = strSkillName;
}

void CPartyDisplayBuffInfoUnit::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

}