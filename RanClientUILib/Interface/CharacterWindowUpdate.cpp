#include "StdAfx.h"
#include "CharacterWindow.h"
#include "GLGaeaClient.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxViewPort.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "InventoryPageWear.h"
#include "InventoryPageWearEx.h"
#include "InnerInterface.h"
#include "../Interface/UITextControl.h"
#include "../RanClientLib/G-Logic/GLGaeaClient.h"
#include "GLogicData.h"
#include "GLCharData.h"
#include "./GLogicEx.h"
#include "./GLChar.h"
#include "DxGlobalStage.h"
#include "CharacterWindowCharRender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CCharacterWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();	
	BOOL bPointUsable = (sCharData.m_wStatsPoint)?TRUE:FALSE;

//	스탯 컨트롤

	SetPointControl ( bPointUsable );

	LoadComboData();

	m_pDamageMinText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pDamageMaxText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pDefenseText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pReqPaText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pReqSaText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pReqMaText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pHPText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pMPText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pSPText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pCPText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pHitRateText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );
	m_pAvoidRateText2->SetOneLineText ( "-", NS_UITEXTCOLOR::WHITE );

	m_pDamageMinText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pDamageMaxText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pDefenseText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pReqPaText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pReqSaText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pReqMaText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pHPText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pMPText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pSPText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pCPText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pHitRateText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );
	m_pAvoidRateText3->SetOneLineText ( "0", NS_UITEXTCOLOR::WHITE );

//	이름,클래스	
	SetName ( sCharData );

//	경험치
	SetEXP ( sCharData );

//	Stat	
	SetPow ( sCharData );
	SetDex ( sCharData );
	SetSpi ( sCharData );
	//SetInt ( sCharData );
	SetStr ( sCharData );
	SetSta ( sCharData );
	SetPoint ( sCharData );

	SetPow2 ( m_pNewPow,sCharData );
	SetDex2 ( m_pNewDex,sCharData );
	SetSpi2 ( m_pNewSpi,sCharData );
	SetStr2 ( m_pNewStr,sCharData );
	SetSta2 ( m_pNewSta,sCharData );
	//SetPoint2 ( m_pNewPoint );

//	Status
	SetLevel ( sCharData );
	SetDamage ( sCharData );
	SetDefense ( sCharData );
	SetReqPa ( sCharData );
	SetReqSa ( sCharData );	
	SetReqMa ( sCharData );	
	SetHP ( sCharData );
	SetMP ( sCharData );
	SetSP ( sCharData );
	SetCP ( sCharData );
	SetHitRate ( sCharData );
	SetAvoidRate ( sCharData );
	SetPremium ();
	SetRB ( sCharData );

//	저항력
	SetFireResi ( sCharData );
	SetColdResi ( sCharData );
	SetElectricResi ( sCharData );
	SetPoisonResi ( sCharData );
	SetSpiritResi ( sCharData );

	SetAcademy_Department ( sCharData );
	SetActivityPoint ( sCharData );
	SetPKState ( sCharData );
	//SetDepartment ( sCharData );
	SetBright ( sCharData );
	SetGrade ( sCharData );

	CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );


	{	//	제 자리 찾아가기
		//const UIRECT& rcPowPos = m_pPowDiaableButton->GetGlobalPos ();
		//m_pPowButton->SetGlobalPos ( D3DXVECTOR2 ( rcPowPos.left, rcPowPos.top ) );

		//const UIRECT& rcDexPos = m_pDexDiaableButton->GetGlobalPos ();
		//m_pDexButton->SetGlobalPos ( D3DXVECTOR2 ( rcDexPos.left, rcDexPos.top ) );

		//const UIRECT& rcSpiPos = m_pSpiDiaableButton->GetGlobalPos ();
		//m_pSpiButton->SetGlobalPos ( D3DXVECTOR2 ( rcSpiPos.left, rcSpiPos.top ) );

		//const UIRECT& rcIntPos = m_pIntDiaableButton->GetGlobalPos ();
		//m_pIntButton->SetGlobalPos ( D3DXVECTOR2 ( rcIntPos.left, rcIntPos.top ) );

		//const UIRECT& rcStaPos = m_pStaDiaableButton->GetGlobalPos ();
		//m_pStaButton->SetGlobalPos ( D3DXVECTOR2 ( rcStaPos.left, rcStaPos.top ) );

		//const UIRECT& rcStrPos = m_pStrDiaableButton->GetGlobalPos ();
		//m_pStrButton->SetGlobalPos ( D3DXVECTOR2 ( rcStrPos.left, rcStrPos.top ) );
	}

	{
		m_pPowText->SetUseTextColor ( 0, FALSE );
		m_pPowTextStatic->SetUseTextColor ( 0, FALSE );

		m_pDexText->SetUseTextColor ( 0, FALSE );
		m_pDexTextStatic->SetUseTextColor ( 0, FALSE );

		m_pSpiText->SetUseTextColor ( 0, FALSE );
		m_pSpiTextStatic->SetUseTextColor ( 0, FALSE );

		//m_pIntText->SetUseTextColor ( 0, FALSE );
		//m_pIntTextStatic->SetUseTextColor ( 0, FALSE );

		m_pStrText->SetUseTextColor ( 0, FALSE );
		m_pStrTextStatic->SetUseTextColor ( 0, FALSE );

		m_pStaText->SetUseTextColor ( 0, FALSE );
		m_pStaTextStatic->SetUseTextColor ( 0, FALSE );
	}
}

void CCharacterWindow::ClearRender()
{
	if( m_pRender )
	{
		m_pRender->ClearRender();
	}
}