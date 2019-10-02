#include "StdAfx.h"
#include "CrowTargetInfo.h"
#include "InnerInterface.h"
#include "BasicLineBox.h"
#include "../EngineLib/DxCommon/d3dfont.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "BasicLineBox.h"
#include "BasicLineBoxEx.h"
#include "../Interface/GameTextControl.h"
#include "../Interface/UITextControl.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"

#include "../RanClientLib/G-Logic/GLGaeaClient.h"
#include "../RanClientLib/G-Logic/GLCrowData.h"
#include "../RanClientLib/G-Logic/GLCrow.h"
#include "../RanClientLib/G-Logic/GLCrowClient.h"
#include "../RanClientLib/G-Logic/GlogicEx.h"
#include "d3dfont.h"

#include "GLCharData.h"
#include "GLCharacter.h"
#include "GLChar.h"
#include "GLCharClient.h"
#include "GLogicData.h"
#include "GLCharDefine.h"
#include "UIInfoLoader.h"
#include "GLCrowRenList.h"
#include "GLStringTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCrowTargetInfo::CCrowTargetInfo () :
	m_pNameBoxDummy ( NULL )
{
}

CCrowTargetInfo::~CCrowTargetInfo ()
{
}

void CCrowTargetInfo::CreateSubControl ()
{
	m_pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	/*m_pTargetBox = new CBasicLineBoxEx;
	m_pTargetBox->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pTargetBox->CreateBaseBoxVarTextBoxNew ( "RNCROW_TARGET_INFOBOX" );
	m_pTargetBox->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pTargetBox );*/

	CBasicLineBoxEx* m_pTargetBox = new CBasicLineBoxEx;
	m_pTargetBox->CreateSub ( this, "RNCROW_TARGET_INFOBOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pTargetBox->CreateBaseBoxVarTextBoxNew ( "BASIC_VAR_LINE_MOB_BOX" );
	m_pTargetBox->SetDiffuse ( D3DCOLOR_ARGB (175,0xC0,0xC0,0xC0) );
	m_pTargetBox->SetNoUpdate ( true );
	RegisterControl ( m_pTargetBox );
	//m_InfoCharMobsLine = pLineBoxMob;

	CBasicTextBox* m_pHP = new CBasicTextBox;
	m_pHP->CreateSub ( this, "HP_NAMEBOX" );
    m_pHP->SetFont ( m_pFont8 );
	m_pHP->SetTextAlign ( TEXT_ALIGN_LEFT );
	m_pHP->SetControlNameEx ( "HP Text" );	
	m_pHP->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	RegisterControl ( m_pHP );
	m_pHPBox = m_pHP;

	CBasicTextBox* pNameBox = new CBasicTextBox;
	pNameBox->CreateSub ( this, "CROW_NAMEBOX" );
    pNameBox->SetFont ( m_pFont8 );
	pNameBox->SetTextAlign ( TEXT_ALIGN_LEFT );
	pNameBox->SetControlNameEx ( "HP Text" );	
	pNameBox->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	RegisterControl ( pNameBox );
	m_pNameBox = pNameBox;
	
	m_pNameBoxDummy = CreateControl ( "CROW_NAMEBOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
}

CUIControl*	CCrowTargetInfo::CreateControl ( const char* szControl, WORD wAlignFlag )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, wAlignFlag );
	RegisterControl ( pControl );
	return pControl;
}

void CCrowTargetInfo::SetTargetInfo ( int fNow, int fMax, int fPercent,DWORD Level,  CString strName, STARGETID sTargetID )
{	
	// ADDED BY EDUJ
	    PGLCHARCLIENT pCHAR = GLGaeaClient::GetInstance().GetChar ( sTargetID.dwID );
        PGLCROWCLIENT pCrow = GLGaeaClient::GetInstance().GetActiveMap()->GetCrow ( sTargetID.dwID );
		DWORD dwCrowLevel = pCrow->GETLEVEL();
		DWORD dwCharLevel = GLGaeaClient::GetInstance().GetCharacter()->GETLEVEL();
        float fEXP_RATE = GLCONST_CHAR::GETEXP_RATE ( dwCharLevel, dwCrowLevel ); 
  if ( !(fMax<=3) )
  {
		CString strCombine;
		CString combine;
		strCombine.Format ( "%d/%d (%d", fNow,fMax,fPercent );
		strCombine += "%)";
		m_pHPBox->SetOneLineText ( strCombine, NS_UITEXTCOLOR::GOLD );
		m_pNameBox->ClearText ();
  }else{
		CString strTemp;
		strTemp.Format ( "%s",strName );
		m_pHPBox->SetOneLineText ( strTemp, NS_UITEXTCOLOR::DODGERBLUE );	
		m_pNameBox->ClearText ();  
  }

		SIZE Size;
		m_pFont8->GetTextExtent ( strName.GetString (), Size );
		
    if ( fEXP_RATE==0 )
	{
		CString strTemp;
		strTemp.Format ( "%s",strName );
		m_pNameBox->SetOneLineText ( strTemp, NS_UITEXTCOLOR::WHITE );	
		m_strName = strName;
	}else{
		CString strTemp;
		strTemp.Format ( "%s",strName );
		m_pNameBox->SetOneLineText ( strTemp, NS_UITEXTCOLOR::RED );	
		m_strName = strName;
	}

}
