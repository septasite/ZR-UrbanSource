// SkillSearch.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "SkillSearch.h"
#include ".\skillsearch.h"
#include "RanManagerComments.h"
#include "GLDefine.h"
#include "EtcFunction.h"


// CSkillSearch dialog

IMPLEMENT_DYNAMIC(CSkillSearch, CDialog)
CSkillSearch::CSkillSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CSkillSearch::IDD, pParent)
{
	bMultiple = false;
	sSelectedSkill = NATIVEID_NULL();
}

CSkillSearch::~CSkillSearch()
{
}

void CSkillSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SKILL, m_list_Skill );
	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_cSearchType );
}


BEGIN_MESSAGE_MAP(CSkillSearch, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_SKILLSEARCH, OnBnClickedButtonSkillsearch)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, OnCbnSelchangeComboSearchType)
END_MESSAGE_MAP()


// CSkillSearch message handlers
BOOL CSkillSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	if (bMultiple)	m_list_Skill.SetExtendedStyle ( m_list_Skill.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	else	m_list_Skill.SetExtendedStyle ( m_list_Skill.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	
	m_list_Skill.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 5;	
	char* szColumnName1[nColumnCount] = { "Num","MID", "SID" , "Skill Name", "Skill Description"};
	int nColumnWidthPercent[nColumnCount] = { 10, 5,5,25,55 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Skill.InsertColumn (i, &lvColumn );
	}

	for ( int i = 0; i < SEARCHSKILL_SIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchSkillType[i].c_str() );
	}
	m_cSearchType.SetCurSel(0);

	OnCbnSelchangeComboSearchType();
	ShowSkills();
	return TRUE;  
}


void CSkillSearch::ShowSkills()
{
	int nNum = 0;
	char szTempChar[4096];
	m_list_Skill.DeleteAllItems();
	for ( WORD MID=0; MID<EMSKILLCLASS_NSIZE; ++MID )
	{
		for ( WORD SID=0; SID<GLSkillMan::MAX_CLASSSKILL; ++SID )
		{
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( MID, SID );
			if ( pSkill )
			{
				sprintf( szTempChar, "%d", nNum );
				m_list_Skill.InsertItem( nNum, szTempChar );

				sprintf( szTempChar, "%d", pSkill->m_sBASIC.sNATIVEID.wMainID );
				m_list_Skill.SetItemText(nNum,1,szTempChar);

				sprintf( szTempChar, "%d", pSkill->m_sBASIC.sNATIVEID.wSubID );
				m_list_Skill.SetItemText(nNum,2,szTempChar);

				sprintf( szTempChar, "%s", pSkill->GetName() );
				m_list_Skill.SetItemText(nNum,3,szTempChar);

				sprintf( szTempChar, "%s", pSkill->GetDesc() );
				m_list_Skill.SetItemText(nNum,4,szTempChar);

				nNum++;
			}
		}
	}
}

void CSkillSearch::OnBnClickedButtonOk()
{
	if (bMultiple)	
	{
		m_VecSearchResult.clear();
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_Skill.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Skill.GetCheck(nItem);
			if( bChecked)
			{
				SNATIVEID	wTempID;
				wTempID.wMainID = atoi ( m_list_Skill.GetItemText(nItem, 1).GetString() );
				wTempID.wSubID = atoi ( m_list_Skill.GetItemText(nItem, 2).GetString() );
				m_VecSearchResult.push_back(wTempID);
			}
		}
	}
	else	
	{
		int nSelect = m_list_Skill.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;
		sSelectedSkill.wMainID = atoi ( m_list_Skill.GetItemText(nSelect,1).GetString() );
		sSelectedSkill.wSubID = atoi ( m_list_Skill.GetItemText(nSelect,2).GetString() );
	}
	OnOK();
}

void CSkillSearch::OnBnClickedButtonCancel()
{
	OnCancel();
}

