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
#include "../EngineLib/DxEffect/EffProj/DxEffProj.h"
#include "../EngineLib/DxEffect/Single/DxEffGroupPlayer.h"
#include "../../EngineSoundLib/DxSound/BgmSound.h"
#include "../../EngineSoundLib/DxSound/DxSoundMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int g_nITEMLEVEL;
extern BOOL g_bCHAR_EDIT_RUN;

HRESULT CRanEditLevelView::FrameMove3DEnvironment ()
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

HRESULT CRanEditLevelView::Render3DEnvironment ()
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

HRESULT CRanEditLevelView::ConfirmDevice ( D3DCAPSQ* pCaps, DWORD dwBehavior, D3DFORMAT Format )
{
	if ( dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING )
		return E_FAIL;

	return S_OK;
}

HRESULT CRanEditLevelView::CreateObjects()
{
	DxFontMan::GetInstance().InitDeviceObjects ( m_pd3dDevice );
	CD3DFontPar* pD3dFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );
	CDebugSet::InitDeviceObjects( pD3dFont9 );

	HRESULT hr = S_OK;

	hr = InitDeviceObjects();
    if( FAILED(hr) )	
	{
		MessageBox( "CRanEditLevelView::CreateObjects()" );
		return hr;
	}

	hr = RestoreDeviceObjects();	
    if( FAILED(hr) )	
	{
		MessageBox( "CRanEditLevelView::CreateObjects()" );
		return hr;
	}

	return hr;
}

HRESULT CRanEditLevelView::InitDeviceObjects()
{
	HRESULT hr = S_OK;

	DxViewPort::GetInstance().InitDeviceObjects ( m_pd3dDevice, m_hWnd );
	DxResponseMan::GetInstance().InitDeviceObjects ( m_pd3dDevice );
	GLogicData::GetInstance().InitDeviceObjects ( m_pd3dDevice );

	DXLIGHT sDirectional;
	sDirectional.SetDefault();
	sDirectional.m_Light.Diffuse = D3DXCOLOR(1.1f,1.1f,1.1f,1);
	sDirectional.m_Light.Ambient = D3DXCOLOR(1.1f,1.1f,1.1f,1);
	DxLightMan::SetDefDirect ( sDirectional );

	hr = m_pd3dDevice->GetDeviceCaps ( &m_d3dCaps );
	DxBoneCollector::GetInstance().PreLoad ( _PRELOAD_BONE, m_pd3dDevice );
	DxSkinAniMan::GetInstance().PreLoad ( _PRELOAD_ANI, m_pd3dDevice );
	DxSkinMeshMan::GetInstance().PreLoad( _PRELOAD_SKIN, m_pd3dDevice, FALSE );

	WORD wWidth = 1024; 
	WORD wHeight = 768;

	LPDIRECT3DSURFACEQ pBackBuffer=NULL;
	m_pd3dDevice->GetBackBuffer ( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );

	if ( pBackBuffer )
	{
		pBackBuffer->GetDesc( &m_d3dsdBackBuffer );
		pBackBuffer->Release();

		wWidth = static_cast<WORD> ( m_d3dsdBackBuffer.Width );
		wHeight = static_cast<WORD> ( m_d3dsdBackBuffer.Height );
	}

	DxViewPort::GetInstance().SetCameraType ((CAMERA_TYPE)2);

	D3DXVECTOR3 vFromPt		= D3DXVECTOR3( 0.0f, 70.0f, -70.0f );
	D3DXVECTOR3 vLookatPt	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec		= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	DxViewPort::GetInstance().SetViewTrans ( vFromPt, vLookatPt, vUpVec );

	DxViewPort::GetInstance().SetMoveVelocity( 300 );

	DxViewPort::GetInstance().CameraJump ( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );

	CCursor::GetInstance().InitDeviceObjects ();
	DxResponseMan::GetInstance().SetRenderState ();
	DxFogMan::GetInstance().SetFogRange ( EMFR_HIGH );

	if ( m_pGLLandServer )
	{
		m_pGLLandServer->InitDeviceObjects( m_pd3dDevice );
	}

	if ( m_pDxLandMan )
	{
		m_pDxLandMan->InitDeviceObjects( m_pd3dDevice );
	}

	m_DxEditBox.InitDeviceObjects( m_pd3dDevice );
	m_DxEditMat.InitDeviceObjects( m_pd3dDevice );
	m_DxEditMRS.OnResetDevice( m_pd3dDevice );

	return S_OK;
}

