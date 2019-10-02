// DlgCondition.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "RanEditLevelView.h"
#include "DlgCondition.h"
#include "ToolTab.h"
#include ".\dlgcondition.h"

#include "EtcFunction.h"
#include "GLItemMan.h"
#include "GLQUEST.h"
#include "GLQUESTMAN.h"

#include "DlgListItem.h"
#include "DlgListSkill.h"
#include "DlgListQuest.h"


// CDlgCondition dialog

IMPLEMENT_DYNAMIC(CDlgCondition, CPropertyPage)
CDlgCondition::CDlgCondition(LOGFONT logfont)
	: CPropertyPage(CDlgCondition::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
	, pReq( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgCondition::~CDlgCondition()
{
}

void CDlgCondition::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCondition, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_CANCEL, OnBnClickedButtonBasicCancel)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_SAVE, OnBnClickedButtonBasicSave)
	ON_BN_CLICKED(IDC_BUTTON_REQ_LEVEL, OnBnClickedButtonReqLevel)
	ON_BN_CLICKED(IDC_BUTTON_REQ_ITEM, OnBnClickedButtonReqItem)
	ON_BN_CLICKED(IDC_BUTTON_REQ_SKILL, OnBnClickedButtonReqSkill)
	ON_BN_CLICKED(IDC_BUTTON_REQ_COMQUEST, OnBnClickedButtonReqComquest)
	ON_BN_CLICKED(IDC_BUTTON_REQ_ACTQUEST, OnBnClickedButtonReqActquest)
	ON_BN_CLICKED(IDC_BUTTON_REQ_LIVING, OnBnClickedButtonReqLiving)
	ON_BN_CLICKED(IDC_BUTTON_REQ_BRIGHT, OnBnClickedButtonReqBright)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ITEM, OnBnClickedButtonDelItem)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SKILL, OnBnClickedButtonDelSkill)
	ON_BN_CLICKED(IDC_BUTTON_DEL_COMQUEST, OnBnClickedButtonDelComquest)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ACTQUEST, OnBnClickedButtonDelActquest)
END_MESSAGE_MAP()


// CDlgCondition message handlers
BOOL CDlgCondition::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	SetWin_Combo_Init( this, IDC_COMBO_REQ_SIGN_LEVEL, COMMENT::CDT_SIGN,  EMSIGN_SIZE );
	SetWin_Combo_Init( this, IDC_COMBO_REQ_SIGN_LIVING, COMMENT::CDT_SIGN,  EMSIGN_SIZE );
	SetWin_Combo_Init( this, IDC_COMBO_REQ_SIGN_BRIGHT, COMMENT::CDT_SIGN,  EMSIGN_SIZE );
	SetWin_Combo_Init( this, IDC_COMBO_REQ_SIGN_REBORN, COMMENT::CDT_SIGN,  EMSIGN_SIZE );
	return TRUE;
}

void CDlgCondition::SetData( GLLandMan*	pLand )
{
	if ( pLand ) 
	{
		pReq = NULL;
		pGLLand = pLand;
		pReq = pLand ->GetLevelRequire();

		if ( pGLLand && pReq )
		{
			ShowData();
		}
	}
}

