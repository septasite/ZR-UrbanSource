#pragma once
#include "stdafx.h"

#include "DxSkinPieceData.h"
#include "../../EngineLib/Meshs/DxPieceDefine.h"


class DxSkinPieceRootDataDummy
{
public:
	enum { VERSION = 0x0101, };

	std::string			m_strAbf;
	std::string			m_strCPS;
	std::string			m_strSkeleton;
	std::string			m_strBoneLink;

	DWORD				m_dwType;
	DWORD				m_dwWeaponSlot;

	BOOL				m_bCPS;

	float				m_fRotX;
	float				m_fRotY;
	float				m_fRotZ;

	float				m_fRootX;
	float				m_fRootY;
	float				m_fRootZ;

	float				m_fRotX_F;
	float				m_fRotY_F;
	float				m_fRotZ_F;

	float				m_fRootX_F;
	float				m_fRootY_F;
	float				m_fRootZ_F;
	
	D3DXVECTOR3			m_vRoot;
	D3DXVECTOR3			m_vRot;
	D3DXVECTOR3			m_vScale;
	D3DXVECTOR3			m_vRoot_F;
	D3DXVECTOR3			m_vRot_F;
	D3DXVECTOR3			m_vScale_F;

protected:
	BOOL LOADNEO_Ver100( basestream &SFile );
	BOOL LOAD_Ver100( basestream &SFile );
	BOOL LOAD_Ver101( basestream &SFile );
public:
	BOOL LoadFile ( const char* szFile );
	BOOL SaveFile ( const char* szFile );

	BOOL LoadFileNeo ( const char* szFile );
public:
	DxSkinPieceRootDataDummy ();
	~DxSkinPieceRootDataDummy ();
};

namespace DUMMYABL
{
	extern std::string m_CharType[PIECE_SIZE];
	extern std::string m_SlotType[EMPEACE_WEAPON_SIZE];
};