HRESULT CRanEditLevelView::InvalidateDeviceObjects()
{
	DxResponseMan::GetInstance().InvalidateDeviceObjects ();

	if ( m_pGLLandServer )	m_pGLLandServer->InvalidateDeviceObjects();
	if ( m_pDxLandMan ) m_pDxLandMan->InvalidateDeviceObjects();
	
	m_DxEditMat.InvalidateDeviceObjects();
	m_DxEditMRS.OnLostDevice( m_pd3dDevice );

	return S_OK;
}

HRESULT CRanEditLevelView::RestoreDeviceObjects()
{
	HRESULT hr=S_OK;

	DxResponseMan::GetInstance().RestoreDeviceObjects ();

	if ( m_pd3dDevice )
	{
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

		HRESULT hr;
		LPDIRECT3DSURFACEQ pBackBuffer;
		m_pd3dDevice->GetBackBuffer ( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );

		pBackBuffer->GetDesc( &m_d3dsdBackBuffer );
		pBackBuffer->Release();

		DxViewPort::GetInstance().SetProjection ( D3DX_PI/4, (float)m_d3dsdBackBuffer.Width, 
			(float)m_d3dsdBackBuffer.Height, 1.0f, 1500000.0f );
		
		hr = DxViewPort::GetInstance().SetViewPort ();
		if ( FAILED(hr) )	return hr;

		if ( m_pGLLandServer )	m_pGLLandServer->RestoreDeviceObjects( m_pd3dDevice );
		if ( m_pDxLandMan )	m_pDxLandMan->RestoreDeviceObjects( m_pd3dDevice );
	
		m_DxEditMRS.OnResetDevice( m_pd3dDevice );
	}

	DXPARAMSET::INIT ();
	DxGlowMan::GetInstance().SetProjectActiveON();
	DxPostProcess::GetInstance().SetProjectActiveON();

	m_DxEditMat.RestoreDeviceObjects( m_pd3dDevice );
	m_DxEditMRS.OnResetDevice( m_pd3dDevice );

	DxBgmSound::GetInstance().SetMute ( !bSoundBGM );
	DxSoundMan::GetInstance().SetMapMute ( !bSoundENV );
	DxSoundMan::GetInstance().SetSfxMute ( !bSoundSFX );

	PROFILE_INIT();

	return S_OK;
}

HRESULT CRanEditLevelView::FrameMove()
{
	PROFILE_BEGIN("FrameMove");

	CheckControlfp();
	GLPeriod::GetInstance().UpdateWeather ( m_fElapsedTime );
	DxResponseMan::GetInstance().FrameMove( m_fTime, m_fElapsedTime, m_bDefWin );

	CheckControlfp();

	if ( m_pGLLandServer )	
	{
		SGLNODE<GLMobSchedule*>* pCur = m_pGLLandServer->GetMobSchMan()->GetMobSchList()->m_pHead;
		while ( pCur )
		{
			GLMobSchedule* pMobSch = pCur->Data;
			pMobSch->m_fTimer -= 1000000.0f;
			pCur = pCur->pNext;
		}

		m_pGLLandServer->FrameMove( m_fTime, m_fElapsedTime );
	}

	if ( m_pDxLandMan ) m_pDxLandMan->FrameMove( m_fTime, m_fElapsedTime );
	
	DxEffProjMan::GetInstance().FrameMove( m_fElapsedTime );

	DxViewPort::GetInstance().FrameMove ( m_fTime, m_fElapsedTime );

	m_DxEditBox.FrameMove( m_fTime, m_fElapsedTime );
	m_DxEditMat.FrameMove( m_fTime, m_fElapsedTime );

	DxInputDevice &dxInputDev = DxInputDevice::GetInstance();
	DWORD dwML = dxInputDev.GetMouseState ( DXMOUSE_LEFT );
	bool bCLICK_LEFT = NULL != (dwML&(DXKEY_DOWNED|DXKEY_UP|DXKEY_DUP));

	D3DXVECTOR3 vTargetPt, vFromPt;
	vFromPt = DxViewPort::GetInstance().GetFromPt ();
	BOOL bOk = DxViewPort::GetInstance().GetMouseTargetPosWnd ( vTargetPt );
	if ( bOk && m_pGLLandServer )
	{
		if ( bCLICK_LEFT  )
		{
			if ( dwML&DXKEY_UP )
			{
				D3DXVECTOR3 vCollisionPos;
				DWORD dwCollisionID;
				BOOL bCollision;
				m_pGLLandServer->GetNavi()->IsCollision
				(
					vFromPt,
					vTargetPt,
					vCollisionPos,
					dwCollisionID,
					bCollision
				);

				if ( bCollision )
					m_vPos = vCollisionPos;

				if ( bEditDetect )
				{
					GLMobSchedule* pSched = m_pGLLandServer->GetMobSchMan()->GetCollisionMobSchedule( vFromPt, vTargetPt );
					if ( pSched )
					{
						CMainFrame	*pMainFrame = (CMainFrame*) AfxGetMainWnd();
						if ( pMainFrame )
						{
							pMainFrame->SelectCrow( pSched->m_szName );
						}
					}
				}
			}
		}
	}

	PROFILE_END("FrameMove");

	return S_OK;
}

