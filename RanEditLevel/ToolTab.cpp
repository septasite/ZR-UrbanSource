#include "stdafx.h"
#include <vector>
#include "resource.h"
#include "ToolTab.h"
#include "RanEditLevel.h"
#include "RanEditLevelView.h"

#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTab

IMPLEMENT_DYNAMIC(CToolTab, CPropertySheet)

CToolTab::CToolTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd)
	 : CPropertySheet("", pParentWnd),
	 m_bNoTabs(FALSE),
	 m_pWndParent(NULL),
	 m_iDistanceFromTop(0),
	 m_pFont ( NULL ),

	m_DlgMain( logfont ),
	m_DlgBasic( logfont ),
	m_DlgCondition( logfont ),
	m_DlgEtcFunction( logfont ),
	m_DlgCrowList( logfont ),
	m_DlgGateList( logfont ),
	m_DlgEffList( logfont ),
	m_DlgLandMarkList( logfont ),
	m_DlgCrowEdit( logfont ),
	m_DlgGateEdit( logfont ),
	m_DlgEffEdit( logfont ),
	m_DlgLMEdit( logfont )
{
	m_pWndParent = pParentWnd;
	m_Rect = rect;

	m_bNoTabs = TRUE;
	m_bStacked = FALSE;

	m_DlgMain.SetToolTab ( this );
	AddPage ( &m_DlgMain );

	m_DlgBasic.SetToolTab ( this );
	AddPage ( &m_DlgBasic );

	m_DlgCondition.SetToolTab ( this );
	AddPage ( &m_DlgCondition );

	m_DlgEtcFunction.SetToolTab ( this );
	AddPage ( &m_DlgEtcFunction );

	m_DlgCrowList.SetToolTab ( this );
	AddPage ( &m_DlgCrowList );

	m_DlgGateList.SetToolTab ( this );
	AddPage ( &m_DlgGateList );

	m_DlgEffList.SetToolTab ( this );
	AddPage ( &m_DlgEffList );

	m_DlgLandMarkList.SetToolTab ( this );
	AddPage ( &m_DlgLandMarkList );

	m_DlgCrowEdit.SetToolTab ( this ); 
	AddPage ( &m_DlgCrowEdit );

	m_DlgGateEdit.SetToolTab ( this ); 
	AddPage ( &m_DlgGateEdit );

	m_DlgEffEdit.SetToolTab ( this ); 
	AddPage ( &m_DlgEffEdit );

	m_DlgLMEdit.SetToolTab ( this ); 
	AddPage ( &m_DlgLMEdit );

	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CToolTab::~CToolTab()
{
	SAFE_DELETE( m_pFont );
}

static int module_piButtons[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP };

BOOL CToolTab::OnInitDialog() 
{
	HWND hTabWnd;
	CRect rectTabCtrl;
	ChangeDialogFont( this, m_pFont, CDF_NONE );

	if( m_Rect.right )
	{
		hTabWnd = (HWND)::GetDlgItem(m_hWnd, AFX_IDC_TAB_CONTROL);
		ASSERT(hTabWnd != NULL);
		::GetWindowRect(hTabWnd, &rectTabCtrl); 
		ScreenToClient(rectTabCtrl);

		if( !m_bNoTabs && rectTabCtrl.right > (m_Rect.Width() - 3) )
		{
			rectTabCtrl.right = m_Rect.Width() - 3;
		}
		rectTabCtrl.bottom = 32; 
		::MoveWindow( hTabWnd, 0, m_iDistanceFromTop, rectTabCtrl.Width(), rectTabCtrl.bottom, TRUE );
		BOOL bResult = (BOOL)Default(); 

		if( m_bNoTabs )
		{
			::ShowWindow(hTabWnd, SW_HIDE);
			::EnableWindow(hTabWnd, FALSE);
		}

		if (!m_bStacked)
		{
			hTabWnd = (HWND)SendMessage(PSM_GETTABCONTROL);
			if (hTabWnd != NULL)
			{
				CWnd::ModifyStyle(hTabWnd, TCS_MULTILINE, TCS_SINGLELINE, 0);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			HWND hWnd = ::GetDlgItem(m_hWnd, module_piButtons[i]);
			if (hWnd != NULL)
			{
				::ShowWindow(hWnd, SW_HIDE);
				::EnableWindow(hWnd, FALSE);
			}
		}

		MoveWindow( m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom /*- cyDiff*/ );

		return bResult;
	}

	return CPropertySheet::OnInitDialog();
}

BEGIN_MESSAGE_MAP(CToolTab, CPropertySheet)
	//{{AFX_MSG_MAP(CToolTab)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CToolTab::ActiveDlgPage( int nPage )
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	switch ( nPage )
	{
	case DLG_MAIN:
		{
			SetActivePage ( DLG_MAIN );
		}break;

	case DLG_BASIC:
		{
			SetActivePage ( DLG_BASIC );
			m_DlgBasic.SetData( pGLLand );
		}break;

	case DLG_CONDITION:
		{
			SetActivePage ( DLG_CONDITION );
			m_DlgCondition.SetData( pGLLand );
		}break;

	case DLG_ETCFUNCTION:
		{
			SetActivePage ( DLG_ETCFUNCTION );
			m_DlgEtcFunction.SetData( pGLLand );
		}break;

	case DLG_CROWLIST:
		{
			SetActivePage ( DLG_CROWLIST );
			m_DlgCrowList.SetData( pGLLand );
		}break;

	case DLG_GATELIST:
		{
			SetActivePage ( DLG_GATELIST );
			m_DlgGateList.SetData( pGLLand );
		}break;

	case DLG_EFFLIST:
		{
			SetActivePage ( DLG_EFFLIST );
			m_DlgEffList.SetData( pGLLand );
		}break;

	case DLG_LMLIST:
		{
			SetActivePage ( DLG_LMLIST );
			m_DlgLandMarkList.SetData( pGLLand );
		}break;
	};

	CRanEditLevelView::GetView()->OnMousecontrolNone();
}

void CToolTab::ActiveCrowEdit( std::string strName )
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	SGLNODE<GLMobSchedule*>* pSched = pGLLand->GetMobSchMan()->FindMobSch( strName.c_str() );
	if ( !pSched )	return;

	SetActivePage ( DLG_CROWEDIT );
	m_DlgCrowEdit.SetData( pGLLand, strName.c_str(), true );
}

