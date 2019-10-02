// DlgListMap.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgListMap.h"
#include ".\dlglistmap.h"
#include "EtcFunction.h"

// CDlgListMap dialog

IMPLEMENT_DYNAMIC(CDlgListMap, CDialog)
CDlgListMap::CDlgListMap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListMap::IDD, pParent)
{
	sIDSELECT = NATIVEID_NULL();
}

CDlgListMap::~CDlgListMap()
{
}

void CDlgListMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAP, m_list_Map );
}


BEGIN_MESSAGE_MAP(CDlgListMap, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CANCEL, OnBnClickedButtonListCancel)
	ON_BN_CLICKED(IDC_BUTTON_LIST_OK, OnBnClickedButtonListOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MAP, OnNMClickListMap)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MAP, OnNMRclickListMap)
END_MESSAGE_MAP()


// CDlgListMap message handlers
BOOL CDlgListMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Map.SetExtendedStyle ( m_list_Map.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/ );
		m_list_Map.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 5;	
		char* szColumnName1[nColumnCount] = { "NUM", "Map MID", "Map SID", "Map Name", "Lev Name" };
		int nColumnWidthPercent[nColumnCount] = { 5, 10, 10, 40, 35 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Map.InsertColumn (i, &lvColumn );
		}
	}

	m_sMapList.LoadMapList( "mapslist.ini" );
	GLMapList::FIELDMAP_ITER iter = m_sMapList.GetMapList().begin();
	GLMapList::FIELDMAP_ITER iter_end = m_sMapList.GetMapList().end();


	char szTempChar[512];
	int i = 0;

	m_list_Map.DeleteAllItems();

	for ( ; iter!=iter_end; ++iter )
	{
		bool	bFind = false;
		SMAPNODE* pNode = &(*iter).second;

		if ( pNode )
		{
			sprintf( szTempChar, "%d", i );
			m_list_Map.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%d", pNode->sNativeID.wMainID );
			m_list_Map.SetItemText( i, 1, szTempChar );
			sprintf( szTempChar, "%d", pNode->sNativeID.wSubID );
			m_list_Map.SetItemText( i, 2, szTempChar );
			sprintf( szTempChar, "%s", pNode->strMapName.c_str() );
			m_list_Map.SetItemText( i, 3, szTempChar );
			sprintf( szTempChar, "%s", pNode->strFile.c_str() );
			m_list_Map.SetItemText( i, 4, szTempChar );

			m_list_Map.SetItemData( i, (DWORD_PTR)pNode );
			i++;
		}
	}

	sIDSELECT = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_LIST_MID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_LIST_SID, 65535 );
	SetWin_Text( this, IDC_EDIT_LIST_NAME, "" );

	return TRUE;
}

void CDlgListMap::OnBnClickedButtonListCancel()
{
	sIDSELECT = NATIVEID_NULL();
	OnCancel();
}

void CDlgListMap::OnBnClickedButtonListOk()
{
	sIDSELECT.wMainID = GetWin_Num_int( this, IDC_EDIT_LIST_MID );
	sIDSELECT.wSubID = GetWin_Num_int( this, IDC_EDIT_LIST_SID );

	OnOK();
}

void CDlgListMap::OnNMClickListMap(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSelect = m_list_Map.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SMAPNODE* pNode = (SMAPNODE*)m_list_Map.GetItemData( nSelect );
	if ( pNode )
	{
		SetWin_Num_int( this, IDC_EDIT_LIST_MID, pNode->sNativeID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_LIST_SID, pNode->sNativeID.wSubID );
		SetWin_Text( this, IDC_EDIT_LIST_NAME, pNode->strMapName.c_str() );
	}

	*pResult = 0;
}

void CDlgListMap::OnNMRclickListMap(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSelect = m_list_Map.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SMAPNODE* pNode = (SMAPNODE*)m_list_Map.GetItemData( nSelect );
	if ( pNode )
	{
		SetWin_Num_int( this, IDC_EDIT_LIST_MID, pNode->sNativeID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_LIST_SID, pNode->sNativeID.wSubID );
		SetWin_Text( this, IDC_EDIT_LIST_NAME, pNode->strMapName.c_str() );
	}

	*pResult = 0;
}
