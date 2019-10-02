//
//	[class DxSkinPieceData], (2002.12.09), JDH.
//
//
#pragma once

#include <map>
#include <string>
#include <vector>

#include "DxSkinAniMan.h"
#include "DxSkinPieceContainer.h"

#include "basestream.h"

#define FG_BONEFILE_CHECK	(0x0001)
#define FG_MUSTNEWLOAD		(0x0002)

class DxSkinPieceData : public DxSkinAniControl
{
public:
	enum { VERSION = 0x0100, };
	typedef std::vector<std::string>	VECANIFILE;
	typedef VECANIFILE::iterator		VECANIFILE_ITER;

private:
	enum		{ FILE_LENGTH = 64 };
	char		m_szFileName[FILE_LENGTH];

	std::string			m_strPIECE[PIECE_SIZE];
	VECANIFILE			m_vecANIFILE;

	PDXSKINPIECE		m_pPieceArray[PIECE_SIZE];
public:
	enum				{ MAX_BONE = 32 };

	DWORD				m_dwBONE;
	float				m_fBONE1[MAX_BONE];
	float				m_fBONE2[MAX_BONE];
	float				m_fBONE3[MAX_BONE];
	std::string			m_strBONE[MAX_BONE];

public:
	std::string			m_strPIECE_P[PIECE_SIZE];

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	std::string			m_strAbf2;
	std::string			m_strCPS2;
	std::string			m_strSkeleton2;
	std::string			m_strBoneLink2;

	BOOL				m_bCPS;

	DWORD				m_dwType;
	DWORD				m_dwWeaponSlot;

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	D3DXVECTOR3			m_vRot;
	D3DXVECTOR3			m_vRoot;
	D3DXVECTOR3			m_vScale;

	D3DXVECTOR3			m_vRot_F;
	D3DXVECTOR3			m_vRoot_F;
	D3DXVECTOR3			m_vScale_F;

public:
	DWORD				m_dwRef;

	BOOL				m_bWorldObj;
	float				m_fScale;
	D3DXVECTOR3			m_vMax, m_vMin;

	float				m_fHeight;
	float				m_fRadius;

public:
	const char* GetFileName()		{ return m_szFileName; }

protected:
	BOOL LOAD_Ver100( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );

public:
	//	=false
	BOOL LoadFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, bool bREPRESH=false  );
	BOOL SaveFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL SaveFile_B ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice );

protected:
	 HRESULT CalculateBoundingBox ( LPDIRECT3DDEVICEQ pd3dDevice, D3DXVECTOR3 &vMax, D3DXVECTOR3 &vMin );

public:
	HRESULT SetPiece ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, DWORD dwFlag = 0x0 );
	void ResetPiece ( LPDIRECT3DDEVICEQ pd3dDevice, int i );
	PDXSKINPIECE GetPiece ( int i )		{ return m_pPieceArray[i]; }
	void SetRadiusHeight();
	void RenderAABBBox( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT ClearAll ();

public:
	DxSkinPieceData ();
	~DxSkinPieceData ();
};


class DxSkinPieceDataContainer
{
private:
	typedef std::map<std::string,DxSkinPieceData*>			SKINCHARDATAMAP;
	typedef std::map<std::string,DxSkinPieceData*>::iterator	SKINCHARDATAMAP_ITER;

protected:
	char			m_szPath[MAX_PATH];

	SKINCHARDATAMAP	m_mapSkinCharData;

public:
	void			SetPath ( char* szPath ) { StringCchCopy( m_szPath, MAX_PATH, szPath ); }
	char*			GetPath ()	{ return m_szPath; }

public:
	DxSkinPieceData* FindData ( const char* szFile );
	DxSkinPieceData* LoadData ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread );

	void ReleaseData ( const char* szFile );
	BOOL DeleteData ( const char* szFile );

	HRESULT CleanUp ();

protected:
	DxSkinPieceDataContainer ();

public:
	~DxSkinPieceDataContainer ();

public:
	static DxSkinPieceDataContainer& GetInstance();
};

