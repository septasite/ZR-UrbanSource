// DlgListQuest.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgListQuest.h"
#include ".\dlglistquest.h"
#include "EtcFunction.h"


// CDlgListQuest dialog

IMPLEMENT_DYNAMIC(CDlgListQuest, CDialog)
CDlgListQuest::CDlgListQuest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListQuest::IDD, pParent)
{
	sIDSELECT = NATIVEID_NULL();
}

CDlgListQuest::~CDlgListQuest()
{
}

void CDlgListQuest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
}


BEGIN_MESSAGE_MAP(CDlgListQuest, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CANCEL, OnBnClickedButtonListCancel)
	ON_BN_CLICKED(IDC_BUTTON_LIST_OK, OnBnClickedButtonListOk)
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnNMClickTree)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnNMRclickTree)
END_MESSAGE_MAP()


// CDlgListQuest message handlers
BOOL CDlgListQuest::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlTree.DeleteAllItems();
	m_TreeRoot = m_ctrlTree.InsertItem ( "Root Node" );

	GLQuestMan::MAPQUEST& m_mapQuestMap = GLQuestMan::GetInstance().GetMap();

	GLQuestMan::MAPQUEST_ITER iter_pos;
	DWORD dwQuestID = 0;
	PQUESTNODE pQuestNode = NULL;
	CString strItem;

	for ( iter_pos = m_mapQuestMap.begin(); iter_pos != m_mapQuestMap.end(); iter_pos++ )
	{
		HTREEITEM hMainItem= NULL;
		
		dwQuestID = (DWORD) iter_pos->first;	
		pQuestNode = (PQUESTNODE) &iter_pos->second;

        if ( pQuestNode ) 
		{	
			strItem = GetFormatName ( pQuestNode );
			hMainItem = m_ctrlTree.InsertItem ( strItem, m_TreeRoot );
			m_ctrlTree.SetItemData ( hMainItem, (DWORD_PTR)pQuestNode );
		}
	}

	sIDSELECT = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_LIST_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_LIST_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_LIST_NAME, "" );

	return TRUE;
}

const char* CDlgListQuest::GetFormatName ( PQUESTNODE p )
{
	GASSERT ( p );

	static	CString str;

	if ( !p )	return "";

	if ( p->pQUEST->m_strTITLE != "" )
	{
		str.Format ( "[%04d~%04d]  [%s] [%s]",
		p->pQUEST->m_sNID.wMainID, p->pQUEST->m_sNID.wSubID, p->pQUEST->m_strTITLE.c_str(), p->strFILE.c_str() );
	}

	return str.GetString ();
}

void CDlgListQuest::OnBnClickedButtonListCancel()
{
	sIDSELECT = NATIVEID_NULL();
	OnCancel();
}

void CDlgListQuest::OnBnClickedButtonListOk()
{
	sIDSELECT.wMainID = GetWin_Num_int( this, IDC_EDIT_LIST_MID );
	sIDSELECT.wSubID = GetWin_Num_int( this, IDC_EDIT_LIST_SID );

	OnOK();
}

void CDlgListQuest::OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	POINT OriginPoint;
	GetCursorPos ( &OriginPoint );

	m_ctrlTree.ScreenToClient( &OriginPoint );
	UINT uFlag = 0;

	HTREEITEM h = m_ctrlTree.HitTest ( CPoint(OriginPoint), &uFlag );

	if ( h )
	{
		m_ctrlTree.SelectItem ( h );
		if ( uFlag & TVHT_ONITEMLABEL )
		{			
			PQUESTNODE p =  ( (PQUESTNODE)m_ctrlTree.GetItemData ( h ) );

			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, p->pQUEST->m_sNID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, p->pQUEST->m_sNID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, p->pQUEST->GetTITLE() );
			}
		}
	}
}

void CDlgListQuest::OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	POINT OriginPoint;
	GetCursorPos ( &OriginPoint );
	m_ctrlTree.ScreenToClient( &OriginPoint );

	UINT uFlag = 0;

	HTREEITEM h = m_ctrlTree.HitTest ( CPoint(OriginPoint), &uFlag );

	if ( h )
	{
		m_ctrlTree.SelectItem ( h );
		if ( uFlag & TVHT_ONITEMLABEL )
		{			
			PQUESTNODE p =  ( (PQUESTNODE)m_ctrlTree.GetItemData ( h ) );

			if ( p )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, p->pQUEST->m_sNID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, p->pQUEST->m_sNID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, p->pQUEST->GetTITLE() );
			}
		}
	}
}