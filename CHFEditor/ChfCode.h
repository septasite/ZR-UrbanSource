#pragma once
#include "stdafx.h"

#include <map>
#include <string>
#include <vector>

#include "DxSkinCharData.h"

class CChfCode 
{
public:
	enum { VERSION = 0x0107, };
	typedef std::vector<std::string>	VECANIFILE;
	typedef VECANIFILE::iterator		VECANIFILE_ITER;

	std::string			m_strPIECE[PIECE_SIZE];
	VECANIFILE			m_vecANIFILE;

	std::string			m_strANINAME;

	std::string			m_strSkeleton;

	BOOL				m_bWorldObj;
	float				m_fScale;
	D3DXVECTOR3			m_vMax, m_vMin;

	float				m_fHeight;
	float				m_fRadius;

protected:
	BOOL LOAD_Ver100( basestream &SFile );
	BOOL LOAD_Ver101( basestream &SFile );
	BOOL LOAD_Ver103( basestream &SFile );
	BOOL LOAD_Ver106( basestream &SFile );
	BOOL LOAD_Ver107( basestream &SFile );

public:
	enum				{ MAX_BONE = 1024 };
	DWORD				m_dwBONE;
	float				m_fBONE1[MAX_BONE];
	float				m_fBONE2[MAX_BONE];
	float				m_fBONE3[MAX_BONE];
	std::string			m_strBONE[MAX_BONE];

public:
	BOOL LoadFile ( const char* szFile );
	BOOL SaveFile ( const char* szFile );

public:
	CChfCode();
	~CChfCode();
};