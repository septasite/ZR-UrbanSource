// DlgCrowList.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgCrowList.h"
#include "ToolTab.h"
#include ".\dlgcrowlist.h"

#include "RanEditLevelView.h"
#include "EtcFunction.h"
#include "GenerateName.h"
#include "CrowReplace.h"
#include "CrowReplaceMulti.h"

#include "../RanClientLib/G-Logic/GLCharDefine.h"

// CDlgCrowList dialog

IMPLEMENT_DYNAMIC(CDlgCrowList, CPropertyPage)
CDlgCrowList::CDlgCrowList(LOGFONT logfont)
	: CPropertyPage(CDlgCrowList::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
{
	strEDITID = "";
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgCrowList::~CDlgCrowList()
{
}

void CDlgCrowList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CROW, m_list_Crow );
}


BEGIN_MESSAGE_MAP(CDlgCrowList, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CROW, OnNMDblclkListCrow)
	ON_BN_CLICKED(IDC_BUTTON_CROWLIST_NEW, OnBnClickedButtonCrowlistNew)
	ON_BN_CLICKED(IDC_BUTTON_CROWLIST_DELETE, OnBnClickedButtonCrowlistDelete)
	ON_BN_CLICKED(IDC_BUTTON_CROWLIST_EDIT, OnBnClickedButtonCrowlistEdit)
	ON_BN_CLICKED(IDC_BUTTON_CROWLIST_COPY, OnBnClickedButtonCrowlistCopy)
	ON_BN_CLICKED(IDC_BUTTON_CROWLIST_PASTENEW, OnBnClickedButtonCrowlistPastenew)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE_ID, OnBnClickedButtonReplaceId)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEFILTER, OnBnClickedButtonRemovefilter)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE_ID2, OnBnClickedButtonReplaceId2)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_INVALID, OnBnClickedButtonShowInvalid)
	ON_BN_CLICKED(IDC_BUTTON_SHOWNPC, OnBnClickedButtonShownpc)
END_MESSAGE_MAP()


// CDlgCrowList message handlers
BOOL CDlgCrowList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Crow.SetExtendedStyle ( m_list_Crow.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES /*| LVS_SHOWSELALWAYS*/ );
		m_list_Crow.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 6;	
		char* szColumnName1[nColumnCount] = { "NUM", "GID", "MID", "SID", "Name", "Crow"};
		int nColumnWidthPercent[nColumnCount] = { 15, 10, 10, 10, 20, 35 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Crow.InsertColumn (i, &lvColumn );
		}
	}

	SNATIVEID sID = NATIVEID_NULL();
	SetWin_Num_int( this, IDC_EDIT_FILTER_MID, sID.wMainID );
	SetWin_Num_int( this, IDC_EDIT_FILTER_SID, sID.wSubID );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgCrowList::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );

	CRanEditLevelView::GetView()->EnableSphere( false );
}

void CDlgCrowList::SetData( GLLandMan*	pLand )
{
	if ( pLand )
	{
		pGLLand = pLand;
		ShowData();
		CRanEditLevelView::GetView()->EnableSphere( true );
	}
}

void CDlgCrowList::ShowData()
{
	if ( !pGLLand )	return;

	char szTempChar[512];
	int i = 0;
	m_list_Crow.DeleteAllItems();

	SNATIVEID sID;
	sID.wMainID = GetWin_Num_int( this, IDC_EDIT_FILTER_MID );
	sID.wSubID = GetWin_Num_int( this, IDC_EDIT_FILTER_SID );

	MOBSCHEDULELIST * GLMobSchList = pGLLand->GetMobSchMan()->GetMobSchList();
	SGLNODE<GLMobSchedule*>* pCur = GLMobSchList->m_pHead;
	while ( pCur )
	{
		BOOL bSHOW = TRUE;
		if ( sID != NATIVEID_NULL() )
		{
			if ( pCur->Data->m_CrowID != sID )
				bSHOW = FALSE;
		}

		if ( bSHOW )
		{
			sprintf( szTempChar, "%d", i );
			m_list_Crow.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_dwGlobID );
			m_list_Crow.SetItemText( i, 1, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_CrowID.wMainID );
			m_list_Crow.SetItemText( i, 2, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_CrowID.wSubID );
			m_list_Crow.SetItemText( i, 3, szTempChar );

			sprintf( szTempChar, "%s", pCur->Data->m_szName );
			m_list_Crow.SetItemText( i, 4, szTempChar );

			PCROWDATA pCrow = GLCrowDataMan::GetInstance().GetCrowData( pCur->Data->m_CrowID );

			sprintf( szTempChar, "%s", (pCrow)? pCrow->GetName() : "Unknown Mob" );
			m_list_Crow.SetItemText( i, 5, szTempChar );

			i++;
		}
		
		pCur = pCur->pNext;
	}
}

