#include "stdafx.h"
#include "RanViewer.h"
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
#include "RanDoc.h"
#include "RanView.h"
#include "D3DFont.h"
#include "../EngineUILib/GUInterface/Cursor.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../RanClientUILib/Interface/GameTextControl.h"
#include ".\Ranview.h"
#include "DxSkinMeshMan.h"
#include "DxDynamicVB.h"
#include "DxCubeMap.h"
#include "MainFrm.h"
#include "ToolComment.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int g_nITEMLEVEL;
extern BOOL g_bCHAR_EDIT_RUN;
extern BOOL g_bCHAR_VIEW_RUN;

void CRanView::OnInitialUpdate()
{
	CRanApp *pApp = (CRanApp *) AfxGetApp();

	char szFullPath[MAX_PATH] = {0};
	strcpy ( szFullPath, szAppPath );
	strcat ( szFullPath, SUBPATH::GLOGIC_FILE );
	GLOGIC::SetPath ( szFullPath );

	StringCchCopy ( szAppPath, MAX_PATH, pApp->m_szAppPath );

	BOOL bOK = RANPARAM::LOAD ( szAppPath );
	DXPARAMSET::INIT ();

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

void CRanView::PostNcDestroy()
{
	CD3DApplication::Cleanup3DEnvironment();

	::SetCursor ( NULL );
	::DestroyCursor ( m_hCursorDefault );

	__super::PostNcDestroy();
}

BOOL CRanView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
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

HRESULT CRanView::ConfirmDevice ( D3DCAPSQ* pCaps, DWORD dwBehavior, D3DFORMAT Format )
{
	if ( dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING )
		return E_FAIL;

	return S_OK;
}

HRESULT CRanView::OneTimeSceneInit()
{
	HRESULT hr = S_OK;

	DxResponseMan::GetInstance().OneTimeSceneInit ( szAppPath, this,
		RANPARAM::strFontType, RANPARAM::dwLangSet, RANPARAM::strGDIFont );

	GMTOOL::Create( szAppPath );

	return S_OK;
}

HRESULT CRanView::CreateObjects()
{
	{ 
		DxFontMan::GetInstance().InitDeviceObjects ( m_pd3dDevice );
		CD3DFontPar* pD3dFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );
		CD3DFontPar* pD3dFont10 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, _DEFAULT_FONT_FLAG );

		CDebugSet::InitDeviceObjects( pD3dFont10 );
	}

	HRESULT hr = S_OK;

	hr = InitDeviceObjects();
    if( FAILED(hr) )	return hr;

	hr = RestoreDeviceObjects();	
    if( FAILED(hr) )	return hr;

	return hr;
}

HRESULT CRanView::InitDeviceObjects()
{
	HRESULT hr = S_OK;

	DxViewPort::GetInstance().InitDeviceObjects ( m_pd3dDevice, m_hWnd );
	DxResponseMan::GetInstance().InitDeviceObjects ( m_pd3dDevice );

	DXLIGHT sDirectional;
	sDirectional.SetDefault();
	sDirectional.m_Light.Diffuse = D3DXCOLOR(1.1f,1.1f,1.1f,1);
	sDirectional.m_Light.Ambient = D3DXCOLOR(1.1f,1.1f,1.1f,1);
	DxLightMan::SetDefDirect ( sDirectional );

	TextureManager::EnableTexTypeDEBUG();

	hr = m_pd3dDevice->GetDeviceCaps ( &m_d3dCaps );
	DxBoneCollector::GetInstance().PreLoad ( _PRELOAD_BONE, m_pd3dDevice );
	DxSkinAniMan::GetInstance().PreLoad ( _PRELOAD_ANI, m_pd3dDevice );
	DxSkinMeshMan::GetInstance().PreLoad( _PRELOAD_SKIN, m_pd3dDevice, FALSE );

	WORD wWidth = 960; 
	WORD wHeight = 720;

	LPDIRECT3DSURFACEQ pBackBuffer=NULL;
	m_pd3dDevice->GetBackBuffer ( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );

	if ( pBackBuffer )
	{
		pBackBuffer->GetDesc( &m_d3dsdBackBuffer );
		pBackBuffer->Release();

		wWidth = static_cast<WORD> ( m_d3dsdBackBuffer.Width );
		wHeight = static_cast<WORD> ( m_d3dsdBackBuffer.Height );
	}

	m_vPos.x = 0 ;
	m_vPos.y = 0 ;
	m_vPos.z = 0 ;

	DxViewPort::GetInstance().SetCameraType ((CAMERA_TYPE)2);

	D3DXVECTOR3 vFromPt		= D3DXVECTOR3( 0.0f, 70.0f, -70.0f );
	D3DXVECTOR3 vLookatPt	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec		= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	DxViewPort::GetInstance().SetViewTrans ( vFromPt, vLookatPt, vUpVec );

	D3DXVECTOR3 vCamera = m_vPos;
	vCamera.y += 10.0f;
	DxViewPort::GetInstance().CameraJump ( vCamera );

	CCursor::GetInstance().InitDeviceObjects ();
	DxResponseMan::GetInstance().SetRenderState ();

	return S_OK;
}

