#include "stdafx.h"
#include <vector>
#include "resource.h"
#include "XEffTab.h"
#include "TabCPS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffTab

IMPLEMENT_DYNAMIC(CEffTab, CPropertySheet)

CEffTab::CEffTab(CRect& rect, LOGFONT logfont, CWnd* pParentWnd)
	 : CPropertySheet("jdev", pParentWnd),
	m_bNoTabs(FALSE),
	m_pWndParent(NULL),
	m_iDistanceFromTop(0),
	m_EffList( logfont ),
	m_EffSingle( logfont ),
	m_EffBlur( logfont ),
	m_EffCloneBlur( logfont ),
	m_EffDust( logfont ),
	m_EffShock( logfont ),
	m_EffAttribute( logfont ),
	m_EffArrow( logfont ),
	m_EffSpecular( logfont ),
	m_EffLevel( logfont ),
	m_EffEmit( logfont ),
	m_EffAlpha( logfont ),
	m_EffNeon( logfont ),
	m_EffMark( logfont ),
	m_EffNoAlpha( logfont ),
	m_EffReflection2( logfont ),
	m_EffAmbient( logfont ),
	m_EffDot3( logfont ),
	m_EffMultiTex( logfont ),
	m_EffGhosting( logfont ),
	m_EffSpecular2( logfont ),
	m_EffToon( logfont ),
	m_EffTexDiff( logfont ),
	m_EffParticle( logfont ),
	m_EffBonePos( logfont ),
	m_EffBoneList( logfont ),
	m_EffUserColor( logfont ),
	m_EffNormal( logfont ),
	m_EffLine2Bone( logfont ),
	m_EffAround( logfont ),

	m_pFont ( NULL )
{
	m_pWndParent = pParentWnd;
	m_Rect = rect;

	m_bNoTabs = TRUE;
	m_bStacked = FALSE;

	m_EffList.SetEffTab ( this );
	AddPage ( &m_EffList );
	m_EffSingle.SetEffTab ( this );
	AddPage ( &m_EffSingle );
	m_EffBlur.SetEffTab ( this );
	AddPage ( &m_EffBlur );
	m_EffCloneBlur.SetEffTab ( this );
	AddPage ( &m_EffCloneBlur );
	m_EffDust.SetEffTab ( this );
	AddPage ( &m_EffDust );
	m_EffShock.SetEffTab ( this );
	AddPage ( &m_EffShock );
	m_EffAttribute.SetEffTab ( this );
	AddPage ( &m_EffAttribute );
	m_EffArrow.SetEffTab ( this );
	AddPage ( &m_EffArrow );
	m_EffSpecular.SetEffTab ( this );
	AddPage ( &m_EffSpecular );
	m_EffLevel.SetEffTab ( this );
	AddPage ( &m_EffLevel );
	m_EffEmit.SetEffTab ( this );
	AddPage ( &m_EffEmit );
	m_EffAlpha.SetEffTab ( this );
	AddPage ( &m_EffAlpha );
	m_EffNeon.SetEffTab ( this );
	AddPage ( &m_EffNeon );
	m_EffMark.SetEffTab ( this );
	AddPage ( &m_EffMark );
	m_EffNoAlpha.SetEffTab ( this );
	AddPage ( &m_EffNoAlpha );
	m_EffReflection2.SetEffTab ( this );
	AddPage ( &m_EffReflection2 );
	m_EffAmbient.SetEffTab ( this );
	AddPage ( &m_EffAmbient );
	m_EffDot3.SetEffTab ( this );
	AddPage ( &m_EffDot3 );
	m_EffMultiTex.SetEffTab ( this );
	AddPage ( &m_EffMultiTex );
	m_EffGhosting.SetEffTab ( this );
	AddPage ( &m_EffGhosting );
	m_EffSpecular2.SetEffTab ( this );
	AddPage ( &m_EffSpecular2 );
	m_EffToon.SetEffTab ( this );
	AddPage ( &m_EffToon );
	m_EffTexDiff.SetEffTab ( this );
	AddPage ( &m_EffTexDiff );
	m_EffParticle.SetEffTab ( this );
	AddPage ( &m_EffParticle );
	m_EffBonePos.SetEffTab ( this );
	AddPage ( &m_EffBonePos );
	m_EffBoneList.SetEffTab ( this );
	AddPage ( &m_EffBoneList );
	m_EffUserColor.SetEffTab ( this );
	AddPage ( &m_EffUserColor );
	m_EffNormal.SetEffTab ( this );
	AddPage ( &m_EffNormal );
	m_EffLine2Bone.SetEffTab ( this );
	AddPage ( &m_EffLine2Bone );
	m_EffAround.SetEffTab ( this );
	AddPage ( &m_EffAround );

	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CEffTab::~CEffTab()
{
	SAFE_DELETE( m_pFont );
}

static int module_piButtons[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP };

BOOL CEffTab::OnInitDialog() 
{
	HWND hTabWnd;
	CRect rectTabCtrl;
	ChangeDialogFont( this, m_pFont, XCDF_NONE );

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

BEGIN_MESSAGE_MAP(CEffTab, CPropertySheet)
	//{{AFX_MSG_MAP(CEffTab)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEffTab::ActiveEffList(GLEFFCHAR_VEC m_vecEFFECT )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetPieceData( m_vecEFFECT );
}

void CEffTab::ActiveEffListNormal()
{
	SetActivePage ( EFF_LIST );
}

void CEffTab::ActiveEffSingle( DxEffCharSingle* EffSingle )
{
	SetActivePage ( EFF_SINGLE );
	m_EffSingle.SetEffSingle ( EffSingle );
}
void CEffTab::ActiveEffBlur( DxEffCharBlur* EffBlur )
{
	SetActivePage ( EFF_BLUR );
	m_EffBlur.SetEffBlur ( EffBlur );
}
void CEffTab::ActiveEffCloneBlur( DxEffCharCloneBlur* EffCloneBlur )
{
	SetActivePage ( EFF_CLONEBLUR );
	m_EffCloneBlur.SetEffCloneBlur ( EffCloneBlur );
}
void CEffTab::ActiveEffDust( DxEffCharDust* EffDust )
{
	SetActivePage ( EFF_DUST );
	m_EffDust.SetEffDust ( EffDust );
}
void CEffTab::ActiveEffShock( DxEffCharShock* EffShock )
{
	SetActivePage ( EFF_SHOCK);
	m_EffShock.SetEffShock ( EffShock );
}
void CEffTab::ActiveEffAttribute( DxEffCharAttribute* EffAttribute )
{
	SetActivePage ( EFF_ATTRIBUTE );
	m_EffAttribute.SetEffAttribute ( EffAttribute );
}
void CEffTab::ActiveEffArrow ( DxEffCharArrow* EffArrow )
{
	SetActivePage ( EFF_ARROW );
	m_EffArrow.SetEffArrow ( EffArrow );
}
void CEffTab::ActiveEffSpecular ( DxEffCharSpecular* EffSpecular )
{
	SetActivePage ( EFF_SPECULAR );
	m_EffSpecular.SetEffSpecular ( EffSpecular );
}
void CEffTab::ActiveEffLevel ( DxEffCharLevel* EffLevel )
{
	SetActivePage ( EFF_LEVEL );
	m_EffLevel.SetEffLevel ( EffLevel );
}
void CEffTab::ActiveEffEmit ( DxEffCharEmit* EffEmit )
{
	SetActivePage ( EFF_EMIT );
	m_EffEmit.SetEffEmit ( EffEmit );
}
void CEffTab::ActiveEffAlpha ( DxEffCharAlpha* EffAlpha )
{
	SetActivePage ( EFF_ALPHA );
	m_EffAlpha.SetEffAlpha( EffAlpha );
}
void CEffTab::ActiveEffNeon ( DxEffCharNeon* EffNeon )
{
	SetActivePage ( EFF_NEON );
	m_EffNeon.SetEffNeon( EffNeon );
}
void CEffTab::ActiveEffMark ( DxEffCharMark* EffMark )
{
	SetActivePage ( EFF_MARK );
	m_EffMark.SetEffMark( EffMark );
}
void CEffTab::ActiveEffNoAlpha ( DxEffCharNoAlpha* EffNoAlpha )
{
	SetActivePage ( EFF_NOALPHA );
	m_EffNoAlpha.SetEffNoAlpha( EffNoAlpha );
}
void CEffTab::ActiveEffReflection2 ( DxEffCharReflection2* EffReflection2 )
{
	SetActivePage ( EFF_REFLECTION2 );
	m_EffReflection2.SetEffReflection2( EffReflection2 );
}
void CEffTab::ActiveEffAmbient ( DxEffCharAmbient* EffAmbient )
{
	SetActivePage ( EFF_AMBIENT );
	m_EffAmbient.SetEffAmbient( EffAmbient );
}
void CEffTab::ActiveEffDot3 ( DxEffCharDot3* EffDot3 )
{
	SetActivePage ( EFF_DOT3 );
	m_EffDot3.SetEffDot3( EffDot3 );
}
void CEffTab::ActiveEffMultiTex ( DxEffCharMultiTex* EffMultiTex )
{
	SetActivePage ( EFF_MULTITEX );
	m_EffMultiTex.SetEffMultiTex( EffMultiTex );
}
void CEffTab::ActiveEffGhosting ( DxEffCharGhosting* EffGhosting )
{
	SetActivePage ( EFF_GHOSTING );
	m_EffGhosting.SetEffGhosting( EffGhosting );
}
void CEffTab::ActiveEffSpecular2 ( DxEffCharSpecular2* EffSpecular2 )
{
	SetActivePage ( EFF_SPECULAR2 );
	m_EffSpecular2.SetEffSpecular2( EffSpecular2 );
}
void CEffTab::ActiveEffToon( DxEffCharToon* EffToon )
{
	SetActivePage ( EFF_TOON );
	m_EffToon.SetEffToon( EffToon );
}
void CEffTab::ActiveEffTexDiff( DxEffCharTexDiff* EffTexDiff )
{
	SetActivePage ( EFF_TEXDIFF );
	m_EffTexDiff.SetEffTexDiff( EffTexDiff );
}
void CEffTab::ActiveEffParticle( DxEffCharParticle* EffParticle )
{
	SetActivePage ( EFF_PARTICLE );
	m_EffParticle.SetEffParticle( EffParticle );
}
void CEffTab::ActiveEffBonePos( DxEffCharBonePosEff* EffBonePos )
{
	SetActivePage ( EFF_BONEPOSEFF );
	m_EffBonePos.SetEffBonePos( EffBonePos );
}
void CEffTab::ActiveEffBoneList( DxEffCharBoneListEff* EffBoneList )
{
	SetActivePage ( EFF_BONELISTEFF );
	m_EffBoneList.SetEffBoneList( EffBoneList );
}
void CEffTab::ActiveEffUserColor( DxEffCharUserColor* EffUserColor )
{
	SetActivePage ( EFF_USERCOLOR );
	m_EffUserColor.SetEffUserColor( EffUserColor );
}
void CEffTab::ActiveEffNormal( DxEffCharNormal* EffNormal )
{
	SetActivePage ( EFF_NORMALMAP );
	m_EffNormal.SetEffNormal( EffNormal );
}
void CEffTab::ActiveEffLine2Bone( DxEffCharLine2BoneEff* EffLine2Bone )
{
	SetActivePage ( EFF_LINE2BONE );
	m_EffLine2Bone.SetEffLine2Bone( EffLine2Bone );
}
void CEffTab::ActiveEffAround( DxCharAroundEff* EffAround )
{
	SetActivePage ( EFF_AROUNDEFFECT );
	m_EffAround.SetEffAround( EffAround );
}



void CEffTab::ActiveEffSingleReturn( DxEffCharSingle* EffSingle )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffSingle( EffSingle );
}
void CEffTab::ActiveEffBlurReturn( DxEffCharBlur* EffBlur )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffBlur( EffBlur );
}
void CEffTab::ActiveEffCloneBlurReturn( DxEffCharCloneBlur* EffCloneBlur )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffCloneBlur( EffCloneBlur );
}
void CEffTab::ActiveEffDustReturn( DxEffCharDust* EffDust )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffDust( EffDust );
}
void CEffTab::ActiveEffShockReturn( DxEffCharShock* EffShock )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffShock( EffShock );
}
void CEffTab::ActiveEffAttributeReturn( DxEffCharAttribute* EffAttribute )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffAttribute( EffAttribute );
}
void CEffTab::ActiveEffArrowReturn( DxEffCharArrow* EffArrow )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffArrow( EffArrow );
}
void CEffTab::ActiveEffSpecularReturn( DxEffCharSpecular* EffSpecular )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffSpecular( EffSpecular );
}
void CEffTab::ActiveEffLevelReturn( DxEffCharLevel* EffLevel ,int nSize )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffLevel( EffLevel , nSize);
}
void CEffTab::ActiveEffEmitReturn( DxEffCharEmit* EffEmit )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffEmit( EffEmit );
}
void CEffTab::ActiveEffAlphaReturn( DxEffCharAlpha* EffAlpha )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffAlpha( EffAlpha );
}
void CEffTab::ActiveEffNeonReturn( DxEffCharNeon* EffNeon ,int nSize )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffNeon( EffNeon ,nSize );
}
void CEffTab::ActiveEffMarkReturn( DxEffCharMark* EffMark )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffMark( EffMark );
}
void CEffTab::ActiveEffNoAlphaReturn( DxEffCharNoAlpha* EffNoAlpha )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffNoAlpha( EffNoAlpha );
}
void CEffTab::ActiveEffReflection2Return( DxEffCharReflection2* EffReflection2 ,int nSize)
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffReflection2( EffReflection2,nSize );
}
void CEffTab::ActiveEffAmbientReturn( DxEffCharAmbient* EffAmbient )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffAmbient( EffAmbient );
}
void CEffTab::ActiveEffDot3Return( DxEffCharDot3* EffDot3 )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffDot3( EffDot3 );
}
void CEffTab::ActiveEffMultiTexReturn( DxEffCharMultiTex* EffMultiTex ,int nSize)
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffMultiTex( EffMultiTex ,nSize );
}
void CEffTab::ActiveEffGhostingReturn( DxEffCharGhosting* EffGhosting )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffGhosting( EffGhosting );
}
void CEffTab::ActiveEffSpecular2Return( DxEffCharSpecular2* EffSpecular2 ,int nSize)
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffSpecular2( EffSpecular2 ,nSize);
}
void CEffTab::ActiveEffToonReturn( DxEffCharToon* EffToon )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffToon( EffToon );
}
void CEffTab::ActiveEffTexDiffReturn( DxEffCharTexDiff* EffTexDiff ,int nSize)
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffTexDiff( EffTexDiff ,nSize);
}
void CEffTab::ActiveEffParticleReturn( DxEffCharParticle* EffParticle )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffParticle( EffParticle );
}
void CEffTab::ActiveEffBonePosReturn( DxEffCharBonePosEff* EffBonePos )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffBonePos( EffBonePos );
}
void CEffTab::ActiveEffBoneListReturn( DxEffCharBoneListEff* EffBoneList )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffBoneList( EffBoneList );
}
void CEffTab::ActiveEffUserColorReturn( DxEffCharUserColor* EffUserColor ,int nSize)
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffUserColor( EffUserColor ,nSize);
}
void CEffTab::ActiveEffNormalReturn( DxEffCharNormal* EffNormal )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffNormal( EffNormal );
}
void CEffTab::ActiveEffLine2BoneReturn( DxEffCharLine2BoneEff* EffLine2Bone )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffLine2Bone( EffLine2Bone );
}
void CEffTab::ActiveEffAroundReturn( DxCharAroundEff* EffAround )
{
	SetActivePage ( EFF_LIST );
	m_EffList.SetEffAround( EffAround );
}



HBRUSH CEffTab::CtlColor(CDC* pDc, UINT uCtlColor) 
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

BOOL CEffTab::PreTranslateMessage(MSG* pMsg)
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

void CEffTab::ChangeDialogFont(CWnd* pWnd, CFont* pFont, int nFlag)
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

	if (nFlag != XCDF_NONE)
	{
		long xDiff = windowRect.Width() - clientRect.Width();
		long yDiff = windowRect.Height() - clientRect.Height();
	
		newClientRect.left = newClientRect.top = 0;
		newClientRect.right = clientRect.right * (LONG)fWidth;
		newClientRect.bottom = clientRect.bottom * (LONG)fHeigth; 

		if (nFlag == XCDF_TOPLEFT)
		{
			newWindowRect.left = windowRect.left;
			newWindowRect.top = windowRect.top;
			newWindowRect.right = windowRect.left + newClientRect.right + xDiff;
			newWindowRect.bottom = windowRect.top + newClientRect.bottom + yDiff;
		}
		else if (nFlag == XCDF_CENTER) 
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
void CEffTab::ClearData()
{
}

