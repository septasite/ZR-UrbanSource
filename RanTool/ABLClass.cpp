#include "stdafx.h"

#include "ABLClass.h"
#include "../G-Logic/GLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CABLClass::CABLClass(void):
	m_dwType(0)
	,m_dwWeaponSlot(0)
	,m_bCPS(FALSE)
	,m_fRotX(0.0f)
	,m_fRotY(0.0f)
	,m_fRotZ(0.0f)
	,m_fRootX(0.0f)
	,m_fRootY(0.0f)
	,m_fRootZ(0.0f)
	,m_fRotX_F(0.0f)
	,m_fRotY_F(0.0f)
	,m_fRotZ_F(0.0f)
	,m_fRootX_F(0.0f)
	,m_fRootY_F(0.0f)
	,m_fRootZ_F(0.0f)
{
	m_strAbf = "";
	m_strCPS = "";
	m_strSkeleton = "";
	m_strBoneLink = "";
}

CABLClass::~CABLClass(void)
{
}

BOOL CABLClass::SaveFile ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << VERSION;

	SFile << m_strAbf;
	SFile << m_strCPS;
	SFile << m_strSkeleton;
	SFile << m_strBoneLink;
	SFile << m_dwType;
	SFile << m_dwWeaponSlot;
	SFile << m_fRotX;
	SFile << m_fRotY;
	SFile << m_fRotZ;
	SFile << m_fRootX;
	SFile << m_fRootY;
	SFile << m_fRootZ;
	SFile << m_fRotX_F;
	SFile << m_fRotY_F;
	SFile << m_fRotZ_F;
	SFile << m_fRootX_F;
	SFile << m_fRootY_F;
	SFile << m_fRootZ_F;

	return TRUE;
}

BOOL CABLClass::LOADNEO_Ver100( basestream &SFile )
{
	SFile >> m_strAbf;
	SFile >> m_strCPS;
	SFile >> m_strSkeleton;
	SFile >> m_strBoneLink;
	SFile >> m_dwType;
	SFile >> m_dwWeaponSlot;
	SFile >> m_fRotX;
	SFile >> m_fRotY;
	SFile >> m_fRotZ;
	SFile >> m_fRootX;
	SFile >> m_fRootY;
	SFile >> m_fRootZ;
	SFile >> m_fRotX_F;
	SFile >> m_fRotY_F;
	SFile >> m_fRotZ_F;
	SFile >> m_fRootX_F;
	SFile >> m_fRootY_F;
	SFile >> m_fRootZ_F;

	if ( strcmp( m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_bCPS = TRUE;
	}

	return TRUE;
}

BOOL CABLClass::LOAD_Ver100( basestream &SFile )
{
	DWORD dwDummy0;
	DWORD dwDummy1;

	SFile >> dwDummy0;
	SFile >> m_strAbf;
	SFile >> m_strCPS;
	SFile >> m_strSkeleton;
	SFile >> m_strBoneLink;
	SFile >> dwDummy1;
	SFile >> m_dwType;
	SFile >> m_dwWeaponSlot;
	//SFile >> m_fRotX;
	//SFile >> m_fRotY;
	//SFile >> m_fRotZ;
	//SFile >> m_fRootX;
	//SFile >> m_fRootY;
	//SFile >> m_fRootZ;
	//SFile >> m_fRotX_F;
	//SFile >> m_fRotY_F;
	//SFile >> m_fRotZ_F;
	//SFile >> m_fRootX_F;
	//SFile >> m_fRootY_F;
	//SFile >> m_fRootZ_F;

	if ( strcmp( m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_bCPS = TRUE;
	}

	return TRUE;
}

BOOL CABLClass::LOAD_Ver101( basestream &SFile )
{
	DWORD dwDummy0;
	DWORD dwDummy1;

	SFile >> dwDummy0;
	SFile >> m_strAbf;
	SFile >> m_strCPS;
	SFile >> m_strSkeleton;
	SFile >> m_strBoneLink;
	SFile >> dwDummy1;
	SFile >> m_dwType;
	SFile >> m_dwWeaponSlot;
	/*SFile >> m_fRotX;
	SFile >> m_fRotY;
	SFile >> m_fRotZ;
	SFile >> m_fRootX;
	SFile >> m_fRootY;
	SFile >> m_fRootZ;
	SFile >> m_fRotX_F;
	SFile >> m_fRotY_F;
	SFile >> m_fRotZ_F;
	SFile >> m_fRootX_F;
	SFile >> m_fRootY_F;
	SFile >> m_fRootZ_F;*/

	if ( strcmp( m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_bCPS = TRUE;
	}

	return TRUE;
}

BOOL CABLClass::LoadFileNeo ( const char* szFile )
{
	Reset();

	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strSKINOBJ_ZIPFILE.c_str(), 
																	szPathName, 
																	szFile ) );

	if ( !pBStream.get() )
		return FALSE;
	basestream &SFile = *pBStream;


	DWORD dwVer;
	SFile >> dwVer;

	switch ( dwVer )
	{
	case VERSION:
		LOADNEO_Ver100( SFile );
		break;
	default:
		return FALSE;
	};

	return TRUE;
}
BOOL CABLClass::LoadFile( const char* szFile )
{
	Reset();

	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strSKINOBJ_ZIPFILE.c_str(), 
																	szPathName, 
																	szFile ) );

	if ( !pBStream.get() )
		return FALSE;
	basestream &SFile = *pBStream;


	DWORD dwVer;
	SFile >> dwVer;


	switch ( dwVer )
	{
	case VERSION:
		LOAD_Ver100( SFile );
		break;
	case 0x0101:
		LOAD_Ver101( SFile );
		break;
	default:
		return FALSE;
	};

	return TRUE;
}

void CABLClass::Reset()
{
	m_strAbf = "";
	m_strCPS = "";
	m_strSkeleton = "";
	m_strBoneLink = "";
	m_dwType = 0;
	m_dwWeaponSlot = 0;
	m_bCPS = false;
	m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_fRotZ = 0.0f;
	m_fRootX = 0.0f;
	m_fRootY = 0.0f;
	m_fRootZ = 0.0f;
	m_fRotX_F = 0.0f;
	m_fRotY_F = 0.0f;
	m_fRotZ_F = 0.0f;
	m_fRootX_F = 0.0f;
	m_fRootY_F = 0.0f;
	m_fRootZ_F = 0.0f;
}