HRESULT CRanView::RestoreDeviceObjects()
{
	HRESULT hr=S_OK;

	DxResponseMan::GetInstance().RestoreDeviceObjects ();
	DxGlowMan::GetInstance().SetProjectActiveON();
	DxPostProcess::GetInstance().SetProjectActiveON();

	DXPARAMSET::INIT ();

	if ( !m_pd3dDevice )	return S_FALSE;

	if ( m_d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGVERTEX )
	{
		m_pd3dDevice->SetRenderState ( D3DRS_FOGENABLE,		TRUE );
	}

	float fFogStart=720.0f, fFogEnd=790.0f, fFongDensity=0.0f;

	m_pd3dDevice->SetRenderState ( D3DRS_FOGSTART,		*((DWORD *)(&fFogStart)) );
	m_pd3dDevice->SetRenderState ( D3DRS_FOGEND,		*((DWORD *)(&fFogEnd)) );
	m_pd3dDevice->SetRenderState ( D3DRS_FOGDENSITY,	*((DWORD *)(&fFongDensity)) );

	m_pd3dDevice->SetRenderState( D3DRS_FOGVERTEXMODE,	D3DFOG_LINEAR );
	m_pd3dDevice->SetRenderState ( D3DRS_FOGTABLEMODE,	D3DFOG_NONE );

	if ( m_d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGRANGE )
	{
		m_pd3dDevice->SetRenderState ( D3DRS_RANGEFOGENABLE,	TRUE );
	}

	LPDIRECT3DSURFACEQ pBackBuffer;
	m_pd3dDevice->GetBackBuffer ( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );

    pBackBuffer->GetDesc( &m_d3dsdBackBuffer );
    pBackBuffer->Release();

	DxViewPort::GetInstance().SetProjection ( D3DX_PI/4, (float)m_d3dsdBackBuffer.Width, 
		(float)m_d3dsdBackBuffer.Height, 1.0f, 5000.0f );
	
	hr = DxViewPort::GetInstance().SetViewPort ();
	if ( FAILED(hr) )	return hr;

	PROFILE_INIT();

	return S_OK;
}

HRESULT CRanView::FrameMove3DEnvironment ()
{
	HRESULT hr=S_OK;

	PROFILE_BLOCKSTART();

	if ( m_pd3dDevice )
	{
		hr = CD3DApplication::FrameMove3DEnvironment ();
		if ( FAILED(hr) )	return hr;
	}

	PROFILE_BLOCKEND();
	PROFILE_DUMPOUTPUT();

	return S_OK;
}

HRESULT CRanView::Render3DEnvironment ()
{
	HRESULT hr=S_OK;

	PROFILE_BLOCKSTART();

	if ( m_pd3dDevice )
	{
		hr = CD3DApplication::Render3DEnvironment ();
		if ( FAILED(hr) )	return hr;
	}

	PROFILE_BLOCKEND();
	PROFILE_DUMPOUTPUT();

	return S_OK;
}

