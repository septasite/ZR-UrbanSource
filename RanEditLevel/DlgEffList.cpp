// DlgEffList.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "RanEditLevelView.h"
#include "DlgEffList.h"
#include "ToolTab.h"
#include ".\dlgefflist.h"


// CDlgEffList dialog

IMPLEMENT_DYNAMIC(CDlgEffList, CPropertyPage)
CDlgEffList::CDlgEffList(LOGFONT logfont)
	: CPropertyPage(CDlgEffList::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgEffList::~CDlgEffList()
{
}

void CDlgEffList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EFF, m_list_Eff );
}


BEGIN_MESSAGE_MAP(CDlgEffList, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_EFF, OnNMDblclkListEff)
	ON_BN_CLICKED(IDC_BUTTON_EFF_ADD, OnBnClickedButtonEffAdd)
	ON_BN_CLICKED(IDC_BUTTON_EFF_EDIT, OnBnClickedButtonEffEdit)
	ON_BN_CLICKED(IDC_BUTTON_EFF_DEL, OnBnClickedButtonEffDel)
END_MESSAGE_MAP()


// CDlgEffList message handlers
BOOL CDlgEffList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Eff.SetExtendedStyle ( m_list_Eff.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/ );
		m_list_Eff.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 3;	
		char* szColumnName1[nColumnCount] = { "NUM", "EffectName", "EffectFileName" };
		int nColumnWidthPercent[nColumnCount] = { 10, 45, 45 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Eff.InsertColumn (i, &lvColumn );
		}
	}

	return TRUE;
}

void CDlgEffList::SetData( GLLandMan*	pLand )
{
	if ( pLand ) 
	{
		pGLLand = pLand;

		if ( pGLLand )
		{
			ShowData();
			CRanEditLevelView::GetView()->EnableSphere( true );
		}
	}
}

void CDlgEffList::ShowData()
{
	if ( pGLLand )
	{
		char szTempChar[512];
		int i = 0;

		m_list_Eff.DeleteAllItems();

		PLANDEFF pCurLandEff = pGLLand->GetLandEffList ();
		while ( pCurLandEff )
		{

			sprintf( szTempChar, "%d", i );
			m_list_Eff.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%s", pCurLandEff->m_szName );
			m_list_Eff.SetItemText( i, 1, szTempChar );

			sprintf( szTempChar, "%s", pCurLandEff->m_szFileName );
			m_list_Eff.SetItemText( i, 2, szTempChar );

			m_list_Eff.SetItemData( i, (DWORD_PTR)pCurLandEff );
			i++;

			pCurLandEff = pCurLandEff->m_pNext;
		}
	}
}

void CDlgEffList::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );

	CRanEditLevelView::GetView()->EnableSphere( false );
}

void CDlgEffList::OnNMDblclkListEff(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Eff.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand )
	{
		PLANDEFF pEff = (PLANDEFF)m_list_Eff.GetItemData( nSelect );
		if ( pEff )
		{
			JumpTo( pEff->m_matWorld );
		}
	}
}

void CDlgEffList::JumpTo( D3DXMATRIX sMat )
{
	D3DXVECTOR3 vPos = D3DXVECTOR3( sMat._41, sMat._42, sMat._43 );
	vPos.y += 10.0f;
	DxViewPort::GetInstance().CameraJump( vPos );
}

void CDlgEffList::OnBnClickedButtonEffAdd()
{
	if ( pGLLand )
	{
		if ( m_pToolTab )
			m_pToolTab->ActiveEffAdd();
	}
}

void CDlgEffList::OnBnClickedButtonEffEdit()
{
	int nSelect = m_list_Eff.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand )
	{
		PLANDEFF pEff = (PLANDEFF)m_list_Eff.GetItemData( nSelect );
		if ( pEff )
		{
			if ( m_pToolTab )
				m_pToolTab->ActiveEffEdit( pEff );
		}
	}
}

void CDlgEffList::OnBnClickedButtonEffDel()
{
	int nSelect = m_list_Eff.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand )
	{
		PLANDEFF pEff = (PLANDEFF)m_list_Eff.GetItemData( nSelect );
		if ( pEff )
		{
			pGLLand->DelLandEff( pEff );
			pGLLand->BuildSingleEffTree();
			ShowData();
		}
	}
}
