#include "stdafx.h"
#include <vector>
#include "resource.h"
#include "ToolTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString g_strEditSheet[EDITSHEET] =
{
	"Default",
	"ABF Editor",
	"VCF Editor",
	"CHF Editor",
	"ABL Editor",
	"File Converter",
	"Credits",
	"MMP Creator",
	"File Cryption"
};

/////////////////////////////////////////////////////////////////////////////
// CToolTab

IMPLEMENT_DYNAMIC(CToolTab, CPropertySheet)

CToolTab::CToolTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd)
	 : CPropertySheet(IDS_SHEET_CAPTION, pParentWnd),
	 m_bNoTabs(FALSE),
	 m_pWndParent(NULL),
	 m_iDistanceFromTop(0),
	 m_TabDEF( logfont ),
	 m_TabABF( logfont ),
	 m_TabVCF( logfont ),
	 m_TabCHF( logfont ),
	 m_TabCFG( logfont ),
	 m_TabABL( logfont ),
	 m_TabCNV( logfont ),
	 m_TabCRD( logfont ),
	 m_TabCPS( logfont ),
	 m_TabMMP( logfont ),
	 m_TabCRY( logfont ),


	 m_pFont ( NULL )
{
	m_pWndParent = pParentWnd;
	m_Rect = rect;

	m_bNoTabs = TRUE;
	m_bStacked = FALSE;

	m_TabDEF.SetToolTab ( this );
	AddPage ( &m_TabDEF );

	m_TabABF.SetToolTab ( this );
	AddPage ( &m_TabABF );

	m_TabVCF.SetToolTab ( this );
	AddPage ( &m_TabVCF );

	m_TabCHF.SetToolTab ( this );
	AddPage ( &m_TabCHF );

	m_TabCFG.SetToolTab ( this );
	AddPage ( &m_TabCFG );

	m_TabABL.SetToolTab ( this );
	AddPage ( &m_TabABL );

	m_TabCNV.SetToolTab ( this );
	AddPage ( &m_TabCNV );

	m_TabCRD.SetToolTab ( this );
	AddPage ( &m_TabCRD );

	m_TabCPS.SetToolTab ( this );
	AddPage ( &m_TabCPS );

	m_TabMMP.SetToolTab ( this );
	AddPage ( &m_TabMMP );

	m_TabCRY.SetToolTab ( this );
	AddPage ( &m_TabCRY );

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

void CToolTab::ActivateTab(int nPage ,  bool bSave )
{	
	/*TYPE_DEF = 0,
	TYPE_CHF = 1,
	TYPE_ABF = 2,
	TYPE_VCF = 3,
	TYPE_CPS = 4,
	TYPE_APS = 5,
	TYPE_VPS = 6,
	TYPE_ABL = 7,
	TYPE_CFG = 8,
	TYPE_CNV = 9,*/

	switch( nPage )
	{
	case 0:
		{
			SetActivePage ( TAB_DEF );	
			AddHistory( "Open Welcome Page"  );
		}break;
	case 1:	
		{
			SetActivePage ( TAB_CHF );	
			AddHistory( "Open CHF Editor"  );
			if (!bSave)	
			{
				m_TabCHF.Reset();	
				AddHistory( "Save Session Disabled CHF Editor Contents Reset"  );
			}
		}break;
	case 2:	
		{
			SetActivePage ( TAB_ABF );	
			AddHistory( "Open ABF Editor"  );
			if (!bSave)	
			{
				m_TabABF.Reset();
				AddHistory( "Save Session Disabled ABF Editor Contents Reset"  );
			}
		}break;
	case 3:
		{
			SetActivePage ( TAB_VCF );	
			AddHistory( "Open VCF Editor"  );
			if (!bSave)	
			{
				m_TabVCF.Reset();
				AddHistory( "Save Session Disabled VCF Editor Contents Reset"  );
			}
		}break;
	case 4:	
		{
			SetActivePage ( TAB_CPS );
			AddHistory( "Open CPS-APS-VPS Editor"  );
			if (!bSave)	
			{
				m_TabCPS.Reset();	
				AddHistory( "Save Session Disabled CPS-APS-VPS Editor Contents Reset"  );
			}
		}break;
	case 5:
		{
			SetActivePage ( TAB_ABL );	
			AddHistory( "Open ABL Editor"  );
			if (!bSave)
			{
				m_TabABL.Reset();	
				AddHistory( "Save Session Disabled ABL Editor Contents Reset"  );
			}
		}break;
	case 6:
		{
			SetActivePage ( TAB_CFG );	
			AddHistory( "Open CFG Editor"  );
			if (!bSave)	
			{
				m_TabCFG.Reset();	
				AddHistory( "Save Session Disabled CFG Editor Contents Reset"  );
			}
		}break;
	case 7:	
		{
			SetActivePage ( TAB_CNV );	
			AddHistory( "Open File Converters"  );
			if (!bSave)	
			{
				m_TabCNV.Reset();	
				AddHistory( "Save Session Disabled File Converter Contents Reset"  );
			}
		}break;
	case 8:	
		{
			SetActivePage ( TAB_MMP );
			AddHistory( "Open MMP Creator"  );
			if (!bSave)	
			{
				m_TabMMP.Reset();	
				AddHistory( "Save Session Disabled MMP Creator Contents Reset"  );
			}
		}break;
	case 9:	
		{
			SetActivePage ( TAB_CRY );
			AddHistory( "Open File Cryption"  );
			if (!bSave)	
			{
				m_TabCRY.Reset();	
				AddHistory( "Save Session Disabled File Cryption Contents Reset"  );
			}
		}break;
	case 30:	
		{
			SetActivePage ( TAB_CRD );	
			AddHistory( "Open Credits"  );
		}break;
	};
}

void CToolTab::AddHistory( const char* szInfo )
{
	CString strTemp ="";
	std::string strTIME = CDebugSet::GetCurTime ();
	strTemp.Format("%s---%s" ,strTIME.c_str(),szInfo);
	m_TabDEF.AddEditString (strTemp.GetString() );
	strTIME.clear();
	strTemp.Empty();
}

void CToolTab::AddHistoryOpen( const char* szSender ,const char* szInfo )
{
	CString strTemp ="";
	std::string strTIME = CDebugSet::GetCurTime ();
	strTemp.Format("%s---%s-Open File: %s" ,strTIME.c_str(),szSender,szInfo);
	m_TabDEF.AddEditString (strTemp.GetString() );
	strTIME.clear();
	strTemp.Empty();
}

void CToolTab::AddHistorySave( const char* szSender ,const char* szInfo )
{
	CString strTemp ="";
	std::string strTIME = CDebugSet::GetCurTime ();
	strTemp.Format("%s---%s-Save File: %s" ,strTIME.c_str(),szSender,szInfo);
	m_TabDEF.AddEditString (strTemp.GetString()  );
	strTIME.clear();
	strTemp.Empty();
}

void CToolTab::AddHistoryOpenFail( const char* szSender ,const char* szInfo )
{
	CString strTemp ="";
	std::string strTIME = CDebugSet::GetCurTime ();
	strTemp.Format("%s---%s-Open File Failure: %s" ,strTIME.c_str(),szSender,szInfo);
	m_TabDEF.AddEditString (strTemp.GetString() );
	strTIME.clear();
	strTemp.Empty();
}

void CToolTab::AddHistorySaveFail( const char* szSender ,const char* szInfo )
{
	CString strTemp ="";
	std::string strTIME = CDebugSet::GetCurTime ();
	strTemp.Format("%s---%s-Save File Failure: %s" ,strTIME.c_str(),szSender,szInfo);
	m_TabDEF.AddEditString (strTemp.GetString()  );
	strTIME.clear();
	strTemp.Empty();
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