void CDlgCondition::ShowData()
{
	if ( pGLLand && pReq )
	{

		SetWin_Num_int( this, IDC_EDIT_REQ_LEVEL1, pReq->m_wLevel );
		SetWin_Num_int( this, IDC_EDIT_REQ_LEVEL2, pReq->m_wLevel2 );
		SetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_LEVEL, pReq->m_signLevel );

		//SetWin_Num_int( this, IDC_EDIT_REQ_REBORN1, pReq->m_wRebornChar );
		//SetWin_Num_int( this, IDC_EDIT_REQ_REBORN2, pReq->m_wRebornChar2 );
		//SetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_REBORN, pReq->m_signRebornChar );

		SetWin_Num_int( this, IDC_EDIT_REQ_ITEM_MID, pReq->m_sItemID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_REQ_ITEM_SID, pReq->m_sItemID.wSubID );
		SITEM* pItem = GLItemMan::GetInstance().GetItem( pReq->m_sItemID );
		SetWin_Text( this, IDC_EDIT_REQ_ITEM_NAME, ( pItem )? pItem->GetName() : "Unknown Item" );
		
		SetWin_Num_int( this, IDC_EDIT_REQ_SKILL_MID, pReq->m_sSkillID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_REQ_SKILL_SID, pReq->m_sSkillID.wSubID );
		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData( pReq->m_sSkillID );
		SetWin_Text( this, IDC_EDIT_REQ_SKILL_NAME, ( pSkill )? pSkill->GetName() : "Unknown Skill" );

		SetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_MID, pReq->m_sComQuestID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_SID, pReq->m_sComQuestID.wSubID );
		GLQUEST *pQUESTCOM = GLQuestMan::GetInstance().Find ( pReq->m_sComQuestID.dwID );
		SetWin_Text( this, IDC_EDIT_REQ_COMQUEST_NAME, ( pQUESTCOM )? pQUESTCOM->GetTITLE() : "Unknown Quest" );

		SetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_MID, pReq->m_sActQuestID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_SID, pReq->m_sActQuestID.wSubID );

		GLQUEST *pQUESTACT = GLQuestMan::GetInstance().Find ( pReq->m_sActQuestID.dwID );
		SetWin_Text( this, IDC_EDIT_REQ_ACTQUEST_NAME, ( pQUESTACT )? pQUESTACT->GetTITLE() : "Unknown Quest" );

		SetWin_Num_int( this, IDC_EDIT_REQ_LIVING, pReq->m_nLiving );
		SetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_LIVING, pReq->m_signLiving );
		SetWin_Num_int( this, IDC_EDIT_REQ_BRIGHT, pReq->m_nBright );
		SetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_BRIGHT, pReq->m_signBright );

		SetWin_Check( this, IDC_CHECK_REQ_PARTYMEMBER, pReq->m_bPartyMbr );
	}
}

BOOL CDlgCondition::GetData()
{
	if ( pGLLand && pReq )
	{

		pReq->m_wLevel = GetWin_Num_int( this, IDC_EDIT_REQ_LEVEL1 );
		pReq->m_wLevel2 = GetWin_Num_int( this, IDC_EDIT_REQ_LEVEL2 );
		pReq->m_signLevel = (EMCDT_SIGN) GetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_LEVEL );

		//pReq->m_wRebornChar = GetWin_Num_int( this, IDC_EDIT_REQ_REBORN1 );
		//pReq->m_wRebornChar2 = GetWin_Num_int( this, IDC_EDIT_REQ_REBORN2 );
		//pReq->m_signRebornChar = (EMCDT_SIGN) GetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_REBORN );

		pReq->m_sItemID.wMainID = GetWin_Num_int( this, IDC_EDIT_REQ_ITEM_MID );
		pReq->m_sItemID.wSubID = GetWin_Num_int( this, IDC_EDIT_REQ_ITEM_SID );
		SITEM* pItem = GLItemMan::GetInstance().GetItem( pReq->m_sItemID );
		if ( !pItem && pReq->m_sItemID != NATIVEID_NULL() )
		{
			MessageBox( "Invalid Item" );
			return FALSE;
		}
		
		pReq->m_sSkillID.wMainID = GetWin_Num_int( this, IDC_EDIT_REQ_SKILL_MID );
		pReq->m_sSkillID.wSubID = GetWin_Num_int( this, IDC_EDIT_REQ_SKILL_SID );
		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData( pReq->m_sSkillID );
		if ( !pSkill && pReq->m_sSkillID != NATIVEID_NULL())
		{
			MessageBox( "Invalid Skill" );
			return FALSE;
		}

		pReq->m_sComQuestID.wMainID = GetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_MID );
		pReq->m_sComQuestID.wSubID = GetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_SID );
		GLQUEST *pQUESTCOM = GLQuestMan::GetInstance().Find ( pReq->m_sComQuestID.dwID );
		if ( !pQUESTCOM && pReq->m_sComQuestID != NATIVEID_NULL())
		{
			MessageBox( "Invalid Quest" );
			return FALSE;
		}

		pReq->m_sActQuestID.wMainID = GetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_MID );
		pReq->m_sActQuestID.wSubID = GetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_SID );
		GLQUEST *pQUESTACT = GLQuestMan::GetInstance().Find ( pReq->m_sActQuestID.dwID );
		if ( !pQUESTACT && pReq->m_sActQuestID != NATIVEID_NULL())
		{
			MessageBox( "Invalid Quest" );
			return FALSE;
		}

		pReq->m_nLiving = GetWin_Num_int( this, IDC_EDIT_REQ_LIVING );
		pReq->m_signLiving = (EMCDT_SIGN) GetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_LIVING );
		pReq->m_nBright = GetWin_Num_int( this, IDC_EDIT_REQ_BRIGHT );
		pReq->m_signBright = (EMCDT_SIGN) GetWin_Combo_Sel( this, IDC_COMBO_REQ_SIGN_BRIGHT );

		pReq->m_bPartyMbr = GetWin_Check( this, IDC_CHECK_REQ_PARTYMEMBER );

		return TRUE;
	}

	return FALSE;
}