void CToolTab::ActiveCrowAdd()
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	SetActivePage ( DLG_CROWEDIT );
	m_DlgCrowEdit.SetData( pGLLand, "", false );
}

void CToolTab::SelectCrow( std::string strName )
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	SGLNODE<GLMobSchedule*>* pSched = pGLLand->GetMobSchMan()->FindMobSch( strName.c_str() );
	if ( !pSched )	return;

	SetActivePage ( DLG_CROWLIST );
	m_DlgCrowList.SetData( pGLLand );
	m_DlgCrowList.SelectCrow( strName.c_str() );
}

void CToolTab::ActiveGateEdit( PDXLANDGATE pLandGate )
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	if ( !pLandGate )	return;

	SetActivePage ( DLG_GATEEDIT );
	m_DlgGateEdit.SetData( pGLLand, pLandGate );
}

void CToolTab::ActiveGateAdd()
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	SetActivePage ( DLG_GATEEDIT );
	m_DlgGateEdit.SetData( pGLLand, NULL );
}

void CToolTab::ActiveEffEdit( PLANDEFF pEff )
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	if ( !pEff )	return;

	SetActivePage ( DLG_EFFEDIT );
	m_DlgEffEdit.SetData( pGLLand, pEff );
}

void CToolTab::ActiveEffAdd()
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	SetActivePage ( DLG_EFFEDIT );
	m_DlgEffEdit.SetData( pGLLand, NULL );
}


void CToolTab::ActiveLMEdit( PLANDMARK pLM )
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	if ( !pLM )	return;

	SetActivePage ( DLG_LMEDIT );
	m_DlgLMEdit.SetData( pGLLand, pLM );
}

void CToolTab::ActiveLMAdd()
{
	GLLandMan	*pGLLand = CRanEditLevelView::GetView()->m_pGLLandServer;
	if ( !pGLLand )	return;

	SetActivePage ( DLG_LMEDIT );
	m_DlgLMEdit.SetData( pGLLand, NULL );
}

