#include "stdafx.h"
#include <vector>
#include "resource.h"
#include "RanManagerPetTab.h"
#include "RanManagerComments.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CRanManagerPetTab, CPropertySheet)

CRanManagerPetTab::CRanManagerPetTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd)
	 : CPropertySheet("jdev", pParentWnd),
	 m_bNoTabs(FALSE),
	 m_pWndParent(NULL),
	 m_iDistanceFromTop(0),

	m_PetDefault( logfont ),
	m_PetEdit( logfont ),
	m_PetInven( logfont ),
	m_PetSkill( logfont ),
	m_PetSkillSlot( logfont ),

	 m_pFont ( NULL )
{
	m_pWndParent = pParentWnd;
	m_Rect = rect;

	m_bNoTabs = TRUE;
	m_bStacked = FALSE;

	m_PetDefault.SetToolTab ( this );
	AddPage ( &m_PetDefault );
	m_PetEdit.SetToolTab ( this );
	AddPage ( &m_PetEdit );
	m_PetInven.SetToolTab ( this );
	AddPage ( &m_PetInven );
	m_PetSkill.SetToolTab ( this );
	AddPage ( &m_PetSkill );
	m_PetSkillSlot.SetToolTab ( this );
	AddPage ( &m_PetSkillSlot );

	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerPetTab::~CRanManagerPetTab()
{
	SAFE_DELETE( m_pFont );
}

static int module_piButtons[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP };

BOOL CRanManagerPetTab::OnInitDialog() 
{
	HWND hTabWnd;
	CRect rectTabCtrl;
	ChangeDialogFont( this, m_pFont, BCDF_NONE );

	if( m_Rect.right )	{
		hTabWnd = (HWND)::GetDlgItem(m_hWnd, AFX_IDC_TAB_CONTROL);
		ASSERT(hTabWnd != NULL);
		::GetWindowRect(hTabWnd, &rectTabCtrl); 
		ScreenToClient(rectTabCtrl);

		if( !m_bNoTabs && rectTabCtrl.right > (m_Rect.Width() - 3) )	{
			rectTabCtrl.right = m_Rect.Width() - 3;	}
		rectTabCtrl.bottom = 32; 
		::MoveWindow( hTabWnd, 0, m_iDistanceFromTop, rectTabCtrl.Width(), rectTabCtrl.bottom, TRUE );
		BOOL bResult = (BOOL)Default(); 

		if( m_bNoTabs )	{
			::ShowWindow(hTabWnd, SW_HIDE);
			::EnableWindow(hTabWnd, FALSE);	}

		if (!m_bStacked)	{
			hTabWnd = (HWND)SendMessage(PSM_GETTABCONTROL);
			if (hTabWnd != NULL)	{
				CWnd::ModifyStyle(hTabWnd, TCS_MULTILINE, TCS_SINGLELINE, 0);	}	}

		for (int i = 0; i < 4; i++)	{
			HWND hWnd = ::GetDlgItem(m_hWnd, module_piButtons[i]);
			if (hWnd != NULL)	{
				::ShowWindow(hWnd, SW_HIDE);
				::EnableWindow(hWnd, FALSE);	}	}

		MoveWindow( m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom /*- cyDiff*/ );
		return bResult;
	}	return CPropertySheet::OnInitDialog();
}

BEGIN_MESSAGE_MAP(CRanManagerPetTab, CPropertySheet)
	//{{AFX_MSG_MAP(CRanManagerPetTab)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CRanManagerPetTab::ActivePage(int nPage ,int nPet )
{
	switch (nPage)
	{
	case PETPAGE_MAIN:	
		{
			SetActivePage ( PETPAGE_MAIN );
			m_PetDefault.SetPet(nPet);
		}break;
	case PETPAGE_EDIT:	
		{
			SetActivePage ( PETPAGE_EDIT );
			m_PetEdit.SetPet(nPet);
		}break;
	case PETPAGE_INVEN:	
		{
			SetActivePage ( PETPAGE_INVEN );
			m_PetInven.SetPet(nPet);
		}break;
	case PETPAGE_SKILL:	
		{
			SetActivePage ( PETPAGE_SKILL );
			m_PetSkill.SetPet(nPet);
		}break;
	case PETPAGE_SKILLSLOT:	
		{
			SetActivePage ( PETPAGE_SKILLSLOT );
			m_PetSkillSlot.SetPet(nPet);
		}break;
	};
}

HBRUSH CRanManagerPetTab::CtlColor(CDC* pDc, UINT uCtlColor) 
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

BOOL CRanManagerPetTab::PreTranslateMessage(MSG* pMsg)
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

void CRanManagerPetTab::ChangeDialogFont(CWnd* pWnd, CFont* pFont, int nFlag)
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

	if (nFlag != BCDF_NONE)	{
		long xDiff = windowRect.Width() - clientRect.Width();
		long yDiff = windowRect.Height() - clientRect.Height();
	
		newClientRect.left = newClientRect.top = 0;
		newClientRect.right = clientRect.right * (LONG)fWidth;
		newClientRect.bottom = clientRect.bottom * (LONG)fHeigth; 

		if (nFlag == BCDF_TOPLEFT)	{
			newWindowRect.left = windowRect.left;
			newWindowRect.top = windowRect.top;
			newWindowRect.right = windowRect.left + newClientRect.right + xDiff;
			newWindowRect.bottom = windowRect.top + newClientRect.bottom + yDiff;	}
		else if (nFlag == BCDF_CENTER) {
			newWindowRect.left = windowRect.left - (newClientRect.right - clientRect.right)/2;
			newWindowRect.top = windowRect.top -(newClientRect.bottom - clientRect.bottom)/2;
			newWindowRect.right = newWindowRect.left + newClientRect.right + xDiff;
			newWindowRect.bottom = newWindowRect.top + newClientRect.bottom + yDiff;	}
		pWnd->MoveWindow(newWindowRect);	}

	pWnd->SetFont(pFont);
	CWnd* pChildWnd = pWnd->GetWindow(GW_CHILD);

	while (pChildWnd)	{
		pChildWnd->SetFont(pFont);
		pChildWnd->GetWindowRect(windowRect);
		CString strClass;
		::GetClassName(pChildWnd->m_hWnd, strClass.GetBufferSetLength(32), 31);
		strClass.MakeUpper();
		if(strClass==_T("COMBOBOX"))	{
			CRect rect;
			pChildWnd->SendMessage(CB_GETDROPPEDCONTROLRECT,0,(LPARAM) &rect);
			windowRect.right = rect.right;
			windowRect.bottom = rect.bottom;	}
		pWnd->ScreenToClient(windowRect);
		windowRect.left = windowRect.left * (LONG)fWidth; 
		windowRect.right = windowRect.right * (LONG)fWidth; 
		windowRect.top = windowRect.top * (LONG)fHeigth; 
		windowRect.bottom = windowRect.bottom * (LONG)fHeigth; 
		pChildWnd->MoveWindow(windowRect);
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);	}
}
void CRanManagerPetTab::ClearData()
{
}

