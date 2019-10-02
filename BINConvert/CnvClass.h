#pragma once
#include "stdafx.h"

#include "SAnimation.h"
#include "DxSkinAniMan.h"


struct BSPositionKey
{
	DWORD		dwTime;
	D3DXVECTOR3	vPos;	
};

struct BSRotateKey
{
	DWORD			dwTime;
	D3DXQUATERNION	quatRotate;	
};

struct BSScaleKey
{
	DWORD		dwTime;
	D3DXVECTOR3	vScale;	
};

struct BSMatrixKey
{
	DWORD			dwTime;
	D3DXMATRIXA16	mat;

	BSMatrixKey() :
		dwTime(0)
	{
	}

	~BSMatrixKey()
	{
	}

	bool operator < ( const BSMatrixKey &rvalue ) const
	{
		return dwTime < rvalue.dwTime;
	}
};

struct BQUATCOMP
{
	DWORD dwFirst;
	DWORD dwSecond;

	BQUATCOMP()	{}
	BQUATCOMP( DWORD a, DWORD b ) :
		dwFirst(a),
		dwSecond(dwSecond)
	{
	}
};

struct BSQuatPosKey
{
	DWORD			m_dwTime;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vPos;
	BQUATCOMP		m_vQuatComp;	

	BSQuatPosKey() :
		m_dwTime(0L),
		m_vScale(0.f,0.f,0.f),
		m_vPos(0.f,0.f,0.f),
		m_vQuatComp(0,0)
	{
	}

	~BSQuatPosKey()
	{
	}

	bool operator < ( const BSQuatPosKey &rvalue ) const
	{
		return m_dwTime < rvalue.m_dwTime;
	}
};


struct InnerBin
{
	enum 
	{ 
		VERSION					= 0x0103,
		VERSION_BIN_INNER_SAVE	= 0x0102, 
	};

	BSPositionKey	*m_pPositionKeys;
	UINT			m_cPositionKeys;
	
	BSRotateKey		*m_pRotateKeys;
	UINT			m_cRotateKeys;
	
	BSScaleKey		*m_pScaleKeys;
	UINT			m_cScaleKeys;
	
	BSMatrixKey		*m_pMatrixKeys;
	UINT			m_cMatrixKeys;

	BSQuatPosKey*	m_pQuatPosKeys;
	UINT			m_cQuatPosKeys;
	D3DXQUATERNION*	m_pQuatOrigRot;	

	TSTRING			m_strBone;
	DxBoneTrans		*pBoneToAnimate;

	DWORD			m_dwCurKey;
	float			m_fDivFullTime;	
	float			m_fMatrixKeys;

	InnerBin() :
			m_pPositionKeys(NULL),
			m_cPositionKeys(0),
			m_pScaleKeys(NULL),
			m_cScaleKeys(0),
			m_pRotateKeys(NULL),
			m_cRotateKeys(0),
			m_pMatrixKeys(NULL),
			m_cMatrixKeys(0),
			m_pQuatPosKeys(NULL),
			m_cQuatPosKeys(0),
			m_pQuatOrigRot(NULL),

			pBoneToAnimate(NULL),
			m_dwCurKey(0),
			m_fDivFullTime(0.f),
			m_fMatrixKeys(0.f)
	{
	}

	~InnerBin()
	{
		SAFE_DELETE_ARRAY(m_pPositionKeys);
		SAFE_DELETE_ARRAY(m_pRotateKeys);
		SAFE_DELETE_ARRAY(m_pScaleKeys);
		SAFE_DELETE_ARRAY(m_pMatrixKeys);
		SAFE_DELETE_ARRAY(m_pQuatPosKeys);
		SAFE_DELETE_ARRAY(m_pQuatOrigRot);

	}


	HRESULT SaveToFile ( CSerialFile &SFile );
	HRESULT LoadFromFile ( CSerialFile &SFile );
	HRESULT Load_0100( CSerialFile &SFile );
	HRESULT Load_0101( CSerialFile &SFile );
	HRESULT Load_0102( CSerialFile &SFile );
	HRESULT Load( CSerialFile &SFile );
};

struct BinManager
{
public:
	enum 
	{ 
		VERSION			= 0x0104,
		VERSION_ANISAVE	= 0x0102,
	};
	const static TCHAR szFILETYPE[];


	typedef std::list<InnerBin*>		SANILIST;
	typedef SANILIST::iterator			SANILIST_ITER;

	DWORD					m_dwRefCount;

	bool					m_bLOAD;
	bool					m_bVALID;

	SANILIST				m_listAnimation;
	SANILIST				m_listAniUPBODY;

public:

	HRESULT  Load_0100( CSerialFile &SFile );
	HRESULT  Load_0101( CSerialFile &SFile );
	HRESULT  Load_0102( CSerialFile &SFile );
	HRESULT  Load_0103( CSerialFile &SFile );
	HRESULT  Load( CSerialFile &SFile );

	BOOL LoadFile ( const char* szFile );
	BOOL SaveFile ( const char* szFile );

};




