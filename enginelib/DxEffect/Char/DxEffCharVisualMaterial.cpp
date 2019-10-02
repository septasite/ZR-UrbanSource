#include "stdafx.h"
#include "../DxEffect/Single/DxEffSingle.h"
#include "../Single/DxEffSinglePropGMan.h"
#include "../Common/SerialFile.h"

#include "../DxEffect/DxLoadShader.h"
#include "../DxCommon/DxRenderStates.h"

#include "../DxCommon/DxLightMan.h"
#include "../DxCommon/DxViewPort.h"
#include "../DxEffect/DxEffectMan.h"

#include "../DxCommon/RENDERPARAM.h"
#include "../Meshs/DxCharPart.h"
#include "../Meshs/DxSkinPieceContainer.h"

#include "./DxEffCharHLSL.h"
#include "../Meshs/DxSkinMesh9_HLSL.h"

#include "./DxEffCharVisualMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWORD		DxEffCharVisualMaterial::TYPEID			= EMEFFCHAR_VISUALMATERIAL;
DWORD		DxEffCharVisualMaterial::VERSION			= 0x0100;
DWORD		DxEffCharVisualMaterial::VERSION_SAVE		= 0x0100;
char		DxEffCharVisualMaterial::NAME[MAX_PATH]	= "EffCharNormal";

DxEffCharVisualMaterial::DxEffCharVisualMaterial(void) :
	DxEffChar(),
	m_pSkinMesh(NULL),
	m_pmcMesh(NULL)
{
}

DxEffCharVisualMaterial::~DxEffCharVisualMaterial(void)
{
	CleanUp ();
}

DxEffChar* DxEffCharVisualMaterial::CloneInstance ( LPDIRECT3DDEVICEQ pd3dDevice, DxCharPart* pCharPart, DxSkinPiece* pSkinPiece )
{
	HRESULT hr;
	DxEffCharVisualMaterial *pEffChar = new DxEffCharVisualMaterial;
	pEffChar->SetLinkObj ( pCharPart, pSkinPiece );
	pEffChar->SetProperty ( &m_Property );
	pEffChar->m_sMaterialHLSL.Clone( pd3dDevice, &m_sMaterialHLSL );

	hr = pEffChar->Create ( pd3dDevice );
	if ( FAILED(hr) )
	{
		SAFE_DELETE(pEffChar);
		return NULL;
	}

	return pEffChar;
}

HRESULT DxEffCharVisualMaterial::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pCharPart )
	{
		m_pSkinMesh = m_pCharPart->m_pSkinMesh;
		m_pmcMesh = m_pCharPart->m_pmcMesh;
	}
	else if ( m_pSkinPiece )
	{
		m_pSkinMesh = m_pSkinPiece->m_pSkinMesh;
		m_pmcMesh = m_pSkinPiece->m_pmcMesh;
	}

	if( !m_pmcMesh )	return S_OK;
	m_sMaterialHLSL.OnCreateDevice( pd3dDevice, m_pmcMesh->pMaterials, m_pmcMesh->GetNumMaterials() );

	return S_OK;
}

HRESULT DxEffCharVisualMaterial::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	return S_OK;
}

HRESULT DxEffCharVisualMaterial::InvalidateDeviceObjects ()
{
	return S_OK;
}

HRESULT DxEffCharVisualMaterial::DeleteDeviceObjects ()
{
	m_sMaterialHLSL.OnDestroyDevice();

	return S_OK;
}

HRESULT DxEffCharVisualMaterial::FrameMove ( float fTime, float fElapsedTime )
{
	HRESULT hr = S_OK;

	return S_OK;
}

void DxEffCharVisualMaterial::Render( LPDIRECT3DDEVICEQ pd3dDevice, BOOL bPieceRender )
{
	if( !m_pmcMesh )		return;
	if( !m_pSkinMesh )		return;

    // Note : ReloadTexture - Loading檜 寰 脹 匙擊 嬪 褻纂.
	m_sMaterialHLSL.ReloadTexture();

	m_pSkinMesh->SetDrawState( FALSE, FALSE, FALSE, FALSE );
	m_pSkinMesh->DrawMeshNORMALMAP( pd3dDevice, m_pmcMesh, NULL, &m_sMaterialHLSL, bPieceRender );
}

HRESULT	DxEffCharVisualMaterial::LoadFile ( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice,bool bTool,bool bRan2 )
{
	DWORD dwVer, dwSize;

	SFile >> dwVer;
	SFile >> dwSize;

	//	Note : 幗瞪檜 橾纂 唳辦. 
	if( dwVer == VERSION )
	{
		//	Note : 檜曖 Property 蒂 盪濰.
		SFile.ReadBuffer ( &m_Property, sizeof(m_Property) );
		m_sMaterialHLSL.Load( pd3dDevice, SFile );

		//	Note : Device 濠錳擊 儅撩棻.
		HRESULT hr(S_OK);
		if (!bTool)
		{
			hr = Create( pd3dDevice );
			if ( FAILED(hr) )	return hr;
		}
	}
	else
	{
		CString strTemp = "";
		strTemp.Format( "DxEffCharVisualMaterial::LoadFile Error! Name:%s Version:%d Size:%d Current Version:%d" ,SFile.GetFileName(),dwVer,dwSize,VERSION);
		//MessageBox (NULL,strTemp,"Need New Version",MB_OK);
		//CDebugSet::ToFile ( "EngineLoadError.txt",strTemp );
		strTemp.Empty();
		//
		SFile.SetOffSet ( SFile.GetfTell()+dwSize );
		
		return E_FAIL;
	}

	return S_OK;
}

HRESULT	DxEffCharVisualMaterial::SaveFile ( basestream &SFile,bool bTool )
{
	SFile << TYPEID;
	SFile << VERSION_SAVE;

	SFile.BeginBlock( EMBLOCK_00 );
	{
		SFile.WriteBuffer ( &m_Property, sizeof(m_Property) );
		m_sMaterialHLSL.Save( SFile );
	}
	SFile.EndBlock( EMBLOCK_00 );

	return S_OK;
}