void CDlgCrowList::OnNMDblclkListCrow(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if ( !pGLLand )	return;

	int nSelect = m_list_Crow.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	std::string strCrow = m_list_Crow.GetItemText( nSelect, 4 );
	
	SGLNODE<GLMobSchedule*>* pSched = pGLLand->GetMobSchMan()->FindMobSch( strCrow.c_str() );
	if ( pSched )
	{
		D3DXVECTOR3 vPos = pSched->Data->m_pAffineParts->vTrans;
		JumpTo( vPos );
	}
}

void CDlgCrowList::OnBnClickedButtonCrowlistNew()
{
	if ( !pGLLand )	return;

	if ( m_pToolTab )
		m_pToolTab->ActiveCrowAdd();
}

void CDlgCrowList::OnBnClickedButtonCrowlistDelete()
{
	if ( !pGLLand )	return;
	
	for( int nItem = 0 ; nItem <  m_list_Crow.GetItemCount(); nItem++)
	{
		BOOL bChecked = m_list_Crow.GetCheck(nItem);
		if( bChecked )
		{
			std::string strCrow = m_list_Crow.GetItemText( nItem, 4 );
			GLMobSchedule	*pSched = pGLLand->GetMobSchMan()->FindMobSch( strCrow.c_str() )->Data;
			if ( pSched )
			{
				DWORD dwID = pSched->m_dwGlobID;
				BOOL bOK = pGLLand->GetMobSchMan()->DelMobSch( strCrow.c_str() );
				if ( bOK )
				{
					pGLLand->DropOutCrow( dwID );
				}
			}
		}	
	}

	ShowData();
}

void CDlgCrowList::OnBnClickedButtonCrowlistEdit()
{
	if ( !pGLLand )	return;

	int nSelect = m_list_Crow.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	std::string strCrow = m_list_Crow.GetItemText( nSelect, 4 );

	if ( m_pToolTab )
		m_pToolTab->ActiveCrowEdit( strCrow.c_str() );
}

void CDlgCrowList::OnBnClickedButtonCrowlistCopy()
{
	int nSelect = m_list_Crow.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	std::string strCrow = m_list_Crow.GetItemText( nSelect, 4 );
	SetWin_Text( this, IDC_EDIT_COPY, strCrow.c_str() );
}

