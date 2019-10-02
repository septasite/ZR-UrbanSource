#include "stdafx.h"
#include "RanEditLevelView.h"
#include "RanEditLevel.h"

#include "GLOGIC.h"
#include "DxEffectMan.h"
#include "RANPARAM.h"
#include "DxResponseMan.h"
#include "DxViewPort.h"
#include "DxGlowMan.h"
#include "DxShadowMap.h"
#include "DxPostProcess.h"
#include "DxInputDevice.h"
#include "profile.h"
#include "dxparamset.h"
#include "SUBPATH.h"
#include "GLChar.h"
#include "DxServerInstance.h"
#include "DxGlobalStage.h"
#include "RanEditLevelDoc.h"
#include "D3DFont.h"
#include "../EngineUILib/GUInterface/Cursor.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../RanClientUILib/Interface/GameTextControl.h"
#include "DxSkinMeshMan.h"
#include "DxDynamicVB.h"
#include "DxCubeMap.h"
#include "MainFrm.h"
#include "DxEnvironment.h"
#include "DxEffGroupPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CRanEditLevelView::OnInitialUpdate()
{
	CRanEditLevelApp *pApp = (CRanEditLevelApp *) AfxGetApp();

	StringCchCopy ( szAppPath, MAX_PATH, pApp->m_szAppPath );

	char szFullPath[MAX_PATH] = {0};
	strcpy ( szFullPath, szAppPath );
	strcat ( szFullPath, SUBPATH::GLOGIC_FILE );
	GLOGIC::SetPath ( szFullPath );

	BOOL bOK = RANPARAM::LOAD ( szAppPath );
	DXPARAMSET::INIT ();

	char szEditorPath[MAX_PATH] = {0};
	strcpy ( szEditorPath, szAppPath );
	strcat ( szEditorPath, SUBPATH::OBJ_FILE_EDIT );
	
	m_DxEditBox.SetPath( szEditorPath );
	m_DxEditMat.SetParam( szEditorPath, NULL );

	if (!bOK )
	{
		MessageBox("Unable to Load PARAM.ini!","Error",MB_OK);
	}
	else
	{
		CD3DApplication::SetScreen ( RANPARAM::dwScrWidth, RANPARAM::dwScrHeight, RANPARAM::emScrFormat, RANPARAM::uScrRefreshHz, TRUE );
		if ( FAILED( CD3DApplication::Create ( m_hWnd, m_hWnd, AfxGetInstanceHandle() ) ) )		return;
		m_bCreated = TRUE;
	}

	__super::OnInitialUpdate();
}

void CRanEditLevelView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CRanEditLevelApp *pApp = (CRanEditLevelApp*) AfxGetApp();
	pApp->SetActive ( bActivate );
	CRanEditLevelView::SetActive ( bActivate );

	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CRanEditLevelView::PostNcDestroy()
{
	CD3DApplication::Cleanup3DEnvironment();

	::SetCursor ( NULL );
	::DestroyCursor ( m_hCursorDefault );

	__super::PostNcDestroy();
}

void CRanEditLevelView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if ( m_bCreated )
	{
		ReSizeWindow(cx,cy);

		if ( m_pd3dDevice )
		{
			InvalidateDeviceObjects();
			RestoreDeviceObjects();
		}
	}
}

void CRanEditLevelView::SetActive ( BOOL bActive )
{
	DxInputDevice::GetInstance().OnActivate ( bActive );
}

BOOL CRanEditLevelView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR hCursl = CCursor::GetInstance().GetCurCursor();
	if ( !hCursl )
	{
		if ( !m_hCursorDefault )		m_hCursorDefault = LoadCursor ( NULL, IDC_ARROW );
		hCursl = m_hCursorDefault;
	}

	if ( hCursl )	::SetCursor ( hCursl );

	return TRUE;
}

HRESULT CRanEditLevelView::OneTimeSceneInit()
{
	HRESULT hr = S_OK;

	DxResponseMan::GetInstance().OneTimeSceneInit ( szAppPath, this, RANPARAM::strFontType, RANPARAM::dwLangSet, RANPARAM::strGDIFont );

	GMTOOL::Create( szAppPath );

	char szFullPath[MAX_PATH] = {0};

	StringCchCopy ( szFullPath, MAX_PATH, szAppPath );
	StringCchCat ( szFullPath, MAX_PATH, SUBPATH::MAP_FILE );
	GLMapAxisInfo::SetPath( szFullPath );

	CCursor::GetInstance().SetGameCursor ( RANPARAM::bGameCursor );

	return S_OK;
}

HRESULT CRanEditLevelView::RenderText()
{
	if (!bDebugInfo )	return S_OK;

	D3DCOLOR fontColor        = D3DCOLOR_ARGB(255,255,0,0);
	D3DCOLOR fontWarningColor = D3DCOLOR_ARGB(255,255,0,0);
	TCHAR szMsg[MAX_PATH] = TEXT("");

	CD3DFontPar* pD3dFont = DxFontMan::GetInstance().FindFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );
	if ( !pD3dFont )	return S_OK;

	FLOAT fNextLine = 40.0f; 

	lstrcpy( szMsg, m_strDeviceStats );
	fNextLine -= 20.0f;
	pD3dFont->DrawText( 2, fNextLine, fontColor, szMsg );

	lstrcpy( szMsg, m_strFrameStats );
	fNextLine -= 20.0f;
	pD3dFont->DrawText( 2, fNextLine, fontColor, szMsg );

	CDebugSet::Render ();

	return S_OK;
}