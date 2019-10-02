#include "StdAfx.h"
#include "./TowerHPDisplay.h"
#include "UITextControl.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineLib/DxCommon/d3dfontx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTowerHPDisplay::CTowerHPDisplay () :
m_pNameBoxDummy ( NULL )
{

}

CTowerHPDisplay::~CTowerHPDisplay ()
{
}

void CTowerHPDisplay::CreateSubControl ()
{
	m_pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_FLAG );

	CBasicProgressBar* pHP = new CBasicProgressBar;
	pHP->CreateSub ( this, "TOWERDISPLAY_HP_SG" );
	pHP->CreateOverImage2 ( "TOWERDISPLAY_HP_SG_OVERIMAGE" , CBasicProgressBar::VERTICAL2 );
	pHP->SetControlNameEx ( "HP ??????" );
	pHP->SetAlignFlag ( UI_FLAG_XSIZE );
	RegisterControl ( pHP );
	m_pHP = pHP;

	CBasicProgressBar* pHP2 = new CBasicProgressBar;
	pHP2->CreateSub ( this, "TOWERDISPLAY_HP_MP" );
	pHP2->CreateOverImage2 ( "TOWERDISPLAY_HP_MP_OVERIMAGE" , CBasicProgressBar::VERTICAL2 );
	pHP2->SetControlNameEx ( "HP ??????" );
	pHP2->SetAlignFlag ( UI_FLAG_XSIZE );
	RegisterControl ( pHP2 );
	m_pHP2 = pHP2;

	CBasicProgressBar* pHP3 = new CBasicProgressBar;
	pHP3->CreateSub ( this, "TOWERDISPLAY_HP_PHX" );
	pHP3->CreateOverImage2 ( "TOWERDISPLAY_HP_PHX_OVERIMAGE" , CBasicProgressBar::VERTICAL2 );
	pHP3->SetControlNameEx ( "HP ??????" );
	pHP3->SetAlignFlag ( UI_FLAG_XSIZE );
	RegisterControl ( pHP3 );
	m_pHP3 = pHP3;
	
	
	CBasicTextBox* pNameBox = new CBasicTextBox;
	pNameBox->CreateSub ( this, "TARGETINFO_NAMEBOX" );
    pNameBox->SetFont ( m_pFont8 );
	pNameBox->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	pNameBox->SetControlNameEx ( "HP ?????" );	
	pNameBox->SetAlignFlag ( UI_FLAG_XSIZE );
	RegisterControl ( pNameBox );
	m_pNameBox = pNameBox;

	m_pNameBoxDummy = CreateControl ( "TARGETINFO_NAMEBOX", UI_FLAG_DEFAULT );

}

CUIControl*	CTowerHPDisplay::CreateControl ( const char* szControl, WORD wAlignFlag )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, wAlignFlag );
	RegisterControl ( pControl );
	return pControl;
}

void CTowerHPDisplay::SetTowerHPSG ( float fPercent )
{
	m_pHP->SetPercent ( fPercent );
	SIZE Size;
	CString strName;
	m_pFont8->GetTextExtent ( strName.GetString (), Size );
	const UIRECT& rcNameBoxDummy = m_pNameBoxDummy->GetLocalPos();
	float fNameWidth = 0;
	fNameWidth = 0;
	{
		SetAlignFlag ( UI_FLAG_XSIZE );

		if ( fNameWidth < rcNameBoxDummy.sizeX )
		{
			fNameWidth = rcNameBoxDummy.sizeX;
		}

		//	텍스트 박스 크게 리사이징
		const UIRECT& rcNameLocalPos = m_pNameBox->GetLocalPos ();
		const UIRECT& rcNameBoxNew = UIRECT ( rcNameLocalPos.left, rcNameLocalPos.top,
			fNameWidth, rcNameLocalPos.sizeY );
		AlignSubControl ( rcNameLocalPos, rcNameBoxNew );

		const UIRECT& rcLocalPosOld = GetLocalPos ();
		UIRECT rcLocalPosNew = UIRECT ( rcLocalPosOld.left, rcLocalPosOld.top,
			rcLocalPosOld.sizeX + (fNameWidth - rcNameLocalPos.sizeX), rcLocalPosOld.sizeY );

		SetLocalPos ( rcLocalPosNew );
		SetGlobalPos ( rcLocalPosNew );
		
		m_pNameBox->AddTextNoSplit ( strName, NS_UITEXTCOLOR::WHITE );	
		m_strName = strName;
	}
}

