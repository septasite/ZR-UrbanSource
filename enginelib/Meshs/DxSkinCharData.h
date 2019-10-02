//
//	[class DxSkinCharData], (2002.12.09), JDH.
//
//
#pragma once

#include <map>
#include <string>
#include <vector>

#include "DxSkinAniMan.h"
#include "DxSkinPieceContainer.h"
//added by tobets | 18-7-2012 | Add ABL and ABF code
#include "DxSkinCharPiece.h"

#include "basestream.h"

#define FG_BONEFILE_CHECK	(0x0001)
#define FG_MUSTNEWLOAD		(0x0002)

class DxSkinCharData : public DxSkinAniControl
{
public:
	enum 
	{ 
		VERSION_SAVE	= 0x0102,
		VERSION_NEW		= 0x0107
	};

	typedef std::vector<std::string>	VECANIFILE;
	typedef VECANIFILE::iterator		VECANIFILE_ITER;

private:
	enum		{ FILE_LENGTH = 64 };
	char		m_szFileName[FILE_LENGTH];

	std::string			m_strPIECE[PIECE_SIZE];
	VECANIFILE			m_vecANIFILE;

	PDXSKINPIECE		m_pPieceArray[PIECE_SIZE];

//added by tobets | 18-7-2012 | Add ABL and ABF code
public:
	std::string			m_strBoneLink[PIECE_SIZE];
	DWORD				m_dwPieceType[PIECE_SIZE];
	DWORD				m_dwWeaponSlot[PIECE_SIZE];

public:
	DxSkinCharPiece*	m_pSkinCharPiece[PIECE_SIZE];

public:
	enum				{ MAX_BONE = 32 };
	DWORD				m_dwBONE;
	float				m_fBONE1[MAX_BONE];
	float				m_fBONE2[MAX_BONE];
	float				m_fBONE3[MAX_BONE];
	std::string			m_strBONE[MAX_BONE];

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
	BOOL LOAD_Ver101( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_Ver104( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_Ver106( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );
	BOOL LOAD_Ver107( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );


public:
	//	=false
	BOOL LoadFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, bool bREPRESH=false  );
	BOOL SaveFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice );


protected:
	 HRESULT CalculateBoundingBox ( LPDIRECT3DDEVICEQ pd3dDevice, D3DXVECTOR3 &vMax, D3DXVECTOR3 &vMin );

//added by tobets | 18-7-2012 | Add ABL and ABF code
public:
	const char*	GetBoneLink( int i ){ return m_strBoneLink[i].c_str(); }

public:
	HRESULT SetPiece ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, DWORD dwFlag = 0x0 );
	void ResetPiece ( LPDIRECT3DDEVICEQ pd3dDevice, int i );
	PDXSKINPIECE GetPiece ( int i )		{ return m_pPieceArray[i]; }
	void SetRadiusHeight();
	void RenderAABBBox( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT ClearAll ();

public:
	DxSkinCharData ();
	~DxSkinCharData ();
};


class DxSkinCharDataContainer
{
private:
	typedef std::map<std::string,DxSkinCharData*>			SKINCHARDATAMAP;
	typedef std::map<std::string,DxSkinCharData*>::iterator	SKINCHARDATAMAP_ITER;

protected:
	char			m_szPath[MAX_PATH];

	SKINCHARDATAMAP	m_mapSkinCharData;

public:
	void			SetPath ( char* szPath ) { StringCchCopy( m_szPath, MAX_PATH, szPath ); }
	char*			GetPath ()	{ return m_szPath; }

public:
	DxSkinCharData* FindData ( const char* szFile );
	DxSkinCharData* LoadData ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread );

	void ReleaseData ( const char* szFile );
	BOOL DeleteData ( const char* szFile );

	HRESULT CleanUp ();

protected:
	DxSkinCharDataContainer ();

public:
	~DxSkinCharDataContainer ();

public:
	static DxSkinCharDataContainer& GetInstance();
};