void CDlgCrowList::OnBnClickedButtonCrowlistPastenew()
{
	std::string strCopy = GetWin_Text( this, IDC_EDIT_COPY );
	if ( strCopy.size() != 0 && pGLLand )
	{
		GLMobSchedule*	pSched = pGLLand->GetMobSchMan()->FindMobSch( strCopy.c_str() )->Data;
		if ( pSched )
		{
			D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;

			GLMobSchedule sSched;
			
			std::string str = CrowNameNew( pGLLand );
			StringCchCopy( sSched.m_szName, GLMobSchedule::EM_MAXSZNAME, str.c_str() );
			sSched.m_pAffineParts->vTrans = vPOS; 

			sSched.m_CrowID			= pSched->m_CrowID;
			sSched.m_fReGenTime		= pSched->m_fReGenTime;
			sSched.m_nRegenMin		= pSched->m_nRegenMin;
			sSched.m_nRegenHour		= pSched->m_nRegenHour;
			memcpy( sSched.m_bDayOfWeek, pSched->m_bDayOfWeek, sizeof(sSched.m_bDayOfWeek) );

			sSched.m_bLeaderMonster	= pSched->m_bLeaderMonster;
			sSched.m_strGroupName	= pSched->m_strGroupName.c_str();
			sSched.m_sMobActList		= pSched->m_sMobActList;
			sSched.m_dwPC_REGEN_GATEID	= pSched->m_dwPC_REGEN_GATEID;
			sSched.m_bRendGenPos		= pSched->m_bRendGenPos;
			sSched.m_wRendGenPosNum		= pSched->m_wRendGenPosNum;
			sSched.m_wRendGenPosDist	= pSched->m_wRendGenPosDist;
			sSched.m_vectorRendGenPos	= pSched->m_vectorRendGenPos;

			D3DXVECTOR3 vDis = pSched->m_pAffineParts->vTrans - vPOS;
			sSched.ModifierSchList( &vDis, pGLLand->GetNavi() );
			sSched.GenerateRendGenPos( pGLLand->GetNavi() );

			pGLLand->GetMobSchMan()->AddMobSch( sSched );

			ShowData();
		}		
	}
}

void CDlgCrowList::SelectCrow( std::string strName )
{
	if ( !pGLLand )	return;

	for( int nItem = 0 ; nItem <  m_list_Crow.GetItemCount(); nItem++)
	{
		m_list_Crow.SetItemState( nItem, ~LVIS_SELECTED, LVIS_SELECTED  ) ;	
		m_list_Crow.SetCheck( nItem, false );
	}

	for( int nItem = 0 ; nItem <  m_list_Crow.GetItemCount(); nItem++)
	{
		std::string strCrow = m_list_Crow.GetItemText( nItem, 4 );
		if ( !strcmp( strCrow.c_str(), strName.c_str() ) )
		{
			m_list_Crow.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED ) ;
			m_list_Crow.EnsureVisible( nItem, TRUE );
			m_list_Crow.SetCheck( nItem, true );

			SGLNODE<GLMobSchedule*>* pSched = pGLLand->GetMobSchMan()->FindMobSch( strCrow.c_str() );
			if ( pSched )
			{
				EffTo( pSched->Data->m_pAffineParts->vTrans );
			}

			break;
		}	
	}
}

void CDlgCrowList::JumpTo( D3DXVECTOR3 vPos )
{
	EffTo( vPos );
	vPos.y += 10.0f ;
	DxViewPort::GetInstance().CameraJump( vPos );
}

void CDlgCrowList::EffTo( D3DXVECTOR3 vPos )
{
}

void CDlgCrowList::OnBnClickedButtonReplaceId()
{
	if ( pGLLand )
	{
		CCrowReplace dlg;

		if ( dlg.DoModal() == IDOK )
		{
			SNATIVEID sIDFROM = dlg.GetIDFROM();
			SNATIVEID sIDTO = dlg.GetIDTO();
			PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( sIDTO );
			if ( !pCROW )
			{
				MessageBox( "Invalid target ID" );
				return;
			}

			//do some magic here :P

			MOBSCHEDULELIST * GLMobSchList = pGLLand->GetMobSchMan()->GetMobSchList();
			SGLNODE<GLMobSchedule*>* pCur = GLMobSchList->m_pHead;
			while ( pCur )
			{
				if ( pCur->Data->m_CrowID == sIDFROM )
				{
					pCur->Data->m_CrowID = sIDTO;

					pGLLand->DropOutCrow( pCur->Data->m_dwGlobID );
				}

				pCur = pCur->pNext;
			}

			ShowData();
		}
	}
}

void CDlgCrowList::OnBnClickedButtonRefresh()
{
	ShowData();
}

void CDlgCrowList::OnBnClickedButtonRemovefilter()
{
	SNATIVEID sID = NATIVEID_NULL();
	SetWin_Num_int( this, IDC_EDIT_FILTER_MID, sID.wMainID );
	SetWin_Num_int( this, IDC_EDIT_FILTER_SID, sID.wSubID );
}