void CSkillSearch::OnBnClickedButtonSkillsearch()
{
	int nNum = 0;
	char szTempChar[4096];
	m_list_Skill.DeleteAllItems();
	int nSelect = m_cSearchType.GetCurSel();
	int nVal = GetWin_Num_int(this,IDC_EDIT_SEARCH);
	std::string strSearchKey  = GetWin_Text(this,IDC_EDIT_SEARCH);
	for ( WORD MID=0; MID<EMSKILLCLASS_NSIZE; ++MID )
	{
		for ( WORD SID=0; SID<GLSkillMan::MAX_CLASSSKILL; ++SID )
		{
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( MID, SID );
			if ( pSkill )
			{
				bool bFound = false;
				switch(nSelect)
				{
				case SEARCHSKILL_ALL:	bFound = true;	break;
				case SEARCHSKILL_MID:	
					{
						if (pSkill->m_sBASIC.sNATIVEID.wMainID == nVal )	bFound = true;	
					}break;
				case SEARCHSKILL_SID:	
					{
						if (pSkill->m_sBASIC.sNATIVEID.wSubID == nVal )	bFound = true;	
					}break;
				case SEARCHSKILL_NAME:	
					{
						std::string strSkillName = pSkill->GetName();
						unsigned found = strSkillName.find(strSearchKey);
						if (found!=std::string::npos)	bFound = true;
					}break;
				case SEARCHSKILL_BRAWLER:	
					{
						if ( pSkill->m_sLEARN.dwCLASS&GLCC_FIGHTER_M && pSkill->m_sLEARN.dwCLASS&GLCC_FIGHTER_W)	bFound = true;	
					}break;
				case SEARCHSKILL_SWORDSMAN:	
					{
						if ( pSkill->m_sLEARN.dwCLASS&GLCC_ARMS_M && pSkill->m_sLEARN.dwCLASS&GLCC_ARMS_W)	bFound = true;	
					}break;
				case SEARCHSKILL_ARCHER:	
					{
						if ( pSkill->m_sLEARN.dwCLASS&GLCC_ARCHER_M && pSkill->m_sLEARN.dwCLASS&GLCC_ARCHER_W)	bFound = true;	
					}break;
				case SEARCHSKILL_SHAMMAN:	
					{
						if ( pSkill->m_sLEARN.dwCLASS&GLCC_SPIRIT_M && pSkill->m_sLEARN.dwCLASS&GLCC_SPIRIT_W)	bFound = true;	
					}break;
				case SEARCHSKILL_EXTREME:	
					{
						if ( pSkill->m_sLEARN.dwCLASS&GLCC_EXTREME_M && pSkill->m_sLEARN.dwCLASS&GLCC_EXTREME_W)	bFound = true;	
					}break;
				case SEARCHSKILL_GUNNER:	
					{
						if ( pSkill->m_sLEARN.dwCLASS&GLCC_SCIENCE_M && pSkill->m_sLEARN.dwCLASS&GLCC_SCIENCE_W)	bFound = true;	
					}break;
				case SEARCHSKILL_ASSASSIN:	
					{
						if ( pSkill->m_sLEARN.dwCLASS&GLCC_ASSASSIN_M && pSkill->m_sLEARN.dwCLASS&GLCC_ASSASSIN_W)	bFound = true;	
					}break;
				};

				if (bFound)
				{
					sprintf( szTempChar, "%d", nNum );
					m_list_Skill.InsertItem( nNum, szTempChar );

					sprintf( szTempChar, "%d", pSkill->m_sBASIC.sNATIVEID.wMainID );
					m_list_Skill.SetItemText(nNum,1,szTempChar);

					sprintf( szTempChar, "%d", pSkill->m_sBASIC.sNATIVEID.wSubID );
					m_list_Skill.SetItemText(nNum,2,szTempChar);

					sprintf( szTempChar, "%s", pSkill->GetName() );
					m_list_Skill.SetItemText(nNum,3,szTempChar);

					sprintf( szTempChar, "%s", pSkill->GetDesc() );
					m_list_Skill.SetItemText(nNum,4,szTempChar);

					nNum++;
				}
			}
		}
	}
}

void CSkillSearch::OnCbnSelchangeComboSearchType()
{
	int nSelect = m_cSearchType.GetCurSel();
	switch (nSelect)
	{
	case SEARCHSKILL_MID:
	case SEARCHSKILL_SID:
	case SEARCHSKILL_NAME:
		{
			SetWin_Enable(this,IDC_EDIT_SEARCH,TRUE);
		}break;
	default:
		{
			SetWin_Enable(this,IDC_EDIT_SEARCH,FALSE);
		}break;
	};

}