HRESULT CRanView::FrameMove()
{
	PROFILE_BEGIN("FrameMove");

	CheckControlfp();
	DxResponseMan::GetInstance().FrameMove( m_fTime, m_fElapsedTime, m_bDefWin );
	DxViewPort::GetInstance().FrameMove ( m_fTime, m_fElapsedTime );
	DxTaregetEffect::GetInstance().FrameMove( m_fTime, m_fElapsedTime );

	DxLightMan::GetInstance()->EnableLighting( true );

	m_vDir = DxViewPort::GetInstance().GetFromPt() - DxViewPort::GetInstance().GetLookatPt();

	if ( m_pSkinChar ) 
	{
		m_pSkinChar->FrameMove ( m_fTime, m_fElapsedTime, TRUE, FALSE, bSAttack );
		m_pSkinChar->SetPosition ( m_vPos );
		
		if ( m_AniMain == AN_ATTACK )
		{
			UpdateAnimation ();
			m_pSkinChar->SELECTANI ( m_AniMain, m_AniSub ,NULL , dwAniSelect );
		}
		else
		{
			m_pSkinChar->SELECTANI ( m_AniMain, m_AniSub );
		}
	
		for ( int i=0; i<PIECE_SIZE; ++i )
		{
			if ( m_pSkinChar->m_pSkinCharPiece[i] ) 
			{
				m_pSkinChar->m_pSkinCharPiece[i]->SELECTANI ( m_ABLAniMain,m_ABLAniSub );
			}
		}

		if ( m_pSkinChar->m_pSkinVehicle ) 
		{
			m_pSkinChar->m_pSkinVehicle->SELECTANI ( m_VCFAniMain,m_VCFAniSub );
		}
	}

	D3DXMATRIX matTrans ;
	D3DXMatrixTranslation ( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	m_matTrans = matTrans;

	m_vMax = m_vPos + m_vMaxOrg;
	m_vMin = m_vPos + m_vMinOrg;

	m_vMousePos.x = (float)DxInputDevice::GetInstance().GetMouseLocateX();
	m_vMousePos.y = (float)DxInputDevice::GetInstance().GetMouseLocateY();
	m_vMousePos.z = (float)DxInputDevice::GetInstance().GetMouseLocateZ();

	PROFILE_END("FrameMove");

	return S_OK;
}

HRESULT CRanView::Render()
{
	PROFILE_BEGIN("Render");

	D3DCOLOR colorClear = D3DCOLOR_ARGB(255,100,100,100);
	DxFogMan::GetInstance().RenderFogSB ( m_pd3dDevice );

	HRESULT hr = m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
						colorClear, 1.0f, 0L );

	if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
	{
		DxGlowMan::GetInstance().RenderTex ( m_pd3dDevice );
		DxLightMan::GetInstance()->Render ( m_pd3dDevice );
		DXLIGHT &Light = *DxLightMan::GetInstance()->GetDirectLight ();
		m_pd3dDevice->SetVertexShaderConstantF ( VSC_LIGHTDIRECT, (float*)&Light.m_Light.Direction, 1 );
		m_pd3dDevice->SetVertexShaderConstantF ( VSC_LIGHTDIFFUSE, (float*)&Light.m_Light.Diffuse, 1 );
		m_pd3dDevice->SetVertexShaderConstantF ( VSC_LIGHTAMBIENT, (float*)&Light.m_Light.Ambient, 1 );
		D3DXVECTOR3 &vFromPt = DxViewPort::GetInstance().GetFromPt ();
		m_pd3dDevice->SetVertexShaderConstantF ( VSC_CAMERAPOSITION, (float*)&vFromPt, 1 );
		
		D3DLIGHTQ	pLight;
		D3DXVECTOR4	vPointPos;
		D3DXVECTOR3	vPointDiff;
		for ( int i=0; i<7; i++ )
		{
			if ( DxLightMan::GetInstance()->GetClosedLight(i+1) )
			{
				pLight = DxLightMan::GetInstance()->GetClosedLight(i+1)->m_Light;
				vPointDiff = D3DXVECTOR3 ( pLight.Diffuse.r, pLight.Diffuse.g, pLight.Diffuse.b );
				vPointPos.x = pLight.Position.x;
				vPointPos.y = pLight.Position.y;
				vPointPos.z = pLight.Position.z;
				vPointPos.w = pLight.Range;
			}
			else
			{
				vPointPos = D3DXVECTOR4 ( 0.f, 0.f, 0.f, 0.1f );
				vPointDiff = D3DXVECTOR3 ( 0.f, 0.f, 0.f );
			}
			m_pd3dDevice->SetVertexShaderConstantF (i*2+VSC_PLIGHTPOS01, (float*)&vPointPos, 1);
			m_pd3dDevice->SetVertexShaderConstantF (i*2+VSC_PLIGHTDIFF01, (float*)&vPointDiff, 1);
		}

		D3DXMATRIX matView = DxViewPort::GetInstance().GetMatView();
		D3DXMATRIX matProj = DxViewPort::GetInstance().GetMatProj();

		m_pd3dDevice->SetVertexShaderConstantF ( VSC_SKIN_DEFAULT, (float*)&D3DXVECTOR4 (1.f, 0.5f, 0.f, 765.01f), 1 );

		D3DXVECTOR3	vLightVector = DxLightMan::GetInstance()->GetDirectLight()->m_Light.Direction;
		D3DXVec3TransformNormal ( &vLightVector, &vLightVector, &matView );
		D3DXVec3Normalize ( &vLightVector, &vLightVector);
		vLightVector = -vLightVector;
		m_pd3dDevice->SetVertexShaderConstantF ( VSC_LIGHTDIRECT_VIEW, (float*)&vLightVector, 1 );

		D3DXMatrixTranspose( &matView, &matView );
		D3DXMatrixTranspose( &matProj, &matProj );

		D3DXMATRIX matIdentity;
		D3DXMatrixIdentity( &matIdentity );
		m_pd3dDevice->SetTransform( D3DTS_WORLD,  &matIdentity );

		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,	D3DTOP_MODULATE );	

		if ( m_d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGVERTEX )		
		m_pd3dDevice->SetRenderState ( D3DRS_FOGENABLE, FALSE );

		CLIPVOLUME &CV = DxViewPort::GetInstance().GetClipVolume ();

		if ( m_d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGVERTEX )	
		{
			m_pd3dDevice->SetRenderState ( D3DRS_FOGENABLE, FALSE );
		}

		if ( m_pSkinChar )
		{
			if ( m_pSkinChar->m_pSkinVehicle )
			{
				m_pSkinChar->RenderVehicle( m_pd3dDevice, m_matTrans );
				DxBoneTrans *pBoneCur = NULL;
				pBoneCur = m_pSkinChar->m_pSkinVehicle->GetSkeleton()->FindBone( m_pSkinChar->m_pSkinVehicle->m_strChar_Font.c_str() );
				if ( pBoneCur )
				{
					D3DXVECTOR3			vRotation_Font, vTransform_Font;

					vRotation_Font = m_pSkinChar->m_pSkinVehicle->m_vRotation_Font;
					vTransform_Font = m_pSkinChar->m_pSkinVehicle->m_vTransform_Font;

					D3DXMATRIXA16	matLocalRot, matScale, matRot;
					matRot = pBoneCur->matCombined;
					D3DXMatrixIdentity( &matScale );

					D3DXMatrixRotationYawPitchRoll( &matScale, vRotation_Font.x, vRotation_Font.y, vRotation_Font.z );

					D3DXMatrixMultiply( &matLocalRot, &matScale, &matRot );

					D3DXVECTOR3	vVelocity;
					D3DXVec3TransformNormal ( &vVelocity, &vTransform_Font, &matRot );
					matLocalRot._41 += vVelocity.x;
					matLocalRot._42 += vVelocity.y;
					matLocalRot._43 += vVelocity.z;

					m_pSkinChar->Render ( m_pd3dDevice, matLocalRot );
				}
			}
			else
			{
				m_pSkinChar->Render( m_pd3dDevice, m_matTrans );
			}

			DxShadowMap::GetInstance().RenderShadowCharMob ( m_pSkinChar, m_matTrans, m_pd3dDevice );

			STARGETID sTargetID (CROW_PC,0,m_vPos);
	
			D3DXMATRIX matTrans_a;
			D3DXMatrixTranslation ( &matTrans_a, m_vPos.x, m_vPos.y, m_vPos.z );
			matTrans_a._42 += m_pSkinChar->m_fHeight;
			DxTaregetEffect::GetInstance().NewEffGroup ( GLCONST_CHAR::strARROW_EFFECT_NPC.c_str() , matTrans_a, &sTargetID );
	
		}

		DxTaregetEffect::GetInstance().Render ( m_pd3dDevice );
		OPTMManager::GetInstance().Render( m_pd3dDevice );

		DxCubeMap::GetInstance().Render ( m_pd3dDevice );
		DxGlowMan::GetInstance().Render ( m_pd3dDevice );
		DxGlowMan::GetInstance().RenderBURN( m_pd3dDevice );
		DxPostProcess::GetInstance().Render( m_pd3dDevice );

		g_nITEMLEVEL = nGrind;


		RenderText();
		CCursor::GetInstance().Render ( m_pd3dDevice, DxInputDevice::GetInstance().GetMouseLocateX(), DxInputDevice::GetInstance().GetMouseLocateY() );

		if( DxInputDevice::GetInstance().GetKeyState(DIK_W) & DXKEY_DOWN )	EditMatrix ( 0 );
		if( DxInputDevice::GetInstance().GetKeyState(DIK_S) & DXKEY_DOWN )	EditMatrix ( 1 );
		if( DxInputDevice::GetInstance().GetKeyState(DIK_A) & DXKEY_DOWN )	EditMatrix ( 2 );
		if( DxInputDevice::GetInstance().GetKeyState(DIK_D) & DXKEY_DOWN )	EditMatrix ( 3 );
		if( DxInputDevice::GetInstance().GetKeyState(DIK_Q) & DXKEY_DOWN )	EditMatrix ( 4 );
		if( DxInputDevice::GetInstance().GetKeyState(DIK_E) & DXKEY_DOWN )	EditMatrix ( 5 );

		m_pd3dDevice->EndScene();

	}

	PROFILE_END("Render");
	return S_OK;
}

