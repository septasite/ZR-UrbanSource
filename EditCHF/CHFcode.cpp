#include "stdafx.h"

#include "CHFcode.h"
#include "PieceDefine.h"
#include "../G-Logic/GLogic.h"

#include "StringUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChfCode::CChfCode(void):
	m_fVal(0.0f),
	//b_usePIECE(TRUE),
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

CChfCode::~CChfCode(void)
{
}

BOOL CChfCode::SaveFile ( const char* szFile)
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinCharDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << VERSION;

	SFile << PIECE_NSIZE;
	for ( int i=0; i<PIECE_NSIZE; ++i )
	{
		SFile << BOOL (!m_strPIECE[i].empty()); //bStatus;
		if ( m_strPIECE[i].empty() )	continue;

		//std::string strPieceFile = m_pPieceArray[i]->m_szFileName;
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

	for ( i=0; i < m_dwBONE ; ++i )
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

BOOL CChfCode::LOAD_Ver100 ( basestream &SFile )
{
	DWORD dwPieceSize;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_NSIZE )		return FALSE;

	//	Note : 조각들 로드.
	//
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

	//	Note : 본파일 읽기.
	SFile >> m_strSkeleton;

	//	Note :에니메이션 읽기.

	DWORD dwAniNum(0);
	SFile >> dwAniNum;

	m_vecANIFILE.clear();
	m_vecANIFILE.reserve ( dwAniNum );

	for ( DWORD i=0; i<dwAniNum; ++i )
	{
		//std::string strANIFILE;
		SFile >> m_strANINAME;
		CString	strCfgName;

		STRUTIL::ChangeExt ( m_strANINAME.c_str(), ".x", strCfgName, ".cfg" );

		m_vecANIFILE.push_back ( strCfgName.GetString() );
	}

	//	Note : 바운드 박스 정보 로드.
	//
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

BOOL CChfCode::LOAD_Ver101( basestream &SFile )
{
	DWORD dwPieceSize;

	SFile >> m_fScale;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_NSIZE )		return FALSE;

	//	Note : 조각들 로드.
	//
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

	//	Note : 본파일 읽기.
	//
	SFile >> m_strSkeleton;

	//	Note :에니메이션 읽기.
	//
	DWORD dwAniNum(0);
	SFile >> dwAniNum;

	m_vecANIFILE.clear();
	m_vecANIFILE.reserve ( dwAniNum );

	for ( DWORD i=0; i<dwAniNum; ++i )
	{
		//std::string strANIFILE;
		SFile >> m_strANINAME;
		CString	strCfgName;

		STRUTIL::ChangeExt ( m_strANINAME.c_str(), ".x", strCfgName, ".cfg" );

		m_vecANIFILE.push_back ( strCfgName.GetString() );
	}

	//	Note : 바운드 박스 정보 로드.
	//
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

	// Note : 덤프
	SFile >> bExist;

	return TRUE;
}

BOOL CChfCode::LOAD_Ver103( basestream &SFile )
{
	DWORD dwPieceSize;

	//SFile >> m_fScale;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_NSIZE )		return FALSE;

	//	Note : ??? ??.
	//
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

	//	Note : ??? ??.
	//
	SFile >> m_strSkeleton;

	//	Note :????? ??.
	//
	DWORD dwAniNum(0);
	SFile >> dwAniNum;

	m_vecANIFILE.clear();
	m_vecANIFILE.reserve ( dwAniNum );

	for ( DWORD i=0; i<dwAniNum; ++i )
	{
		//std::string strANIFILE;
		SFile >> m_strANINAME;
		CString	strCfgName;

		STRUTIL::ChangeExt ( m_strANINAME.c_str(), ".x", strCfgName, ".cfg" );

		m_vecANIFILE.push_back ( strCfgName.GetString() );
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

	//	Note : ??? ?? ?? ??.
	//
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

	// Note : ??
	SFile >> bExist;

	return TRUE;
}

BOOL CChfCode::LOAD_Ver104( basestream &SFile )
{
	DWORD dwPieceSize;

	//SFile >> m_fScale;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_NSIZE )		return FALSE;

	//	Note : ??? ??.
	//
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

	//	Note : ??? ??.
	//
	SFile >> m_strSkeleton;

	//	Note :????? ??.
	//
	DWORD dwAniNum(0);
	SFile >> dwAniNum;

	m_vecANIFILE.clear();
	m_vecANIFILE.reserve ( dwAniNum );

	for ( DWORD i=0; i<dwAniNum; ++i )
	{
		//std::string strANIFILE;
		SFile >> m_strANINAME;
		CString	strCfgName;

		STRUTIL::ChangeExt ( m_strANINAME.c_str(), ".x", strCfgName, ".cfg" );

		m_vecANIFILE.push_back ( strCfgName.GetString() );
	}

	SFile >> m_fScale;

	BOOL bExist = FALSE;
	SFile >> bExist;
	if( bExist )	
	{
		SFile >> m_fHeight;
		SFile >> m_fRadius;
	}
	else			return TRUE;

	SFile >> m_dwBONE;

	DWORD dwZero[MAX_BONE];
	DWORD dwSize[MAX_BONE];
	DWORD dwSize2[MAX_BONE];

	if ( m_dwBONE > MAX_BONE ) return FALSE;

	for ( i=0; i < m_dwBONE ; ++i )
	{
		SFile >> m_fBONE1[i];
		SFile >> m_fBONE2[i];
		SFile >> m_fBONE3[i];
		SFile >> dwZero[i];
		SFile.ReadBuffer ( &m_strBONE[i], sizeof(m_strBONE[i])*SIZE_NAME );
		SFile >> dwSize[i];
		SFile >> dwSize2[i];
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

BOOL CChfCode::LOAD_Ver106( basestream &SFile )
{
	DWORD dwPieceSize;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_NSIZE )		return FALSE;

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
		//std::string strANIFILE;
		SFile >> m_strANINAME;
		CString	strCfgName;

		STRUTIL::ChangeExt ( m_strANINAME.c_str(), ".x", strCfgName, ".cfg" );

		m_vecANIFILE.push_back ( strCfgName.GetString() );
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

BOOL CChfCode::LOAD_Ver107( basestream &SFile )
{
	DWORD dwPieceSize;
	SFile >> dwPieceSize;
	if ( dwPieceSize > PIECE_NSIZE )		return FALSE;

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
		//std::string strANIFILE;
		SFile >> m_strANINAME;

		m_vecANIFILE.push_back ( m_strANINAME.c_str() );
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

BOOL CChfCode::LoadFile ( const char* szFile )
{
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
	//added by geger009 | 13-9-2012 | add new version for chf
		LOAD_Ver107( SFile );
		break;
	case 0x0106:
		LOAD_Ver106( SFile );
		break;
	case 0x0105:
	case 0x0104:
		LOAD_Ver104( SFile );
		break;
	case 0x0103:
	//added by geger009 | 18-7-2012 | Add ABL and ABF code
		LOAD_Ver103( SFile );
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