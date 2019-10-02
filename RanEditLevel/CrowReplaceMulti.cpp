// CrowReplaceMulti.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "CrowReplaceMulti.h"
#include ".\crowreplacemulti.h"
#include "DlgListCrow.h"
#include "EtcFunction.h"

// CCrowReplaceMulti dialog

IMPLEMENT_DYNAMIC(CCrowReplaceMulti, CDialog)
CCrowReplaceMulti::CCrowReplaceMulti(CWnd* pParent /*=NULL*/)
	: CDialog(CCrowReplaceMulti::IDD, pParent)
{
}

CCrowReplaceMulti::~CCrowReplaceMulti()
{
}

void CCrowReplaceMulti::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPLACE, m_list );
}


BEGIN_MESSAGE_MAP(CCrowReplaceMulti, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CROW, OnBnClickedButtonCrow)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_DELETE2, OnBnClickedButtonDelete2)
END_MESSAGE_MAP()


// CCrowReplaceMulti message handlers
BOOL CCrowReplaceMulti::OnInitDialog()
{
	CDialog::OnInitDialog();

	SNATIVEID sIDFROM = NATIVEID_NULL();
	SNATIVEID sIDTO = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_MID_FROM, sIDFROM.wMainID );
	SetWin_Num_int( this, IDC_EDIT_SID_FROM, sIDFROM.wSubID );
	SetWin_Num_int( this, IDC_EDIT_MID_TO, sIDTO.wMainID );
	SetWin_Num_int( this, IDC_EDIT_SID_TO, sIDTO.wSubID );
	SetWin_Text( this, IDC_EDIT_CROW, "" );

	m_Vec.clear();

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list.SetExtendedStyle ( m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES /*| LVS_SHOWSELALWAYS*/ );
		m_list.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 5;	
		char* szColumnName1[nColumnCount] = { "NUM", "FROM MID", "FROM SID", "TO MID", "TO SID" };
		int nColumnWidthPercent[nColumnCount] = { 10, 20, 20, 20, 20 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list.InsertColumn (i, &lvColumn );
		}
	}

	return TRUE;
}

void CCrowReplaceMulti::OnBnClickedButtonCrow()
{
	CDlgListCrow dlg;
	if ( dlg.DoModal() == IDOK )
	{
		PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( dlg.sIDSELECT );
		if ( pCROW )
		{
			SetWin_Num_int( this, IDC_EDIT_MID_TO, pCROW->m_sBasic.sNativeID.wMainID );
			SetWin_Num_int( this, IDC_EDIT_SID_TO, pCROW->m_sBasic.sNativeID.wSubID );
			SetWin_Text( this, IDC_EDIT_CROW, pCROW->GetName() );
		}
	}
}

void CCrowReplaceMulti::OnBnClickedButtonAdd()
{
	SREPLACEID SIDR;

	SIDR.sFROM.wMainID = (WORD)GetWin_Num_int( this, IDC_EDIT_MID_FROM );
	SIDR.sFROM.wSubID = (WORD)GetWin_Num_int( this, IDC_EDIT_SID_FROM );
	SIDR.sTO.wMainID = (WORD)GetWin_Num_int( this, IDC_EDIT_MID_TO );
	SIDR.sTO.wSubID = (WORD)GetWin_Num_int( this, IDC_EDIT_SID_TO );

	m_Vec.push_back( SIDR );

	ResetInput();

	UpdateList();
}

void CCrowReplaceMulti::UpdateList()
{
	char szTempChar[512];

	m_list.DeleteAllItems();

	for ( int i=0; i<m_Vec.size(); ++i )
	{
		sprintf( szTempChar, "%d", i );
		m_list.InsertItem( i, szTempChar );

		sprintf( szTempChar, "%d", m_Vec[i].sFROM.wMainID );
		m_list.SetItemText( i, 1, szTempChar );

		sprintf( szTempChar, "%d", m_Vec[i].sFROM.wSubID );
		m_list.SetItemText( i, 2, szTempChar );

		sprintf( szTempChar, "%d", m_Vec[i].sTO.wMainID );
		m_list.SetItemText( i, 3, szTempChar );

		sprintf( szTempChar, "%d", m_Vec[i].sTO.wSubID );
		m_list.SetItemText( i, 4, szTempChar );
	}
}

void CCrowReplaceMulti::ResetInput()
{
	SNATIVEID sIDRFROM = NATIVEID_NULL();
	SNATIVEID sIDRTO = NATIVEID_NULL();

	SetWin_Num_int( this, IDC_EDIT_MID_FROM, sIDRFROM.wMainID );
	SetWin_Num_int( this, IDC_EDIT_SID_FROM, sIDRFROM.wSubID );
	SetWin_Num_int( this, IDC_EDIT_MID_TO, sIDRTO.wMainID );
	SetWin_Num_int( this, IDC_EDIT_SID_TO, sIDRTO.wSubID );
	SetWin_Text( this, IDC_EDIT_CROW, "" );
}

void CCrowReplaceMulti::OnBnClickedOk()
{
	ResetInput();
	OnOK();
}

void CCrowReplaceMulti::OnBnClickedCancel()
{
	m_Vec.clear();

	ResetInput();
	OnCancel();
}

void CCrowReplaceMulti::OnBnClickedButtonDelete()
{
	for( int nItem = 0 ; nItem <  m_list.GetItemCount(); nItem++)
	{
		BOOL bChecked = m_list.GetCheck(nItem);
		if( bChecked )
		{
			SREPLACEID SIDR;

			GetWin_Num_int( this, IDC_EDIT_MID_FROM );
			GetWin_Num_int( this, IDC_EDIT_SID_FROM );
			GetWin_Num_int( this, IDC_EDIT_MID_TO );
			GetWin_Num_int( this, IDC_EDIT_SID_TO );

			SIDR.sFROM.wMainID = (WORD) atoi( m_list.GetItemText( nItem, 1 ) );
			SIDR.sFROM.wSubID = (WORD) atoi( m_list.GetItemText( nItem, 2 ) );
			SIDR.sTO.wMainID = (WORD) atoi( m_list.GetItemText( nItem, 3 ) );
			SIDR.sTO.wSubID = (WORD) atoi( m_list.GetItemText( nItem, 4 ) );

			for ( int i=0; i<m_Vec.size(); ++i )
			{
				if ( m_Vec[i].sFROM == SIDR.sFROM && m_Vec[i].sTO == SIDR.sTO )
				{
					m_Vec.erase( m_Vec.begin()+i );
				}
			}
		}	
	}

	UpdateList();
}

void CCrowReplaceMulti::OnBnClickedButtonDelete2()
{
	m_Vec.clear();
	UpdateList();
}
