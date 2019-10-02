#include "stdafx.h"
#include "CHFClass.h"
#include "../G-Logic/GLogic.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCHFClass::CCHFClass(void):
	m_fVal(0.0f),
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

CCHFClass::~CCHFClass(void)
{
}

BOOL CCHFClass::SaveFile ( const char* szFile)
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinCharDataContainer::GetInstance().GetPath() );
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
	SFile << m_fVal;
	SFile << (BOOL)TRUE;
	SFile << m_fHeight;
	SFile << m_fRadius;
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
	SFile << (BOOL)FALSE;

	return TRUE;
}

BOOL CCHFClass::SaveFileOld ( const char* szFile)
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinCharDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << VERSION_SAVE;
	SFile << m_fScale;

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

BOOL CCHFClass::LOAD_Ver100 ( basestream &SFile )
{
	DWORD dwPieceSize;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_SIZE )		return FALSE;

	BOOL bExit;
	char szPIECE[PIECE_SIZE][MAX_PATH] = {0};
	memset ( szPIECE, 0, sizeof(char)*PIECE_SIZE*MAX_PATH );
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

	char szSkeleton[MAX_PATH] = "";
	SFile.ReadBuffer ( szSkeleton, sizeof(char)*MAX_PATH );
	m_strSkeleton = szSkeleton;

	char szAniName[ACF_SZNAME] = "";

	DWORD dwLenght;
	SFile >> dwLenght;

	m_vecANIFILE.clear();
	m_vecANIFILE.reserve(dwLenght);

	for ( DWORD i=0; i<dwLenght; ++i )
	{
		SFile.ReadBuffer ( szAniName, sizeof(char)*ACF_SZNAME );
		m_vecANIFILE.push_back ( szAniName );
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
	return TRUE;
}

BOOL CCHFClass::LOAD_Ver101( basestream &SFile )
{
	DWORD dwPieceSize;

	SFile >> m_fScale;
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


BOOL CCHFClass::LOAD_Ver104( basestream &SFile )
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

BOOL CCHFClass::LOAD_Ver106( basestream &SFile )
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
	//
	BOOL bExist = FALSE;
	bExist = FALSE;
	SFile >> bExist;
	if( bExist )	
	{
		SFile >> m_fHeight;
		SFile >> m_fRadius;
	}
	else			return TRUE;

	SFile >> m_fVal;

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

BOOL CCHFClass::LOAD_Ver107( basestream &SFile )
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

	std::string strANIFILE;
	CString strCfgFile, strTEMP;

	for ( DWORD i=0; i<dwAniNum; ++i )
	{
		SFile >> strANIFILE;

		strTEMP = strANIFILE.c_str();
		int nIndex = strTEMP.ReverseFind ( '.' );
		strCfgFile = strTEMP.Left(nIndex) + ".x";
		m_vecANIFILE.push_back ( strCfgFile.GetString() );
	}

	SFile >> m_fScale;

	SFile >> m_fVal;

	BOOL bExist = FALSE;
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

	bExist = FALSE;
	SFile >> bExist;
	if( bExist )	SFile >> m_bWorldObj;
	else			return TRUE;

	SFile >> bExist;

	return TRUE;
}

BOOL CCHFClass::LoadFile ( const char* szFile )
{
	Reset();

	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinCharDataContainer::GetInstance().GetPath() );
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
		LOAD_Ver107( SFile );
		break;
	case 0x0106:
		LOAD_Ver106( SFile );
		break;
	case 0x0105:
	case 0x0104:
		LOAD_Ver104( SFile );
		break;
	case 0x0102:
	case 0x0101:
		LOAD_Ver101( SFile );
		break;
	case 0x0100:
		LOAD_Ver100( SFile );
		break;
	default:
		return FALSE;
	};

	return TRUE;
}

void CCHFClass::Reset()
{
	m_fVal			= 0.0f;
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