void CRanView::UpdateAnimation ()
{
	DWORD dwAMOUNT = m_pSkinChar->GETANIAMOUNT ( m_AniMain, m_AniSub );

	if ( m_pSkinChar->ISENDANIM() ) 
	{
		dwAniSelect ++;
		if ( dwAniSelect >= dwAMOUNT )		dwAniSelect = 0;
	}
}

HRESULT CRanView::InvalidateDeviceObjects()
{
	DxResponseMan::GetInstance().InvalidateDeviceObjects ();
	if ( m_pSkinChar ) m_pSkinChar->InvalidateDeviceObjects();
	return S_OK;
}

HRESULT CRanView::DeleteDeviceObjects()
{
#ifdef _DEBUG
	_CrtCheckMemory();
#endif //_DEBUG

	DxResponseMan::GetInstance().DeleteDeviceObjects ();
	CCursor::GetInstance().DeleteDeviceObjects ();
	if ( m_pSkinChar ) m_pSkinChar->DeleteDeviceObjects();

	return S_OK;
}

HRESULT CRanView::FinalCleanup()
{
	DxResponseMan::GetInstance().FinalCleanup ();
	return S_OK;
}

void CRanView::OnSize(UINT nType, int cx, int cy)
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

void CRanView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CRanApp *pApp = (CRanApp*) AfxGetApp();
	pApp->SetActive ( bActivate );
	CRanView::SetActive ( bActivate );

	__super::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