void CDlgCondition::OnBnClickedButtonBasicCancel()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );
}

void CDlgCondition::OnBnClickedButtonBasicSave()
{
	if ( GetData() )
	{
		if ( m_pToolTab )
			m_pToolTab->ActiveDlgPage( DLG_MAIN );
	}
}

void CDlgCondition::OnBnClickedButtonReqLevel()
{
	// TODO: Add your control notification handler code here
}

void CDlgCondition::OnBnClickedButtonReqItem()
{
	if ( pGLLand && pReq )
	{
		CDlgListItem dlg;
		if ( dlg.DoModal() == IDOK )
		{
			SITEM* p = GLItemMan::GetInstance().GetItem( dlg.sIDSELECT );
			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_REQ_ITEM_MID, p->sBasicOp.sNativeID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_REQ_ITEM_SID, p->sBasicOp.sNativeID.wSubID );
				SetWin_Text( this, IDC_EDIT_REQ_ITEM_NAME, p->GetName() );
			}
		}
	}
}

void CDlgCondition::OnBnClickedButtonReqSkill()
{
	if ( pGLLand && pReq )
	{
		CDlgListSkill dlg;
		if ( dlg.DoModal() == IDOK )
		{
			PGLSKILL p = GLSkillMan::GetInstance().GetData( dlg.sIDSELECT );
			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_REQ_SKILL_MID, p->m_sBASIC.sNATIVEID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_REQ_SKILL_SID, p->m_sBASIC.sNATIVEID.wSubID );
				SetWin_Text( this, IDC_EDIT_REQ_SKILL_NAME, p->GetName() );
			}
		}
	}
}

void CDlgCondition::OnBnClickedButtonReqComquest()
{
	if ( pGLLand && pReq )
	{
		CDlgListQuest dlg;
		if ( dlg.DoModal() == IDOK )
		{
			GLQUEST *p = GLQuestMan::GetInstance().Find ( dlg.sIDSELECT.dwID );
			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_MID, p->m_sNID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_SID, p->m_sNID.wSubID );
				SetWin_Text( this, IDC_EDIT_REQ_COMQUEST_NAME, p->GetTITLE() );
			}
		}
	}
}

void CDlgCondition::OnBnClickedButtonReqActquest()
{
	if ( pGLLand && pReq )
	{
		CDlgListQuest dlg;
		if ( dlg.DoModal() == IDOK )
		{
			GLQUEST *p = GLQuestMan::GetInstance().Find ( dlg.sIDSELECT.dwID );
			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_MID, p->m_sNID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_SID, p->m_sNID.wSubID );
				SetWin_Text( this, IDC_EDIT_REQ_ACTQUEST_NAME, p->GetTITLE() );
			}
		}
	}
}

void CDlgCondition::OnBnClickedButtonReqLiving()
{
	// TODO: Add your control notification handler code here
}

void CDlgCondition::OnBnClickedButtonReqBright()
{
	// TODO: Add your control notification handler code here
}

void CDlgCondition::OnBnClickedButtonDelItem()
{
	SetWin_Num_int( this, IDC_EDIT_REQ_ITEM_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_REQ_ITEM_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_REQ_ITEM_NAME, "Unknown Item" );
}

void CDlgCondition::OnBnClickedButtonDelSkill()
{
	SetWin_Num_int( this, IDC_EDIT_REQ_SKILL_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_REQ_SKILL_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_REQ_SKILL_NAME, "Unknown Skill" );
}

void CDlgCondition::OnBnClickedButtonDelComquest()
{
	SetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_REQ_COMQUEST_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_REQ_COMQUEST_NAME, "Unknown Quest" );
}

void CDlgCondition::OnBnClickedButtonDelActquest()
{
	SetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_REQ_ACTQUEST_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_REQ_ACTQUEST_NAME, "Unknown Quest" );
}
