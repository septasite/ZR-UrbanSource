#pragma once

#include <string>
#include "DxTexEff.h"

class CSerialFile;
struct DxMeshes;

struct TEXEFF_VISUALMATERIAL_PROPERTY
{
	std::string		strVisualMaterial;
	DWORD			dw0;
	DWORD			dw1;
	std::string		strTex[100];

	void Save( CSerialFile& SFile );
	void Load_100( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile );
	void Load_102( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile );

	TEXEFF_VISUALMATERIAL_PROPERTY();
	~TEXEFF_VISUALMATERIAL_PROPERTY();
};

class DxTexEffVisualMaterial : public DxTexEffBase
{
public:
	const static DWORD	TYPEID;
	const static DWORD	VERSION;
	const static char	NAME[];

protected:
	TEXEFF_VISUALMATERIAL_PROPERTY	m_sProp;

public:
	virtual DWORD GetTypeID()				{ return TYPEID; }
	virtual const char* GetName()			{ return NAME; }
	virtual void GetProperty( PBYTE &pProp ) { pProp = (PBYTE)&m_sProp; }
	virtual void SetProperty( LPDIRECT3DDEVICEQ pd3dDevice, PBYTE &pProp );

public:
	virtual void FrameMove( const float fElapsedTime );

public:
	static LPDIRECT3DSTATEBLOCK9	m_pSavedSB;
	static LPDIRECT3DSTATEBLOCK9	m_pDrawSB;
	static void OnCreateDevice( LPDIRECT3DDEVICEQ pd3dDevice );
	static void OnReleaseDevice( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	void Render( LPDIRECT3DDEVICEQ pd3dDevice, LPD3DXMESH pMesh, const DWORD dwAttrib );
	void SetRenderBegin( LPDIRECT3DDEVICEQ pd3dDevice );
	void SetRenderEnd( LPDIRECT3DDEVICEQ pd3dDevice );

public:
	TEXEFF_VISUALMATERIAL_PROPERTY* GetProperty()	{ return &m_sProp; }

public:
	virtual void SavePSF( CSerialFile& SFile );
	virtual void LoadPSF( LPDIRECT3DDEVICEQ pd3dDevice, CSerialFile& SFile );

public:
	DxTexEffVisualMaterial();
	virtual ~DxTexEffVisualMaterial();
};