void CDlgCrowList::OnBnClickedButtonReplaceId2()
{
	if ( pGLLand )
	{
		CCrowReplaceMulti dlg;

		if ( dlg.DoModal() == IDOK )
		{
			int nTOTAL = dlg.m_Vec.size();
			for ( int i=0; i<nTOTAL; ++ i )
			{
				SREPLACEID SIDR;
				SIDR = dlg.m_Vec[i];

				SNATIVEID sIDFROM = SIDR.sFROM;
				SNATIVEID sIDTO = SIDR.sTO;
				PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( sIDTO );
				if ( !pCROW )
				{
					MessageBox( "Invalid target ID" );
					continue;
				}

				//do some magic here :P

				MOBSCHEDULELIST * GLMobSchList = pGLLand->GetMobSchMan()->GetMobSchList();
				SGLNODE<GLMobSchedule*>* pCur = GLMobSchList->m_pHead;
				while ( pCur )
				{
					if ( pCur->Data->m_CrowID == sIDFROM )
					{
						pCur->Data->m_CrowID = sIDTO;

						pGLLand->DropOutCrow( pCur->Data->m_dwGlobID );
					}

					pCur = pCur->pNext;
				}

			}
			ShowData();
		}
	}
}

void CDlgCrowList::OnBnClickedButtonShowInvalid()
{
	if ( !pGLLand )	return;

	char szTempChar[512];
	int i = 0;
	m_list_Crow.DeleteAllItems();

	//shows invalid crow 
	MOBSCHEDULELIST * GLMobSchList = pGLLand->GetMobSchMan()->GetMobSchList();
	SGLNODE<GLMobSchedule*>* pCur = GLMobSchList->m_pHead;
	while ( pCur )
	{
		PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( pCur->Data->m_CrowID );
		if ( !pCROW )
		{
			sprintf( szTempChar, "%d", i );
			m_list_Crow.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_dwGlobID );
			m_list_Crow.SetItemText( i, 1, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_CrowID.wMainID );
			m_list_Crow.SetItemText( i, 2, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_CrowID.wSubID );
			m_list_Crow.SetItemText( i, 3, szTempChar );

			sprintf( szTempChar, "%s", pCur->Data->m_szName );
			m_list_Crow.SetItemText( i, 4, szTempChar );

			PCROWDATA pCrow = GLCrowDataMan::GetInstance().GetCrowData( pCur->Data->m_CrowID );

			sprintf( szTempChar, "%s", (pCrow)? pCrow->GetName() : "Unknown Mob" );
			m_list_Crow.SetItemText( i, 5, szTempChar );

			i++;
		}

		pCur = pCur->pNext;
	}
}

void CDlgCrowList::OnBnClickedButtonShownpc()
{
	if ( !pGLLand )	return;

	char szTempChar[512];
	int i = 0;
	m_list_Crow.DeleteAllItems();

	//shows npc crow 
	MOBSCHEDULELIST * GLMobSchList = pGLLand->GetMobSchMan()->GetMobSchList();
	SGLNODE<GLMobSchedule*>* pCur = GLMobSchList->m_pHead;
	while ( pCur )
	{
		PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( pCur->Data->m_CrowID );
		if ( pCROW && pCROW->m_sBasic.m_emCrow == CROW_NPC )
		{
			sprintf( szTempChar, "%d", i );
			m_list_Crow.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_dwGlobID );
			m_list_Crow.SetItemText( i, 1, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_CrowID.wMainID );
			m_list_Crow.SetItemText( i, 2, szTempChar );

			sprintf( szTempChar, "%d", pCur->Data->m_CrowID.wSubID );
			m_list_Crow.SetItemText( i, 3, szTempChar );

			sprintf( szTempChar, "%s", pCur->Data->m_szName );
			m_list_Crow.SetItemText( i, 4, szTempChar );

			PCROWDATA pCrow = GLCrowDataMan::GetInstance().GetCrowData( pCur->Data->m_CrowID );

			sprintf( szTempChar, "%s", (pCrow)? pCrow->GetName() : "Unknown Mob" );
			m_list_Crow.SetItemText( i, 5, szTempChar );

			i++;
		}

		pCur = pCur->pNext;
	}
}
