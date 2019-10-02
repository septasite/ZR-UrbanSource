#pragma once

#include <map>
#include <string>
#include <vector>

#include "DxSkinAniMan.h"
#include "DxSkinPieceContainer.h"

#include "DxSkinCharPiece.h"

#include "basestream.h"

#define FG_BONEFILE_CHECK	(0x0001)
#define FG_MUSTNEWLOAD		(0x0002)

class DxSkinVehicleData : public DxSkinAniControl
{
public:
	enum { VERSION = 0x0100, };
	typedef std::vector<std::string>	VECANIFILE;
	typedef VECANIFILE::iterator		VECANIFILE_ITER;

private:
	enum		{ FILE_LENGTH = 64 };
	char		m_szFileName[FILE_LENGTH];

public:
	std::string			m_strPIECE[PIECE_SIZE];

private:
	VECANIFILE			m_vecANIFILE;

	PDXSKINPIECE		m_pPieceArray[PIECE_SIZE];

public:
	std::string			m_strBoneLink[PIECE_SIZE];
	DWORD				m_dwPieceType[PIECE_SIZE];
	DWORD				m_dwWeaponSlot[PIECE_SIZE];

public:
	DxSkinCharPiece*	m_pSkinCharPiece[PIECE_SIZE];
public:
	enum				{ MAX_BONE = 32 };

	//NeoMasteI2 Development 2011
	DWORD				m_dwBONE;
	float				m_fBONE1[MAX_BONE];
	float				m_fBONE2[MAX_BONE];
	float				m_fBONE3[MAX_BONE];
	std::string			m_strBONE[MAX_BONE];

public:
	DWORD				m_dwRef;

	float				m_fScale;

	D3DXVECTOR3			m_vRotation_Font, m_vTransform_Font;
	D3DXVECTOR3			m_vRotation_Back, m_vTransform_Back;
	std::string			m_strChar_Font;
	std::string			m_strChar_Back;

public:
	const char* GetFileName()		{ return m_szFileName; }

protected:
	BOOL LOAD_Ver100( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice );

public:
	BOOL LoadFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, bool bREPRESH=false  );
	BOOL SaveFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice );

public:
	const char*	GetBoneLink( int i ){ return m_strBoneLink[i].c_str(); }

public:
	HRESULT SetPiece ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, DWORD dwFlag = 0x0 );
	void ResetPiece ( LPDIRECT3DDEVICEQ pd3dDevice, int i );
	PDXSKINPIECE GetPiece ( int i )		{ return m_pPieceArray[i]; }
	HRESULT ClearAll ();

public:
	DxSkinVehicleData ();
	~DxSkinVehicleData ();
};


class DxSkinVehicleDataContainer
{
private:
	typedef std::map<std::string,DxSkinVehicleData*>			SKINCHARDATAMAP;
	typedef std::map<std::string,DxSkinVehicleData*>::iterator	SKINCHARDATAMAP_ITER;

protected:
	char			m_szPath[MAX_PATH];

	SKINCHARDATAMAP	m_mapSkinCharData;

public:
	void			SetPath ( char* szPath ) { StringCchCopy( m_szPath, MAX_PATH, szPath ); }
	char*			GetPath ()	{ return m_szPath; }

public:
	DxSkinVehicleData* FindData ( const char* szFile );
	DxSkinVehicleData* LoadData ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread );

	void ReleaseData ( const char* szFile );
	BOOL DeleteData ( const char* szFile );

	HRESULT CleanUp ();

protected:
	DxSkinVehicleDataContainer ();

public:
	~DxSkinVehicleDataContainer ();

public:
	static DxSkinVehicleDataContainer& GetInstance();
};

