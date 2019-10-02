#include "StdAfx.h"

#include "SkillTimeUnit.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "SkillImage.h"
#include "InnerInterface.h"
#include "UITextControl.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSkillTimeUnit::CSkillTimeUnit ()
{
}

CSkillTimeUnit::~CSkillTimeUnit ()
{
}

void CSkillTimeUnit::CreateSubControl ()
{
	CSkillImage* pSkillImage = new CSkillImage;
	pSkillImage->CreateSub ( this, "SKILLTIME_IMAGE" );	
	pSkillImage->SetUseRender ( TRUE );
	RegisterControl ( pSkillImage );
	m_pSkillImage = pSkillImage;

	CUIControl* pProgressBack = new CUIControl;
	pProgressBack->CreateSub ( this, "SKILLTIME_BACK" );
	RegisterControl ( pProgressBack );

	CBasicProgressBar* pProgressBar = new CBasicProgressBar;
	pProgressBar->CreateSub ( this, "SKILLTIME_PROGRESS" );
	pProgressBar->CreateOverImage ( "SKILLTIME_PROGRESS_OVERIMAGE" );
	pProgressBar->SetType ( CBasicProgressBar::VERTICAL );
	RegisterControl ( pProgressBar );
	m_pProgressBar = pProgressBar;
}

void CSkillTimeUnit::SetLeftTime ( const float& fLeftTime )
{
	m_fLEFT_TIME = fLeftTime;
}

void CSkillTimeUnit::SetSkill ( const DWORD& dwID, const float& fLifeTime, const CString& strSkillName, SNATIVEID sID )
{
	m_fLIFE_TIME = fLifeTime;
	m_pSkillImage->SetSkill ( dwID );
	m_pSkillImage->SetVisibleSingle ( TRUE );

	m_strSkillName = strSkillName;
	m_sSKILLID = sID;
}

void CSkillTimeUnit::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	if ( m_pProgressBar )
	{
		const float fPercent = m_fLEFT_TIME/m_fLIFE_TIME;
		m_pProgressBar->SetPercent ( fPercent );
	}

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( CHECK_MOUSE_IN ( GetMessageEx () ) )
	{
		CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( m_strSkillName, NS_UITEXTCOLOR::GREENYELLOW );
		if ( GetMessageEx () & UIMSG_LB_DOWN )
		{
			CString strCombine;
			CInnerInterface::GetInstance().SetSKEFFID( m_sSKILLID );
			strCombine.Format ( "Removing '%s' will make the effect deactivated. Will you continue to remove it?", m_strSkillName );
			DoModal ( strCombine, MODAL_QUESTION, YESNO, MODAL_SKILLFACT_ASK_RESET );
		}
	}
}