HBRUSH CToolTab::CtlColor(CDC* pDc, UINT uCtlColor) 
{
	CWnd*    pwndParent;   // Parent window to property-sheet
	CDC*     pdcParent;    // Parent dc
	COLORREF color;        // color on parent dc           

	pwndParent = GetParent();
	ASSERT( pwndParent->IsKindOf( RUNTIME_CLASS( CWnd ) ) ); 
	pdcParent = pwndParent->GetDC();
	color = pdcParent->GetBkColor();    // Get parent color
	pwndParent->ReleaseDC( pdcParent );
	CBrush brush( color );              // Make a brush

	return (HBRUSH)brush;
}

BOOL CToolTab::PreTranslateMessage(MSG* pMsg)
{
	switch ( pMsg->message )
	{
	case WM_KEYDOWN:
		{
			if ( pMsg->wParam == VK_ESCAPE )
			{
			}
		}
		break;
	}
	return CPropertySheet::PreTranslateMessage(pMsg);
}

void CToolTab::ChangeDialogFont(CWnd* pWnd, CFont* pFont, int nFlag)
{
	CRect windowRect;
	TEXTMETRIC tmOld, tmNew;
	CDC * pDC = pWnd->GetDC();
	CFont * pSavedFont = pDC->SelectObject(pWnd->GetFont());
	pDC->GetTextMetrics(&tmOld);
	pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tmNew);
	pDC->SelectObject(pSavedFont);
	pWnd->ReleaseDC(pDC);

	CRect clientRect, newClientRect, newWindowRect;

	pWnd->GetWindowRect(windowRect);
	pWnd->GetClientRect(clientRect);

	double fHeigth = (double)(m_Rect.bottom-m_Rect.top) / clientRect.bottom;
	double fWidth = (double) (m_Rect.right-m_Rect.left) / clientRect.right;

	if (nFlag != CDF_NONE)
	{
		long xDiff = windowRect.Width() - clientRect.Width();
		long yDiff = windowRect.Height() - clientRect.Height();
	
		newClientRect.left = newClientRect.top = 0;
		newClientRect.right = clientRect.right * (LONG)fWidth;
		newClientRect.bottom = clientRect.bottom * (LONG)fHeigth; 

		if (nFlag == CDF_TOPLEFT)
		{
			newWindowRect.left = windowRect.left;
			newWindowRect.top = windowRect.top;
			newWindowRect.right = windowRect.left + newClientRect.right + xDiff;
			newWindowRect.bottom = windowRect.top + newClientRect.bottom + yDiff;
		}
		else if (nFlag == CDF_CENTER) 
		{
			newWindowRect.left = windowRect.left - (newClientRect.right - clientRect.right)/2;
			newWindowRect.top = windowRect.top -(newClientRect.bottom - clientRect.bottom)/2;
			newWindowRect.right = newWindowRect.left + newClientRect.right + xDiff;
			newWindowRect.bottom = newWindowRect.top + newClientRect.bottom + yDiff;
		}
		pWnd->MoveWindow(newWindowRect);
	}

	pWnd->SetFont(pFont);
	CWnd* pChildWnd = pWnd->GetWindow(GW_CHILD);

	while (pChildWnd)
	{
		pChildWnd->SetFont(pFont);
		pChildWnd->GetWindowRect(windowRect);
		CString strClass;
		::GetClassName(pChildWnd->m_hWnd, strClass.GetBufferSetLength(32), 31);
		strClass.MakeUpper();
		if(strClass==_T("COMBOBOX"))
		{
			CRect rect;
			pChildWnd->SendMessage(CB_GETDROPPEDCONTROLRECT,0,(LPARAM) &rect);
			windowRect.right = rect.right;
			windowRect.bottom = rect.bottom;
		}
		pWnd->ScreenToClient(windowRect);
		windowRect.left = windowRect.left * (LONG)fWidth; 
		windowRect.right = windowRect.right * (LONG)fWidth; 
		windowRect.top = windowRect.top * (LONG)fHeigth; 
		windowRect.bottom = windowRect.bottom * (LONG)fHeigth; 
		pChildWnd->MoveWindow(windowRect);
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}
void CToolTab::ClearData()
{
}

