#include "stdafx.h"

#include "VCFcode.h"
#include "../G-Logic/GLogic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVcfCode::CVcfCode(void):
	m_fScale(1.0f),
	m_vRotation_Font(1.f,1.f,1.f),
	m_vTransform_Font(1.f,1.f,1.f),
	m_vRotation_Back(1.f,1.f,1.f),
	m_vTransform_Back(1.f,1.f,1.f),
	m_dwBONE(0)

{
	m_strChar_Font = "";
	m_strChar_Back = "";

	for ( DWORD n=0; n<MAX_BONE; ++n )
	{
		m_fBONE1[n] = 0.0f;
		m_fBONE2[n] = 0.0f;
		m_fBONE3[n] = 0.0f;
		m_strBONE[n] = "";
	}
}

CVcfCode::~CVcfCode(void)
{
}

BOOL CVcfCode::SaveFile ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinVehicleDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << VERSION;

	SFile << PIECE_SIZE;
	for ( int i=0; i<PIECE_SIZE; ++i )
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

	SFile << m_dwBONE;

	if ( m_dwBONE > MAX_BONE ) return FALSE;

	for ( i=0; i < m_dwBONE ; ++i )
	{
		SFile << m_fBONE1[i];
		SFile << m_fBONE2[i];
		SFile << m_fBONE3[i];
		SFile << m_strBONE[i];
	}

	SFile << m_vRotation_Font;
	SFile << m_vTransform_Font;
	SFile << m_strChar_Font;

	SFile << m_vRotation_Back;
	SFile << m_vTransform_Back;
	SFile << m_strChar_Back;

	return TRUE;
}

BOOL CVcfCode::LOAD_Ver100 ( basestream &SFile )
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
		//std::string strANIFILE;
		SFile >> m_strANINAME;

		m_vecANIFILE.push_back ( m_strANINAME.c_str() );
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

	SFile >> m_vRotation_Font;
	SFile >> m_vTransform_Font;
	SFile >> m_strChar_Font;

	SFile >> m_vRotation_Back;
	SFile >> m_vTransform_Back;
	SFile >> m_strChar_Back;

	return TRUE;
}

BOOL CVcfCode::LoadFile ( const char* szFile )
{ 
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinVehicleDataContainer::GetInstance().GetPath() );
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
	default:
		return FALSE;
	};

	return TRUE;
}

