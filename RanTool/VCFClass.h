#pragma once
#include "stdafx.h"

#include <map>
#include <string>
#include <vector>

#include "DxSkinVehicleData.h"
#include "DxSkinCharData.h"
#include "../../EngineLib/Meshs/DxPieceDefine.h"


class CVCFClass
{
public:
	enum { VERSION = 0x0100, };
	typedef std::vector<std::string>	VECANIFILE;
	typedef VECANIFILE::iterator		VECANIFILE_ITER;

	std::string			m_strPIECE[PIECE_SIZE];
	VECANIFILE			m_vecANIFILE;
	std::string			m_strANINAME;

	enum				{ MAX_BONE = 32 };
	DWORD				m_dwBONE;
	float				m_fBONE1[MAX_BONE];
	float				m_fBONE2[MAX_BONE];
	float				m_fBONE3[MAX_BONE];
	std::string			m_strBONE[MAX_BONE];

	std::string			m_strSkeleton;

	float				m_fScale;

	D3DXVECTOR3			m_vRotation_Font, m_vTransform_Font;
	D3DXVECTOR3			m_vRotation_Back, m_vTransform_Back;
	std::string			m_strChar_Font;
	std::string			m_strChar_Back;

protected:
	BOOL LOAD_Ver100( basestream &SFile );

public:
	BOOL LoadFile ( const char* szFile );
	BOOL SaveFile ( const char* szFile );
	void Reset();

public:
	CVCFClass();
	~CVCFClass();
};

