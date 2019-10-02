// DlgGateList.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgGateList.h"
#include ".\dlggatelist.h"
#include "ToolTab.h"
#include "RanEditLevelView.h"

// CDlgGateList dialog

IMPLEMENT_DYNAMIC(CDlgGateList, CPropertyPage)
CDlgGateList::CDlgGateList(LOGFONT logfont)
	: CPropertyPage(CDlgGateList::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
	, pGate( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgGateList::~CDlgGateList()
{
}

void CDlgGateList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GATE, m_list_Gate );
}


BEGIN_MESSAGE_MAP(CDlgGateList, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_GATE, OnNMDblclkListGate)
	ON_BN_CLICKED(IDC_BUTTON_GATE_ADD, OnBnClickedButtonGateAdd)
	ON_BN_CLICKED(IDC_BUTTON_GATE_EDIT, OnBnClickedButtonGateEdit)
	ON_BN_CLICKED(IDC_BUTTON_GATE_DEL, OnBnClickedButtonGateDel)
END_MESSAGE_MAP()


// CDlgGateList message handlers
BOOL CDlgGateList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Gate.SetExtendedStyle ( m_list_Gate.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/ );
		m_list_Gate.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 3;	
		char* szColumnName1[nColumnCount] = { "NUM", "Gate ID", "GateName" };
		int nColumnWidthPercent[nColumnCount] = { 10, 20, 70 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Gate.InsertColumn (i, &lvColumn );
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgGateList::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );

	CRanEditLevelView::GetView()->EnableSphere( false );
}

void CDlgGateList::SetData( GLLandMan*	pLand )
{
	if ( pLand )
	{
		pGLLand = pLand;

		pGate = NULL;
		pGate = &pLand->GetLandGateMan();

		if ( pGLLand && pGate )
		{
			ShowData();
			CRanEditLevelView::GetView()->EnableSphere( true );
		}
	}
}

void CDlgGateList::ShowData()
{
	if ( pGLLand && pGate )
	{
		char szTempChar[512];
		int i = 0;

		m_list_Gate.DeleteAllItems();

		PDXLANDGATE pLandGate = pGate->GetListLandGate();
		while ( pLandGate )
		{
			sprintf( szTempChar, "%d", i );
			m_list_Gate.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%d", pLandGate->GetGateID());
			m_list_Gate.SetItemText( i, 1, szTempChar );

			sprintf( szTempChar, "%s", pLandGate->GetName() );
			m_list_Gate.SetItemText( i, 2, szTempChar );

			m_list_Gate.SetItemData( i, (DWORD_PTR)pLandGate );
			i++;
			pLandGate = pLandGate->m_pNext;
		}
	}
}

void CDlgGateList::JumpTo( D3DXVECTOR3 vMax, D3DXVECTOR3 vMin )
{
	float fDistX = vMax.x-vMin.x;
	float fDistY = vMax.y-vMin.y;
	float fDistZ = vMax.z-vMin.z;

	float fCenterX = vMin.x + ( fDistX / 2.0f );
	float fCenterY = vMin.y + ( fDistY / 2.0f );
	float fCenterZ = vMin.z + ( fDistZ / 2.0f );

	DxViewPort::GetInstance().CameraJump( D3DXVECTOR3( fCenterX, fCenterY, fCenterZ ) );
}

void CDlgGateList::OnNMDblclkListGate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Gate.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand && pGate )
	{
		PDXLANDGATE pLandGate = (PDXLANDGATE)m_list_Gate.GetItemData( nSelect );
		if ( pLandGate )
		{
			JumpTo( pLandGate->GetMax(), pLandGate->GetMin() );
		}
	}
}

void CDlgGateList::OnBnClickedButtonGateAdd()
{
	if ( pGLLand && pGate )
	{
		if ( m_pToolTab )
			m_pToolTab->ActiveGateAdd();
	}
}

void CDlgGateList::OnBnClickedButtonGateEdit()
{
	int nSelect = m_list_Gate.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand && pGate )
	{
		PDXLANDGATE pLandGate = (PDXLANDGATE)m_list_Gate.GetItemData( nSelect );
		if ( pLandGate )
		{
			if ( m_pToolTab )
				m_pToolTab->ActiveGateEdit( pLandGate );
		}
	}
}

void CDlgGateList::OnBnClickedButtonGateDel()
{
	int nSelect = m_list_Gate.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand && pGate )
	{
		PDXLANDGATE pLandGate = (PDXLANDGATE)m_list_Gate.GetItemData( nSelect );
		if ( pLandGate )
		{
			std::string strName = pLandGate->GetName();
			if ( strName.size() != 0 )
			{
				pGate->DelLandGate( pLandGate->GetName() );
			}
			else
			{
				pGate->DelLandGate( pLandGate->GetGateID() );
			}	

			ShowData();
		}
	}
}
