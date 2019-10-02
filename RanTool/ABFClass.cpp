#include "stdafx.h"

#include "ABFClass.h"
#include "../G-Logic/GLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CABFClass::CABFClass(void):
	m_dwRef(0),

	m_bWorldObj(FALSE),
	m_fScale(1.0f),
	m_vMax(7.f,20.f,7.f),
	m_vMin(-7.f,0.f,-7.f),
	m_fHeight(20.f),
	m_fRadius(7.f),
	m_dwBONE(0)
{
	for ( DWORD n=0; n<MAX_BONE; ++n )
	{
		m_fBONE1[n] = 0.0f;
		m_fBONE2[n] = 0.0f;
		m_fBONE3[n] = 0.0f;
		m_strBONE[n] = "";
	}
}

CABFClass::~CABFClass(void)
{
}

BOOL CABFClass::SaveFile ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << VERSION;
	SFile << PIECE_SIZE;
	
	for ( int i=0; i<PIECE_SIZE; ++i )
	{
		SFile << BOOL (!m_strPIECE[i].empty());
		if ( m_strPIECE[i].empty() )	continue;

		SFile << m_strPIECE[i];
	}

	SFile << m_strSkeleton;

	SFile << (DWORD)m_vecANIFILE.size();
	for ( size_t n=0; n<m_vecANIFILE.size(); ++n )
	{
		std::string strNAME = m_vecANIFILE[n].c_str();
		SFile << strNAME;
	}

	SFile << m_fScale;
	SFile << m_dwBONE;

	if ( m_dwBONE > MAX_BONE ) return FALSE;
	for ( i=0; i < (int)m_dwBONE ; ++i )
	{
		SFile << m_fBONE1[i];
		SFile << m_fBONE2[i];
		SFile << m_fBONE3[i];
		SFile << m_strBONE[i];
	}

	SFile << (BOOL) TRUE;
	SFile << m_vMax;
	SFile << m_vMin;

	SFile << (BOOL)TRUE;
	SFile << m_bWorldObj;

	SFile << (BOOL)TRUE;
	SFile << m_fHeight;
	SFile << m_fRadius;

	SFile << (BOOL)FALSE;

	return TRUE;
}

BOOL CABFClass::SaveFileOld ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << VERSION;

	int nOldSize = 9;
	SFile << nOldSize;
	for ( int i=0; i< nOldSize ; ++i )
	{
		SFile << BOOL (!m_strPIECE[i].empty());
		if ( m_strPIECE[i].empty() )	continue;

		SFile << m_strPIECE[i];
	}

	SFile << m_strSkeleton;

	SFile << (DWORD)m_vecANIFILE.size();
	for ( size_t n=0; n<m_vecANIFILE.size(); ++n )
	{
		std::string strNAME = m_vecANIFILE[n].c_str();
		SFile << strNAME;
	}

	SFile << m_fScale;
	SFile << m_dwBONE;

	if ( m_dwBONE > MAX_BONE ) return FALSE;
	for ( i=0; i < (int)m_dwBONE ; ++i )
	{
		SFile << m_fBONE1[i];
		SFile << m_fBONE2[i];
		SFile << m_fBONE3[i];
		SFile << m_strBONE[i];
	}

	SFile << (BOOL) TRUE;
	SFile << m_vMax;
	SFile << m_vMin;

	SFile << (BOOL)TRUE;
	SFile << m_bWorldObj;

	SFile << (BOOL)TRUE;
	SFile << m_fHeight;
	SFile << m_fRadius;

	SFile << (BOOL)FALSE;

	return TRUE;
}

BOOL CABFClass::LOAD_Ver100 ( basestream &SFile )
{

	DWORD dwPieceSize;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_SIZE )		return FALSE;

	BOOL bExit;
	for ( DWORD i=0; i<dwPieceSize; ++i )
	{
		SFile >> bExit;
		if ( !bExit )
		{
			m_strPIECE[i].clear();
			continue;
		}

		SFile >> m_strPIECE[i];
	}

	SFile >> m_strSkeleton;

	DWORD dwAniNum(0);
	SFile >> dwAniNum;

	m_vecANIFILE.clear();
	m_vecANIFILE.reserve ( dwAniNum );

	for ( DWORD i=0; i<dwAniNum; ++i )
	{
		std::string strANIFILE;
		SFile >> strANIFILE;

		m_vecANIFILE.push_back ( strANIFILE.c_str() );
	}

	SFile >> m_fScale;
	SFile >> m_dwBONE;

	if ( m_dwBONE > MAX_BONE ) return FALSE;

	for ( i=0; i < m_dwBONE ; ++i )
	{
		SFile >> m_fBONE1[i];
		SFile >> m_fBONE2[i];
		SFile >> m_fBONE3[i];
		SFile >> m_strBONE[i];
	}

	BOOL bBoundBox(FALSE);
	SFile >> bBoundBox;
	if ( bBoundBox )
	{
		SFile >> m_vMax;
		SFile >> m_vMin;
	}
	else
	{
		m_vMax = D3DXVECTOR3(7.f,20.f,7.f);
		m_vMin = D3DXVECTOR3(-7.f,0.f,-7.f);
	}

	BOOL bExist = FALSE;
	SFile >> bExist;
	if( bExist )	SFile >> m_bWorldObj;
	else			return TRUE;

	bExist = FALSE;
	SFile >> bExist;
	if( bExist )	
	{
		SFile >> m_fHeight;
		SFile >> m_fRadius;
	}
	else			return TRUE;

	SFile >> bExist;

	return TRUE;
}


