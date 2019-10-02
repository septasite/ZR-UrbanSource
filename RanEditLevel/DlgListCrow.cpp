// DlgListCrow.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgListCrow.h"
#include ".\dlglistcrow.h"
#include "EtcFunction.h"


// CDlgListCrow dialog

IMPLEMENT_DYNAMIC(CDlgListCrow, CDialog)
CDlgListCrow::CDlgListCrow(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListCrow::IDD, pParent)
{
	sIDSELECT = NATIVEID_NULL();
}

CDlgListCrow::~CDlgListCrow()
{
}

void CDlgListCrow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_ctrlCrowTree);
}


BEGIN_MESSAGE_MAP(CDlgListCrow, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CANCEL, OnBnClickedButtonListCancel)
	ON_BN_CLICKED(IDC_BUTTON_LIST_OK, OnBnClickedButtonListOk)
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnNMClickTree)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnNMRclickTree)
END_MESSAGE_MAP()


// CDlgListCrow message handlers
BOOL CDlgListCrow::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlCrowTree.DeleteAllItems();
	m_TreeRoot = m_ctrlCrowTree.InsertItem ( "Root Node" );

	for ( int MID = 0; MID < GLCrowDataMan::MAX_CROW_MID; MID++ )
	{
		HTREEITEM hMainCrow= NULL;
		HTREEITEM hSubCrow = NULL;

		for ( int SID = 0; SID < GLCrowDataMan::MAX_CROW_SID; SID++ )
		{        	

			SCROWDATA* pCrow = GLCrowDataMan::GetInstance().GetCrowData ( MID, SID );
			if ( pCrow )
			{
				CString strCrow;
				strCrow = GetFormatName ( pCrow );

				if ( !hMainCrow )
				{
					hMainCrow = m_ctrlCrowTree.InsertItem ( strCrow, m_TreeRoot );
					m_ctrlCrowTree.SetItemData ( hMainCrow, (DWORD_PTR)pCrow );
				}else{
					hSubCrow = m_ctrlCrowTree.InsertItem ( strCrow, hMainCrow );
					m_ctrlCrowTree.SetItemData ( hSubCrow, (DWORD_PTR)pCrow );
				}
			}
		}
	}

	sIDSELECT = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_LIST_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_LIST_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_LIST_NAME, "" );

	return TRUE;
}

const char* CDlgListCrow::GetFormatName ( PCROWDATA pCrow  )
{
	GASSERT ( pCrow );
	static	CString strCrow;
	if ( pCrow )
	{	
		strCrow.Format ( "[%03d/%03d][LVL:%d]  %s",
		pCrow->m_sBasic.sNativeID.wMainID ,pCrow->m_sBasic.sNativeID.wSubID , pCrow->m_sBasic.m_wLevel, pCrow->GetName() );
	}
	return strCrow.GetString ();
}

void CDlgListCrow::OnBnClickedButtonListCancel()
{
	sIDSELECT = NATIVEID_NULL();
	OnCancel();
}

void CDlgListCrow::OnBnClickedButtonListOk()
{
	sIDSELECT.wMainID = GetWin_Num_int( this, IDC_EDIT_LIST_MID );
	sIDSELECT.wSubID = GetWin_Num_int( this, IDC_EDIT_LIST_SID );

	OnOK();
}

void CDlgListCrow::OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	POINT OriginPoint;
	GetCursorPos ( &OriginPoint );

	m_ctrlCrowTree.ScreenToClient( &OriginPoint );
	UINT uFlag = 0;

	HTREEITEM hCrow = m_ctrlCrowTree.HitTest ( CPoint(OriginPoint), &uFlag );

	if ( hCrow )
	{
		m_ctrlCrowTree.SelectItem ( hCrow );
		if ( uFlag & TVHT_ONITEMLABEL )
		{			
			PCROWDATA pCrow =  ( (PCROWDATA)m_ctrlCrowTree.GetItemData ( hCrow ) );

			if ( pCrow )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, pCrow->sNativeID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, pCrow->sNativeID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, pCrow->GetName() );
			}
		}
	}
}

void CDlgListCrow::OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	POINT OriginPoint;
	GetCursorPos ( &OriginPoint );
	m_ctrlCrowTree.ScreenToClient( &OriginPoint );

	UINT uFlag = 0;

	HTREEITEM hCrow = m_ctrlCrowTree.HitTest ( CPoint(OriginPoint), &uFlag );

	if ( hCrow )
	{
		m_ctrlCrowTree.SelectItem ( hCrow );
		if ( uFlag & TVHT_ONITEMLABEL )
		{			
			PCROWDATA pCrow =  ( (PCROWDATA)m_ctrlCrowTree.GetItemData ( hCrow ) );

			if ( pCrow )
			{
				SetWin_Num_int( this, IDC_EDIT_LIST_MID, pCrow->sNativeID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_LIST_SID, pCrow->sNativeID.wSubID );
				SetWin_Text( this, IDC_EDIT_LIST_NAME, pCrow->GetName() );
			}
		}
	}
}
