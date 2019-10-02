#include "StdAfx.h"
#include "./TargetInfoCtfDisplay.h"

#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"

#include "GLCharDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTargetInfoCtfDisplay::CTargetInfoCtfDisplay () :
	m_pFightSignSG(NULL),
	m_pFightSignMP(NULL),
	m_pFightSignPHX(NULL)
{

}

CTargetInfoCtfDisplay::~CTargetInfoCtfDisplay ()
{
}

void CTargetInfoCtfDisplay::CreateSubControl ()
{
	m_pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_SHADOW_EX_FLAG );

	CBasicProgressBar* pHPsg = new CBasicProgressBar;
	pHPsg->CreateSub ( this, "AUTHENTICATOR_CTF_DISPLAY_IMAGE_SM" );
	pHPsg->CreateOverImage ( "AUTHENTICATOR_CTF_DISPLAY_IMAGE_SM_OVER" );
	pHPsg->SetControlNameEx ( "HP 프로그래스바" );
	pHPsg->SetAlignFlag ( UI_FLAG_XSIZE );
	pHPsg->SetType(2);
	RegisterControl ( pHPsg );
	m_pHP_SG = pHPsg;

	CBasicProgressBar* pHPmp = new CBasicProgressBar;
	pHPmp->CreateSub ( this, "AUTHENTICATOR_CTF_DISPLAY_IMAGE_HA" );
	pHPmp->CreateOverImage ( "AUTHENTICATOR_CTF_DISPLAY_IMAGE_HA_OVER" );
	pHPmp->SetControlNameEx ( "HP 프로그래스바" );
	pHPmp->SetAlignFlag ( UI_FLAG_XSIZE );
	pHPmp->SetType(2);
	RegisterControl ( pHPmp );
	m_pHP_MP = pHPmp;

	CBasicProgressBar* pHPphx = new CBasicProgressBar;
	pHPphx->CreateSub ( this, "AUTHENTICATOR_CTF_DISPLAY_IMAGE_BH" );
	pHPphx->CreateOverImage ( "AUTHENTICATOR_CTF_DISPLAY_IMAGE_BH_OVER" );
	pHPphx->SetControlNameEx ( "HP 프로그래스바" );
	pHPphx->SetAlignFlag ( UI_FLAG_XSIZE );
	pHPphx->SetType(2);
	RegisterControl ( pHPphx );
	m_pHP_PHX = pHPphx;

	m_pFightSignSG = CreateControl ( "AUTHENTICATOR_CTF_DISPLAY_IMAGE_SM_FIGHTSIGN", UI_FLAG_DEFAULT );
	m_pFightSignMP = CreateControl ( "AUTHENTICATOR_CTF_DISPLAY_IMAGE_HA_FIGHTSIGN", UI_FLAG_DEFAULT );
	m_pFightSignPHX = CreateControl ( "AUTHENTICATOR_CTF_DISPLAY_IMAGE_BH_FIGHTSIGN", UI_FLAG_DEFAULT );
	m_pFightSignAuth = CreateControl ( "AUTHENTICATOR_CTF_DISPLAY_IMAGE_AUTH", UI_FLAG_DEFAULT );

}

CUIControl*	CTargetInfoCtfDisplay::CreateControl ( const char* szControl, WORD wAlignFlag )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, wAlignFlag );
	RegisterControl ( pControl );
	return pControl;
}

void CTargetInfoCtfDisplay::SetTargetInfo ( float fPercentsg, float fPercentmp, float fPercentphx,  WORD wSchool, WORD wAuthSchool ) /*, int nSchoolMark, int nPartyMark )*/
{
	m_pHP_SG->SetPercent ( fPercentsg );
	m_pHP_MP->SetPercent ( fPercentmp );
	m_pHP_PHX->SetPercent ( fPercentphx );

	m_pFightSignSG->SetVisibleSingle(FALSE);
	m_pFightSignMP->SetVisibleSingle(FALSE);
	m_pFightSignPHX->SetVisibleSingle(FALSE);
	m_pFightSignAuth->SetVisibleSingle(FALSE);


	switch( wAuthSchool )
	{
		case 0: { 
				m_pHP_SG->SetPercent ( 0.0f );
				m_pFightSignAuth->SetVisibleSingle(TRUE);	
				m_pFightSignAuth->SetLocalPos( m_pFightSignSG->GetLocalPos() );
			}
			break;
		case 1: { 
				m_pHP_MP->SetPercent ( 0.0f );
				m_pFightSignAuth->SetVisibleSingle(TRUE);	
				m_pFightSignAuth->SetLocalPos( m_pFightSignMP->GetLocalPos() );
			}
			break;
		case 2: { 
				m_pHP_PHX->SetPercent ( 0.0f );
				m_pFightSignAuth->SetVisibleSingle(TRUE);	
				m_pFightSignAuth->SetLocalPos( m_pFightSignPHX->GetLocalPos() );
			}
			break;
		case 3: m_pFightSignAuth->SetVisibleSingle(FALSE);		break;
	}

	switch( wSchool )
	{
		case 0: m_pFightSignSG->SetVisibleSingle(TRUE);		break;
		case 1: m_pFightSignMP->SetVisibleSingle(TRUE);		break;
		case 2: m_pFightSignPHX->SetVisibleSingle(TRUE);	break;
	}

	{
		SetAlignFlag ( UI_FLAG_XSIZE );


		const UIRECT& rcLocalPosOld = GetLocalPos ();
		UIRECT rcLocalPosNew = UIRECT ( rcLocalPosOld.left, rcLocalPosOld.top,
			rcLocalPosOld.sizeX, rcLocalPosOld.sizeY );

		SetLocalPos ( rcLocalPosNew );
		SetGlobalPos ( rcLocalPosNew );
	}
}