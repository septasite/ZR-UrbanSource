// DlgLandMarkList.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgLandMarkList.h"
#include "ToolTab.h"
#include ".\dlglandmarklist.h"
#include "RanEditLevelView.h"
#include "./GLLandMark.h"
// CDlgLandMarkList dialog

IMPLEMENT_DYNAMIC(CDlgLandMarkList, CPropertyPage)
CDlgLandMarkList::CDlgLandMarkList(LOGFONT logfont)
	: CPropertyPage(CDlgLandMarkList::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgLandMarkList::~CDlgLandMarkList()
{
}

void CDlgLandMarkList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LANDMARK, m_list_LandMark );
}


BEGIN_MESSAGE_MAP(CDlgLandMarkList, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_BN_CLICKED(IDC_BUTTON_LM_ADD, OnBnClickedButtonLmAdd)
	ON_BN_CLICKED(IDC_BUTTON_LM_DEL, OnBnClickedButtonLmDel)
	ON_BN_CLICKED(IDC_BUTTON_LM_EDIT, OnBnClickedButtonLmEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LANDMARK, OnNMDblclkListLandmark)
END_MESSAGE_MAP()


// CDlgLandMarkList message handlers
BOOL CDlgLandMarkList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_LandMark.SetExtendedStyle ( m_list_LandMark.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES/* | LVS_EX_CHECKBOXES */);
		m_list_LandMark.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 3;	
		char* szColumnName1[nColumnCount] = { "NUM", "MarkName", "" };
		int nColumnWidthPercent[nColumnCount] = { 10, 80, 10 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_LandMark.InsertColumn (i, &lvColumn );
		}
	}

	return TRUE;
}

void CDlgLandMarkList::SetData( GLLandMan*	pLand )
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

void CDlgLandMarkList::ShowData()
{
	if ( pGLLand )
	{
		char szTempChar[512];
		int i = 0;

		m_list_LandMark.DeleteAllItems();

		PLANDMARK pCur = pGLLand->GetLandMarkList();
		while ( pCur )
		{
			sprintf( szTempChar, "%d", i );
			m_list_LandMark.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%s", pCur->m_strMARK.c_str() );
			m_list_LandMark.SetItemText( i, 1, szTempChar );

			m_list_LandMark.SetItemData( i, (DWORD_PTR)pCur );

			i++;

			pCur = pCur->m_pNext;
		}
	}
}

void CDlgLandMarkList::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );

	CRanEditLevelView::GetView()->EnableSphere( false );
}

void CDlgLandMarkList::OnBnClickedButtonLmAdd()
{
	if ( pGLLand )
	{
		if ( m_pToolTab )
			m_pToolTab->ActiveLMAdd();
	}
}

void CDlgLandMarkList::OnBnClickedButtonLmDel()
{
	int nSelect = m_list_LandMark.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand )
	{
		PLANDMARK pLM  = (PLANDMARK)m_list_LandMark.GetItemData( nSelect );
		if ( pLM )
		{
			pGLLand->DelLandMark( pLM );
			pGLLand->BuildLandMarkTree();
			ShowData();
		}
	}
}

void CDlgLandMarkList::OnBnClickedButtonLmEdit()
{
	int nSelect = m_list_LandMark.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand )
	{
		PLANDMARK pLM  = (PLANDMARK)m_list_LandMark.GetItemData( nSelect );
		if ( pLM )
		{
			if ( m_pToolTab )
				m_pToolTab->ActiveLMEdit( pLM );
		}
	}
}

void CDlgLandMarkList::OnNMDblclkListLandmark(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSelect = m_list_LandMark.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	if ( pGLLand )
	{
		PLANDMARK pLM  = (PLANDMARK)m_list_LandMark.GetItemData( nSelect );
		if ( pLM )
		{
			D3DXVECTOR3 vPOS = pLM->m_pAffineParts->vTrans;
			vPOS.y += 10.0f;
			DxViewPort::GetInstance().CameraJump( vPOS );
		}
	}

	*pResult = 0;
}