HRESULT CRanEditLevelView::Render()
{
	if ( !m_pd3dDevice )	return S_FALSE;

	PROFILE_BEGIN("Render");

	D3DCOLOR colorClear = D3DCOLOR_XRGB(150,150,150);
	DxFogMan::GetInstance().RenderFogSB ( m_pd3dDevice );
	colorClear = DxFogMan::GetInstance().GetFogColor();
	
	HRESULT hr = m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,colorClear, 1.0f, 0L );

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
			}else{
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

		

		//if ( m_pGLLandServer && m_pDxLandMan )
		{
			DxWeatherMan::GetInstance()->Render_Prev ( m_pd3dDevice );

			if ( m_pDxLandMan )	DxEnvironment::GetInstance().Render ( m_pd3dDevice, NULL, m_pDxLandMan );

			if ( m_d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGVERTEX )		
			{
				m_pd3dDevice->SetRenderState ( D3DRS_FOGENABLE, TRUE );
			}

			DxSkyMan::GetInstance().Render( m_pd3dDevice );

			if ( m_pDxLandMan )	m_pDxLandMan->Render( m_pd3dDevice, CV ); 

			if ( m_pGLLandServer )
			{
				if ( bRenderCrow )	m_pGLLandServer->Render( m_pd3dDevice, CV ); 
				
				if ( bRenderSched && m_pGLLandServer->GetMobSchMan() )
				{
					m_pGLLandServer->GetMobSchMan()->Render( m_pd3dDevice, CV ); 
				}

				if ( bRenderGenPos )
				{
					SGLNODE<GLMobSchedule*>* pCur = m_pGLLandServer->GetMobSchMan()->GetMobSchList()->m_pHead;

					while ( pCur )
					{
						GLMobSchedule* pMobSch = pCur->Data;
						pMobSch->RenderGenPos ( m_pd3dDevice ); 

						pCur = pCur->pNext;
					}
				}
			}

			if ( bRenderCollisionSphere )
			{
			}

			
			DxShadowMap::GetInstance().ClearShadow( m_pd3dDevice );

			DxShadowMap::GetInstance().LastImageBlur( m_pd3dDevice );

			if ( m_pDxLandMan )	m_pDxLandMan->Render_EFF( m_pd3dDevice, CV ); 
			if ( m_pGLLandServer )	m_pGLLandServer->Render_EFF( m_pd3dDevice, CV );  
			
			DxSkyMan::GetInstance().Render_AFTER( m_pd3dDevice );

			DxEffGroupPlayer::GetInstance().Render ( m_pd3dDevice );

			OPTMManager::GetInstance().Render( m_pd3dDevice );

			if ( m_pDxLandMan)	m_pDxLandMan->RenderPickAlpha( m_pd3dDevice );

			if ( m_d3dCaps.RasterCaps & D3DPRASTERCAPS_FOGVERTEX )		
			{
				m_pd3dDevice->SetRenderState ( D3DRS_FOGENABLE, FALSE );
			}

			DxWeatherMan::GetInstance()->Render ( m_pd3dDevice );
			DxCubeMap::GetInstance().Render ( m_pd3dDevice );
			DxGlowMan::GetInstance().RenderTex ( m_pd3dDevice );
			DxGlowMan::GetInstance().Render ( m_pd3dDevice );
			DxGlowMan::GetInstance().RenderBURN( m_pd3dDevice );
			DxEnvironment::GetInstance().UserToRefraction ( m_pd3dDevice );
			DxEnvironment::GetInstance().RenderWave ( m_pd3dDevice, DxEffectMan::GetInstance().GetBumpTexture() );
			DxPostProcess::GetInstance().Render( m_pd3dDevice );
			DxEffProjMan::GetInstance().Render( m_pd3dDevice );

			if ( m_pGLLandServer )
			{
				if ( bRenderQuad )	m_pGLLandServer->RendQuad( m_pd3dDevice );

				if ( bRenderGate )	m_pGLLandServer->GetLandGateMan().Render( m_pd3dDevice ); 

				if ( bRenderLandEff )
				{
					SLEVEL_ETC_FUNC* pLevelEtcFunc = m_pGLLandServer->GetLevelEtcFunc();

					if ( pLevelEtcFunc )
					{
						if ( pLevelEtcFunc->m_bUseFunction[EMETCFUNC_LANDEFFECT] )
						{
							for( i = 0; i < pLevelEtcFunc->m_vecLandEffect.size(); i++ )
							{
								SLANDEFFECT landEffect = pLevelEtcFunc->m_vecLandEffect[i];

								D3DXVECTOR3 vMaxPos;
								D3DXVECTOR3 vMinPos;

								vMaxPos.x = landEffect.vMaxPos.x;
								vMaxPos.z = landEffect.vMaxPos.y;
								vMaxPos.y = 10.0f;

								vMinPos.x = landEffect.vMinPos.x;
								vMinPos.z = landEffect.vMinPos.y;
								vMinPos.y = -10.0f;

								EDITMESHS::RENDERAABB ( m_pd3dDevice, vMaxPos, vMinPos );
							}
						}
					}
				}
			}

			if ( bRenderCollisionSphere )
			{
				EDITMESHS::RENDERSPHERE( m_pd3dDevice, m_vPos, 4.0f, NULL, D3DXCOLOR( 0.0f, 0.5f, 1.0f, 1.0f) );
			}

			if ( !bEditNone && !bEditDetect && bEditBOX )	m_DxEditBox.Render( m_pd3dDevice );
			if ( !bEditNone && !bEditDetect && bEditMAT )	m_DxEditMat.Render( m_pd3dDevice );
			if ( !bEditNone && !bEditDetect && bEditMRS )	m_DxEditMRS.Render( m_pd3dDevice );
		}

		RenderText();
		CCursor::GetInstance().Render ( m_pd3dDevice, DxInputDevice::GetInstance().GetMouseLocateX(), DxInputDevice::GetInstance().GetMouseLocateY() );
		m_pd3dDevice->EndScene();
	}

	PROFILE_END("Render");
	return S_OK;
}

HRESULT CRanEditLevelView::DeleteDeviceObjects()
{
#ifdef _DEBUG
	_CrtCheckMemory();
#endif //_DEBUG

	GLogicData::GetInstance().DeleteDeviceObjects ();

	if ( m_pGLLandServer )	m_pGLLandServer->DeleteDeviceObjects();
	if ( m_pDxLandMan )	m_pDxLandMan->DeleteDeviceObjects();
	
	DxResponseMan::GetInstance().DeleteDeviceObjects ();
	CCursor::GetInstance().DeleteDeviceObjects ();

	m_DxEditBox.DeleteDeviceObjects();
	m_DxEditMat.DeleteDeviceObjects();

	return S_OK;
}

HRESULT CRanEditLevelView::FinalCleanup()
{
	if ( m_pGLLandServer )	m_pGLLandServer->CleanUp();
	if ( m_pDxLandMan )	m_pDxLandMan->CleanUp();
	
	m_DxEditMat.FinalCleanup();

	DxResponseMan::GetInstance().FinalCleanup ();
	GLogicData::GetInstance().ClearData ();

	return S_OK;
}