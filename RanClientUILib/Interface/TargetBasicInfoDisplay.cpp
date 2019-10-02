#include "StdAfx.h"
#include "./TargetBasicInfoDisplay.h"

#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GLGaeaClient.h"
#include "GameTextControl.h"
#include "d3dfont.h"
#include "GLQuest.h"
#include "GLQUESTMAN.h"
#include "../Interface/UITextControl.h"
#include "../EngineUIlib/GUInterface/UIDebugSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTargetBasicInfoDisplay::CTargetBasicInfoDisplay () :
	m_pNameBoxDummy ( NULL )
   ,m_InfoCharPCLine ( NULL )
   ,m_InfoCharMobsLine ( NULL )
   ,m_InfoCharNpcLine ( NULL )

{
	//memset ( m_pSchoolMark, 0, sizeof ( CUIControl* ) * nSCHOOLMARK );
	//memset ( m_pPartyMark, 0, sizeof ( CUIControl* ) * nPARTYMARK );
}

CTargetBasicInfoDisplay::~CTargetBasicInfoDisplay ()
{
}

void CTargetBasicInfoDisplay::CreateSubControl ()
{
	m_pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, _DEFAULT_FONT_SHADOW_FLAG );

	CBasicLineBoxEx* pLineBox = new CBasicLineBoxEx;
	pLineBox->CreateSub ( this, "TARGETINFO_DETAIL_LINEBOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxVarTextBoxNew ( "BASIC_VAR_LINE_CHAR_BOX" );
	pLineBox->SetDiffuse ( D3DCOLOR_ARGB (175,0xC0,0xC0,0xC0) );
	pLineBox->SetNoUpdate ( true );
	RegisterControl ( pLineBox );
	m_InfoCharPCLine = pLineBox;

	CBasicLineBoxEx* pLineBoxMob = new CBasicLineBoxEx;
	pLineBoxMob->CreateSub ( this, "TARGETINFO_DETAIL_LINEBOX_MOB", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBoxMob->CreateBaseBoxVarTextBoxNew ( "BASIC_VAR_LINE_MOB_BOX" );
	pLineBoxMob->SetDiffuse ( D3DCOLOR_ARGB (175,0xC0,0xC0,0xC0) );
	pLineBoxMob->SetNoUpdate ( true );
	RegisterControl ( pLineBoxMob );
	m_InfoCharMobsLine = pLineBoxMob;

	CBasicLineBoxEx* pLineBoxNpc = new CBasicLineBoxEx;
	pLineBoxNpc->CreateSub ( this, "TARGETINFO_DETAIL_LINEBOX_NPC", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBoxNpc->CreateBaseBoxVarTextBoxNew ( "BASIC_VAR_LINE_NPC_BOX" );
	pLineBoxNpc->SetDiffuse ( D3DCOLOR_ARGB (175,0xC0,0xC0,0xC0) );
	pLineBoxNpc->SetNoUpdate ( true );
	RegisterControl ( pLineBoxNpc );
	m_InfoCharNpcLine = pLineBoxNpc;

	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, "TARGETINFO_DETAIL_MOB_TEXT", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
    pTextBox->SetFont ( m_pFont8 );
	pTextBox->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( pTextBox );
	m_InfoCharMobs = pTextBox;

	CBasicTextBox* pTextBoxNpc = new CBasicTextBox;
	pTextBoxNpc->CreateSub ( this, "TARGETINFO_DETAIL_NPC_TEXT", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
    pTextBoxNpc->SetFont ( m_pFont8 );
	pTextBoxNpc->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( pTextBoxNpc );
	m_InfoCharNpc = pTextBoxNpc;
		
	CBasicTextBox* pTextBoxPC = new CBasicTextBox;
	pTextBoxPC->CreateSub ( this, "TARGETINFO_DETAIL_CHAR_TEXT", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
    pTextBoxPC->SetFont ( m_pFont8 );
	pTextBoxPC->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( pTextBoxPC );
	m_InfoCharPC = pTextBoxPC;
}

CUIControl*	CTargetBasicInfoDisplay::CreateControl ( const char* szControl, WORD wAlignFlag )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, wAlignFlag );
	RegisterControl ( pControl );
	return pControl;
}

void CTargetBasicInfoDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

}

void CTargetBasicInfoDisplay::SetTargetInfo ( PGLCHARCLIENT pCHAR, DWORD TypeColor ) /*, int nSchoolMark, int nPartyMark )*/
{
	CString GangName;
	CString strParty;
	
	m_InfoCharNpcLine->SetVisibleSingle ( false );
	m_InfoCharMobsLine->SetVisibleSingle ( false );
	m_InfoCharPCLine->SetVisibleSingle ( true );
	m_InfoCharPC->ClearText();
	m_InfoCharMobs->ClearText();
	m_InfoCharNpc->ClearText();

	//strCombine.Format("Name : %s",pCHAR->GetName());
	//m_InfoCharPC->AddTextNoSplit(strCombine);

	//strCombine.Format("Lv : %d / Rb : %d",pCHAR->GetLevel(),pCHAR->GetReborn() );
	//m_InfoCharPC->AddTextNoSplit(strCombine);

	const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();
	sCharData.m_wSchool;

	/*if ( sCharData.m_wSchool != pCHAR->GetSchool() ) {
	strCombine.Format("Lv.%d %s",pCHAR->GetLevel(),pCHAR->GetName());
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::DISABLE );
	}
	else{
	strCombine.Format("Lv.%d %s",pCHAR->GetLevel(),pCHAR->GetName());
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::PALEGREEN );
	}*/

	strCombine.Format("Lv.%d %s",pCHAR->GetLevel(),pCHAR->GetName());
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::PALEGREEN );
	
	if ( sCharData.m_wSchool != pCHAR->GetSchool() ) {
	strCombine.Format("%s",ID2GAMEWORD("ACADEMY_NAME",pCHAR->GetSchool()));
	m_InfoCharPC->AddTextNoSplit(strCombine , NS_UITEXTCOLOR::DISABLE);
	}
	else{
	strCombine.Format("%s",ID2GAMEWORD("ACADEMY_NAME",pCHAR->GetSchool()));
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::DEFAULT );
	}

	strCombine.Format("%s",COMMENT::CHARCLASS[CharClassToIndex(pCHAR->GetClass())].c_str());
	m_InfoCharPC->AddTextNoSplit(strCombine);
	
	if ( !(pCHAR->GETCLUBID()) ) GangName = "There is no club joined.";
	else GangName = pCHAR->GetClubName();

	if ( !(pCHAR->IsClubMaster()) ){
		strCombine.Format("%s",GangName);
		m_InfoCharPC->AddTextNoSplit(strCombine);
	}else{
		strCombine.Format("%s - Leader",GangName);
		m_InfoCharPC->AddTextNoSplit(strCombine);
	}

	if (pCHAR->IsPartyMem() == true){
	strCombine.Format ( "Already joined in a party.", strParty );
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::IDNAMECOLOR );
	}
	else if (pCHAR->IsPartyMaster() == true){
	strCombine.Format ( "Already joined in a party. - Leader", strParty );
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::IDNAMECOLOR );
	}
	else{
	strCombine.Format ( "There is no party joined.");
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::IDNAMECOLOR );
	}

	strCombine.Format("Shift-click to open the window of shortcut keys.");
	m_InfoCharPC->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::LIGHTYELLOW );

}

