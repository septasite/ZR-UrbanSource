#pragma once
#include "stdafx.h"

#include <map>
#include <string>
#include <vector>

#include "DxSkinPieceData.h"
#include "../../EngineLib/Meshs/DxPieceDefine.h"


class CABLClass
{
public:
	enum { VERSION = 0x0100, };

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


protected:
	BOOL LOADNEO_Ver100( basestream &SFile );
	BOOL LOAD_Ver100( basestream &SFile );
	BOOL LOAD_Ver101( basestream &SFile );

public:
	BOOL LoadFile ( const char* szFile );
	BOOL SaveFile ( const char* szFile );
	BOOL LoadFileNeo ( const char* szFile );
	void Reset();

public:
	CABLClass ();
	~CABLClass ();
};