BOOL CABFClass::LOAD_Ver100_PH ( basestream &SFile )
{

	DWORD dwPieceSize;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_SIZE )		return FALSE;

	BOOL bExit;
	for ( DWORD i=0; i<dwPieceSize; ++i )
	{
		SFile >> bExit;
		if ( !bExit )
		{
			m_strPIECE[i].clear();
			continue;
		}

		SFile >> m_strPIECE[i];
	}

	SFile >> m_strSkeleton;

	DWORD dwAniNum(0);
	SFile >> dwAniNum;

	m_vecANIFILE.clear();
	m_vecANIFILE.reserve ( dwAniNum );

	for ( DWORD i=0; i<dwAniNum; ++i )
	{
		std::string strANIFILE;
		SFile >> strANIFILE;

		m_vecANIFILE.push_back ( strANIFILE.c_str() );
	}

	SFile >> m_fScale;

	BOOL bExist = FALSE;

	bExist = FALSE;
	SFile >> bExist;
	if( bExist )	
	{
		SFile >> m_fHeight;
		SFile >> m_fRadius;
	}
	else			return TRUE;

	SFile >> m_dwBONE;

	if ( m_dwBONE > MAX_BONE ) return FALSE;

	for ( i=0; i < m_dwBONE ; ++i )
	{
		SFile >> m_fBONE1[i];
		SFile >> m_fBONE2[i];
		SFile >> m_fBONE3[i];
		SFile >> m_strBONE[i];
	}

	BOOL bBoundBox(FALSE);
	SFile >> bBoundBox;
	if ( bBoundBox )
	{
		SFile >> m_vMax;
		SFile >> m_vMin;
	}
	else
	{
		m_vMax = D3DXVECTOR3(7.f,20.f,7.f);
		m_vMin = D3DXVECTOR3(-7.f,0.f,-7.f);
	}


	SFile >> bExist;
	if( bExist )	SFile >> m_bWorldObj;
	else			return TRUE;

	SFile >> bExist;

	return TRUE;
}


BOOL CABFClass::LoadFile ( const char* szFile )
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

	m_fHeight = 20.f;
	m_fRadius = 7.f;

	DWORD dwVer;
	SFile >> dwVer;

	switch ( dwVer )
	{
	case VERSION:
		LOAD_Ver100( SFile );
		break;
	default:
		return FALSE;
	};

	return TRUE;
}

BOOL CABFClass::LoadFile_PH ( const char* szFile )
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

	m_fHeight = 20.f;
	m_fRadius = 7.f;

	DWORD dwVer;
	SFile >> dwVer;

	switch ( dwVer )
	{
	case VERSION:
		LOAD_Ver100_PH( SFile );
		break;
	default:
		return FALSE;
	};

	return TRUE;
}


void CABFClass::Reset()
{
	m_bWorldObj		= FALSE;
	m_fScale		= 0.0f;
	m_vMax.x		= 0.0f;
	m_vMax.y		= 0.0f;
	m_vMax.z		= 0.0f;
	m_vMin.x		= 0.0f;
	m_vMin.y		= 0.0f;
	m_vMin.z		= 0.0f;
	m_fHeight		= 0.0f;
	m_fRadius		= 0.0f;
	m_dwBONE		= 0;

	for ( DWORD n=0; n<MAX_BONE; ++n )
	{
		m_fBONE1[n] = 0.0f;
		m_fBONE2[n] = 0.0f;
		m_fBONE3[n] = 0.0f;
		m_strBONE[n] = "";
	}

	for ( DWORD n=0; n<PIECE_SIZE; ++n )
	{
		m_strPIECE[n] = "";
	}
	m_vecANIFILE.clear();
	m_strANINAME = "";
	m_strSkeleton = "";
}
