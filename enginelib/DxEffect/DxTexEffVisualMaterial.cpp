#include "stdafx.h"

#include "../Common/SerialFile.h"
#include "./DxTexEffVisualMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const DWORD DxTexEffVisualMaterial::TYPEID = DEF_TEXEFF_VISUALMATERIAL;
const DWORD	DxTexEffVisualMaterial::VERSION = 0x00000102;
const char DxTexEffVisualMaterial::NAME[] = "DxTexEffVisualMaterial";

TEXEFF_VISUALMATERIAL_PROPERTY::TEXEFF_VISUALMATERIAL_PROPERTY() :
dw0(0)
, dw1(0)
{
	strVisualMaterial ="";
	for ( int i=0; i<100; ++i )
	{
		strTex[i] = "";
	}
}

TEXEFF_VISUALMATERIAL_PROPERTY::~TEXEFF_VISUALMATERIAL_PROPERTY()
{
}

void TEXEFF_VISUALMATERIAL_PROPERTY::Save( CSerialFile& SFile )
{
	SFile << strVisualMaterial;
	SFile << dw0;
	SFile << dw1;

	for ( int i=0; i<dw0; ++i )
	{
		SFile << strTex[i];
	}

	SFile << DWORD(4);
	SFile << DWORD(0);
}

void TEXEFF_VISUALMATERIAL_PROPERTY::Load_100( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile )
{
	SFile >> strVisualMaterial;
	SFile >> dw0;
	SFile >> dw1;

	for ( int i=0; i<dw0; ++i )
	{
		SFile >> strTex[i];
	}
}

void TEXEFF_VISUALMATERIAL_PROPERTY::Load_102( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile )
{
	SFile >> strVisualMaterial;
	SFile >> dw0;
	SFile >> dw1;

	for ( int i=0; i<dw0; ++i )
	{
		SFile >> strTex[i];
	}

	DWORD dwBlockSize = SFile.ReadBlockSize();
	SFile.SetOffSet ( SFile.GetfTell()+dwBlockSize );
}

// Note : DxTexEffVisualMaterial
LPDIRECT3DSTATEBLOCK9	DxTexEffVisualMaterial::m_pSavedSB = NULL;
LPDIRECT3DSTATEBLOCK9	DxTexEffVisualMaterial::m_pDrawSB = NULL;

DxTexEffVisualMaterial::DxTexEffVisualMaterial()
{
}

DxTexEffVisualMaterial::~DxTexEffVisualMaterial()
{
}

void DxTexEffVisualMaterial::SetProperty( LPDIRECT3DDEVICEQ pd3dDevice, PBYTE &pProp )
{
	TEXEFF_VISUALMATERIAL_PROPERTY* pTemp = (TEXEFF_VISUALMATERIAL_PROPERTY*)pProp;

	m_sProp.strVisualMaterial = pTemp->strVisualMaterial;
	m_sProp.dw0	= pTemp->dw0;
	m_sProp.dw1	= pTemp->dw1;

	for ( int i=0; i<100; ++i )
	{
		m_sProp.strTex[i] = pTemp->strTex[i];
	}
}

void DxTexEffVisualMaterial::OnCreateDevice( LPDIRECT3DDEVICEQ pd3dDevice )
{
	D3DCAPSQ d3dCaps;
	pd3dDevice->GetDeviceCaps ( &d3dCaps );

	for( UINT which=0; which<2; which++ )
	{
		pd3dDevice->BeginStateBlock();

		//	Note : SetRenderState() 識情
		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		FALSE );
		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,	TRUE );
		pd3dDevice->SetRenderState( D3DRS_FOGCOLOR,			0x00000000 );

		pd3dDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,			D3DBLEND_ONE );
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND,		D3DBLEND_ONE );

		//	Note : SetTextureStageState() 識情
		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,	D3DTOP_SELECTARG1 );
		pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,	D3DTOP_MODULATE );

		pd3dDevice->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX,			D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR );
		pd3dDevice->SetTextureStageState( 1, D3DTSS_TEXTURETRANSFORMFLAGS,	D3DTTFF_COUNT3 );

		if( which==0 )	pd3dDevice->EndStateBlock ( &m_pSavedSB );
		else			pd3dDevice->EndStateBlock ( &m_pDrawSB );
	}
}

void DxTexEffVisualMaterial::OnReleaseDevice( LPDIRECT3DDEVICEQ pd3dDevice )
{
	SAFE_RELEASE( m_pSavedSB );
	SAFE_RELEASE( m_pDrawSB );
}

void DxTexEffVisualMaterial::FrameMove( const float fElapsedTime )	{}

void DxTexEffVisualMaterial::Render( LPDIRECT3DDEVICEQ pd3dDevice, LPD3DXMESH pMesh, const DWORD dwAttrib )
{
}

void DxTexEffVisualMaterial::SetRenderBegin( LPDIRECT3DDEVICEQ pd3dDevice )
{
}

void DxTexEffVisualMaterial::SetRenderEnd( LPDIRECT3DDEVICEQ pd3dDevice )
{
}

void DxTexEffVisualMaterial::SavePSF( CSerialFile& SFile )
{
	SFile << VERSION;
	SFile.BeginBlock( EMBLOCK_02 );
	m_sProp.Save( SFile );
	SFile.EndBlock( EMBLOCK_02 );
}

void DxTexEffVisualMaterial::LoadPSF( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile )
{
	DWORD dwSize;
	DWORD dwVer;
	SFile >> dwVer;
	SFile >> dwSize;

	if( dwVer==VERSION )
	{
		m_sProp.Load_102( pd3dDevice, SFile );
	}
	else if( dwVer==0x00000100 )
	{
		m_sProp.Load_100( pd3dDevice, SFile );
	}
	else
	{
		DWORD dwCurBuffer = SFile.GetfTell();
		SFile.SetOffSet( dwCurBuffer+dwSize );
	}
}
