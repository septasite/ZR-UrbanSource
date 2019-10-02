#pragma once
#include "stdafx.h"

#include <map>
#include <string>
#include <vector>

#include "DxSkinCharData.h"
#include "../../EngineLib/Meshs/DxPieceDefine.h"


class CABFClass 
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

	DWORD				m_dwRef;

	BOOL				m_bWorldObj;
	float				m_fScale;
	D3DXVECTOR3			m_vMax, m_vMin;

	float				m_fHeight;
	float				m_fRadius;

protected:
	BOOL LOAD_Ver100( basestream &SFile );
	BOOL LOAD_Ver100_PH( basestream &SFile );

public:
	BOOL LoadFile ( const char* szFile );
	BOOL LoadFile_PH ( const char* szFile );
	BOOL SaveFile ( const char* szFile );
	BOOL SaveFileOld ( const char* szFile );
	void Reset();

public:
	CABFClass();
	~CABFClass();
};