void CTargetBasicInfoDisplay::SetTargetInfoMobs ( int fNow, int fMax, int fPercent, CString Name, DWORD Level, DWORD TypeColor  ) /*, int nSchoolMark, int nPartyMark )*/
{
	m_InfoCharPCLine->SetVisibleSingle ( false );
	m_InfoCharNpcLine->SetVisibleSingle ( false );
	m_InfoCharMobsLine->SetVisibleSingle ( true );
	m_InfoCharMobs->ClearText();
	m_InfoCharPC->ClearText();
	m_InfoCharNpc->ClearText();

	/*strCombine.Format("Name : %s",Name);
	//m_InfoCharMobs->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_InfoCharMobs->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::WHITE );

	strCombine.Format("Level : %d",Level);
	//m_InfoCharMobs->SetOneLineText ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_InfoCharMobs->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::WHITE );*/

	strCombine.Format("Lv.%d %s",Level,Name);
	m_InfoCharMobs->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::WHITE );

	strCombine.Format("%d/%d (%d", fNow,fMax,fPercent );
	strCombine += "%)";
	m_InfoCharMobs->AddTextNoSplit(strCombine, NS_UITEXTCOLOR::LIGHTYELLOW );
}

void CTargetBasicInfoDisplay::SetTargetInfoNpc ( int fNow, int fMax, int fPercent, CString Name, DWORD TypeColor ) /*, int nSchoolMark, int nPartyMark )*/
{
	m_InfoCharPCLine->SetVisibleSingle ( false );
	m_InfoCharNpcLine->SetVisibleSingle ( true );
	m_InfoCharMobsLine->SetVisibleSingle ( false );
	m_InfoCharMobs->ClearText();
	m_InfoCharPC->ClearText();
	m_InfoCharNpc->ClearText();

	SIZE Size;
	CString strQuestBegin;
	CString strQuest;

	if ( Name == "College Representative" || Name == "Nurse (Ring)" || Name == "Nurse" )
	{	
	m_pFont8->GetTextExtent ( Name.GetString (), Size );
	strCombine.Format("%s",Name);
	m_InfoCharNpc->AddTextNoSplit ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_InfoCharNpc->AddTextNoSplit ( "Save Point", NS_UITEXTCOLOR::LIGHTYELLOW );
	m_InfoCharNpc->AddTextNoSplit ( "You have no available quest.", NS_UITEXTCOLOR::IDNAMECOLOR );
	}

	else if ( Name == "Mainframe Computer" )
	{	
	m_pFont8->GetTextExtent ( Name.GetString (), Size );
	strCombine.Format("%s",Name);
	m_InfoCharNpc->AddTextNoSplit ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_strName = Name;
	m_InfoCharNpc->AddTextNoSplit ( "Begin Verification", NS_UITEXTCOLOR::LIGHTYELLOW );
	m_InfoCharNpc->AddTextNoSplit ( "Authentication Machine", NS_UITEXTCOLOR::IDNAMECOLOR );
	}

	else if ( Name == "Grocery Merchant" || Name == "Shaman Instructor" || Name == "Archery Instructor" || Name == "Brawler Instructor" || Name == "Sword Instructor" )
	{	
	m_pFont8->GetTextExtent ( Name.GetString (), Size );
	strCombine.Format("%s",Name);
	m_InfoCharNpc->AddTextNoSplit ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_strName = Name;
	m_InfoCharNpc->AddTextNoSplit ( "Open Shop", NS_UITEXTCOLOR::LIGHTYELLOW );
	m_InfoCharNpc->AddTextNoSplit ( "You have no available quest.", NS_UITEXTCOLOR::IDNAMECOLOR );
	}

	else if ( Name == "Student Director" || Name == "Police" || Name == "Special Agent" || Name == "Construction Supervisor" || Name == "Cleaner" || Name == "Zopar" || Name == "Banshee"
		|| Name == "Cleaner" )
	{	
	m_pFont8->GetTextExtent ( Name.GetString (), Size );
	strCombine.Format("%s",Name);
	m_InfoCharNpc->AddTextNoSplit ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_strName = Name;
	m_InfoCharNpc->AddTextNoSplit ( "Begin Talk", NS_UITEXTCOLOR::LIGHTYELLOW );
	m_InfoCharNpc->AddTextNoSplit ( "You have no available quest.", NS_UITEXTCOLOR::IDNAMECOLOR );
	}

	else if ( Name == "Locker Custodian" || Name == "Safe" || Name == "Locker Guard" || Name == "Gold Storage" )
	{	
	m_pFont8->GetTextExtent ( Name.GetString (), Size );
	strCombine.Format("%s",Name);
	m_InfoCharNpc->AddTextNoSplit ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_strName = Name;
	m_InfoCharNpc->AddTextNoSplit ( "Open Locker", NS_UITEXTCOLOR::LIGHTYELLOW );
	m_InfoCharNpc->AddTextNoSplit ( "Store your personal items.", NS_UITEXTCOLOR::IDNAMECOLOR );
	}

	else if ( Name == "Bus Stop" || Name == "Bus Driver" || Name == "Bus Info Terminal" )
	{	
	m_pFont8->GetTextExtent ( Name.GetString (), Size );
	strCombine.Format("%s",Name);
	m_InfoCharNpc->AddTextNoSplit ( strCombine, NS_UITEXTCOLOR::WHITE );
	m_strName = Name;
	m_InfoCharNpc->AddTextNoSplit ( "Ride Bus", NS_UITEXTCOLOR::LIGHTYELLOW );
	m_InfoCharNpc->AddTextNoSplit ( "You have no available quest.", NS_UITEXTCOLOR::IDNAMECOLOR );
	}

	else {
	strCombine.Format("%s",Name);
	m_InfoCharNpc->AddTextNoSplit( strCombine, NS_UITEXTCOLOR::WHITE );

	strCombine.Format("%d/%d (%d", fNow,fMax,fPercent );
	strCombine += "%)";
	m_InfoCharNpc->AddTextNoSplit( strCombine, NS_UITEXTCOLOR::LIGHTYELLOW );
	m_InfoCharNpc->AddTextNoSplit ( "You have no available quest.", NS_UITEXTCOLOR::IDNAMECOLOR );
	}
}