void CTowerHPDisplay::SetTowerHPMP ( float fPercent )
{
	m_pHP2->SetPercent ( fPercent );
	SIZE Size;
	CString strName;
	m_pFont8->GetTextExtent ( strName.GetString (), Size );
	const UIRECT& rcNameBoxDummy = m_pNameBoxDummy->GetLocalPos();
	float fNameWidth = 0;
	fNameWidth = 0;

{
		SetAlignFlag ( UI_FLAG_XSIZE );

		if ( fNameWidth < rcNameBoxDummy.sizeX )
		{
			fNameWidth = rcNameBoxDummy.sizeX;
		}

		//	텍스트 박스 크게 리사이징
		const UIRECT& rcNameLocalPos = m_pNameBox->GetLocalPos ();
		const UIRECT& rcNameBoxNew = UIRECT ( rcNameLocalPos.left, rcNameLocalPos.top,
			fNameWidth, rcNameLocalPos.sizeY );
		AlignSubControl ( rcNameLocalPos, rcNameBoxNew );

		const UIRECT& rcLocalPosOld = GetLocalPos ();
		UIRECT rcLocalPosNew = UIRECT ( rcLocalPosOld.left, rcLocalPosOld.top,
			rcLocalPosOld.sizeX + (fNameWidth - rcNameLocalPos.sizeX), rcLocalPosOld.sizeY );

		SetLocalPos ( rcLocalPosNew );
		SetGlobalPos ( rcLocalPosNew );
		
		m_pNameBox->AddTextNoSplit ( strName, NS_UITEXTCOLOR::WHITE );	
		m_strName = strName;
	}
}
void CTowerHPDisplay::SetTowerHPPHX ( float fPercent )
{
	m_pHP3->SetPercent ( fPercent );
	SIZE Size;
	CString strName;
	m_pFont8->GetTextExtent ( strName.GetString (), Size );
	const UIRECT& rcNameBoxDummy = m_pNameBoxDummy->GetLocalPos();
	float fNameWidth = 0;
	fNameWidth = 0;

	{
		SetAlignFlag ( UI_FLAG_XSIZE );

		if ( fNameWidth < rcNameBoxDummy.sizeX )
		{
			fNameWidth = rcNameBoxDummy.sizeX;
		}

		//	텍스트 박스 크게 리사이징
		const UIRECT& rcNameLocalPos = m_pNameBox->GetLocalPos ();
		const UIRECT& rcNameBoxNew = UIRECT ( rcNameLocalPos.left, rcNameLocalPos.top,
			fNameWidth, rcNameLocalPos.sizeY );
		AlignSubControl ( rcNameLocalPos, rcNameBoxNew );

		const UIRECT& rcLocalPosOld = GetLocalPos ();
		UIRECT rcLocalPosNew = UIRECT ( rcLocalPosOld.left, rcLocalPosOld.top,
			rcLocalPosOld.sizeX + (fNameWidth - rcNameLocalPos.sizeX), rcLocalPosOld.sizeY );

		SetLocalPos ( rcLocalPosNew );
		SetGlobalPos ( rcLocalPosNew );
		
		m_pNameBox->AddTextNoSplit ( strName, NS_UITEXTCOLOR::WHITE );	
		m_strName = strName;
	}
}
void CTowerHPDisplay::GetTowerHPSG()
{
	m_pHP->GetPercent();
}
void CTowerHPDisplay::GetTowerHPMP()
{
	m_pHP2->GetPercent();
}
void CTowerHPDisplay::GetTowerHPPHX()
{
	m_pHP3->GetPercent();
}