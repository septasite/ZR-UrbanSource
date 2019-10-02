#include "stdafx.h"
#include "../Common/SerialFile.h"
#include "../DxCommon/EDITMESHS.h"

#include "../G-Logic/GLogic.h"
#include "DxSkinPieceContainer.h"

#include "SAnimation.h"

#include "DxSkinVehicleData.h"

#include "DxSkinPieceData.h"
#include "DxSkinPieceRootData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DxSkinVehicleData::DxSkinVehicleData(void) :
	m_dwRef(0),

	m_fScale(1.0f),
	m_vRotation_Font(1.f,1.f,1.f),
	m_vTransform_Font(1.f,1.f,1.f),
	m_vRotation_Back(1.f,1.f,1.f),
	m_vTransform_Back(1.f,1.f,1.f),
	m_dwBONE(0)
{
	memset( m_szFileName, 0, FILE_LENGTH );

	m_strChar_Font = "";
	m_strChar_Back = "";

	for ( int i=0; i<PIECE_SIZE; ++i )
	{
		m_pPieceArray[i] = NULL;
		m_pSkinCharPiece[i] = NULL;
		m_strBoneLink[i] = "";
		m_dwWeaponSlot[i] = 0;
		m_dwPieceType[i] = 0;
	}
	for ( DWORD n=0; n<MAX_BONE; ++n )
	{
		m_fBONE1[n] = 0.0f;
		m_fBONE2[n] = 0.0f;
		m_fBONE3[n] = 0.0f;
		m_strBONE[n] = "";
	}
}

DxSkinVehicleData::~DxSkinVehicleData(void)
{
	m_dwBONE = 0;
	ClearAll ();
}

HRESULT DxSkinVehicleData::ClearAll ()
{
	m_dwRef = 0;
	m_fScale = 1.0f;

	m_vecANIFILE.clear();

	for ( int i=0; i<PIECE_SIZE; ++i )
	{
		if ( m_pPieceArray[i] )
		{
			DxSkinPieceContainer::GetInstance().ReleasePiece ( m_pPieceArray[i]->m_szFileName );
		}
		m_pPieceArray[i] = NULL;
		m_pSkinCharPiece[i] = NULL;
		m_strBoneLink[i] = "";
		m_dwWeaponSlot[i] = 0;
		m_dwPieceType[i] = 0;
	}

	DxSkinAniControl::ClearAll ();

	return S_OK;
}

HRESULT DxSkinVehicleData::SetPiece ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, DWORD dwFlag )
{
	if ( dwFlag&FG_MUSTNEWLOAD )
	{
		for ( int i=0; i<PIECE_SIZE; ++i )
		{
			if ( m_pPieceArray[i] && m_pPieceArray[i]->m_szFileName )
			{
				if ( !strcmp(m_pPieceArray[i]->m_szFileName,szFile) )
				{
					m_pPieceArray[i] = NULL;
				}
			}
		}

		DxSkinPieceContainer::GetInstance().DeletePiece ( szFile );
	}
	for ( int i=0; i<PIECE_SIZE; ++i )
	{
		m_pSkinCharPiece[i] = NULL;
		m_strBoneLink[i] = "";
		m_dwWeaponSlot[i] = 0;
		m_dwPieceType[i] = 0;
	}

	DxSkinPiece* pSkinPiece = DxSkinPieceContainer::GetInstance().LoadPiece( szFile, pd3dDevice, bThread );
	if ( !pSkinPiece )	return E_FAIL;

	if ( dwFlag&FG_BONEFILE_CHECK )
	{
		if ( pSkinPiece->m_pmcMesh->pSkinInfo )
		{
			CString strFile1( m_strSkeleton.c_str() );
			strFile1.MakeLower();

			CString strFile2( pSkinPiece->m_szSkeleton );
			strFile2.MakeLower();

			if( _tcscmp(strFile1.GetString(),strFile2.GetString()) != 0 )
			{
				CDebugSet::ToLogFile( "Bone ºÒÀÏÄ¡ %s, %s", strFile1.GetString(), strFile2.GetString() );
				return E_DIFFERENT_BONEFILE;
			}
		}
	}

	if ( m_pPieceArray[pSkinPiece->m_emType] )
	{
		DxSkinPieceContainer::GetInstance().ReleasePiece ( szFile );
	}

	m_pPieceArray[pSkinPiece->m_emType] = pSkinPiece;

	return S_OK;
}

void DxSkinVehicleData::ResetPiece ( LPDIRECT3DDEVICEQ pd3dDevice, int i )
{
	GASSERT(i<PIECE_SIZE);

	PDXSKINPIECE pSkinPiece = GetPiece (i);
	
	if ( pSkinPiece )
	{
		DxSkinPieceContainer::GetInstance().ReleasePiece ( pSkinPiece->m_szFileName );
		m_pPieceArray[i] = NULL;
		m_pSkinCharPiece[i] = NULL;
		m_strBoneLink[i] = "";
		m_dwWeaponSlot[i] = 0;
		m_dwPieceType[i] = 0;
	}
}

BOOL DxSkinVehicleData::SaveFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice )
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
		SFile << BOOL(m_pPieceArray[i]!=NULL);
		if ( !m_pPieceArray[i] )	continue;

		std::string strPieceFile = m_pPieceArray[i]->m_szFileName;
		SFile << strPieceFile;
	}

	SFile << m_strSkeleton;

	SFile << DxSkinAniControl::GETANIAMOUNT();
	
	for ( size_t n=0; n<m_vecAnim.size(); ++n )
	{
		std::string strNAME = m_vecAnim[n]->pAnimCont->m_szName;
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

	SFile << m_vRotation_Font;
	SFile << m_vTransform_Font;
	SFile << m_strChar_Font;

	SFile << m_vRotation_Back;
	SFile << m_vTransform_Back;
	SFile << m_strChar_Back;

	StringCchCopy( m_szFileName, FILE_LENGTH, szFile );

	return TRUE;
}

BOOL DxSkinVehicleData::LOAD_Ver100( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice )
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
		CString strCfgFile, strTEMP;

		SFile >> strANIFILE;

		strTEMP = strANIFILE.c_str();
		int nIndex = strTEMP.ReverseFind ( '.' );
		strCfgFile = strTEMP.Left(nIndex) + ".x";
		m_vecANIFILE.push_back ( strCfgFile.GetString() );
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

BOOL DxSkinVehicleData::LoadFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, bool bREPRESH )
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
		LOAD_Ver100( SFile, pd3dDevice );
		break;
	default:
		return FALSE;
	};

	m_pSkeleton = DxBoneCollector::GetInstance().Load ( m_strSkeleton.c_str(), pd3dDevice );
	if ( !m_pSkeleton )		return FALSE;

	DWORD i;
	for ( i=0; i<PIECE_SIZE; ++i )
	{
		if ( !m_strPIECE[i].empty() )
		{
			m_pSkinCharPiece[i] = NULL;
			DxSkinPieceRootData* pPieceDataRoot;
			pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( m_strPIECE[i].c_str() , pd3dDevice, bThread );
			if ( pPieceDataRoot )
			{
				if ( pPieceDataRoot->GetUseCPS() )
				{
					SetPiece ( pPieceDataRoot->GetCpsName().c_str() , pd3dDevice, bThread );
				}
				DxSkinPieceData* pSkinCharPiece = pPieceDataRoot->GetData();
				m_pSkinCharPiece[i] = new DxSkinCharPiece;
				m_pSkinCharPiece[i]->SetCharData ( pSkinCharPiece, pd3dDevice, TRUE );
				m_strBoneLink[i] = pPieceDataRoot->GetBoneLink();
				m_dwWeaponSlot[i] = pPieceDataRoot->GetWeaponSlot();
				m_dwPieceType[i] = pPieceDataRoot->GetType();
			}else{
				SetPiece ( m_strPIECE[i].c_str(), pd3dDevice, bThread );
			}
		}
	}

	for ( i=0; i<(DWORD)m_vecANIFILE.size(); ++i )
	{
		//DxSkinAniControl::LoadAnimation ( m_vecANIFILE[i].c_str(), pd3dDevice, bREPRESH , true ); //GodThem test
		DxSkinAniControl::LoadAnimation ( m_vecANIFILE[i].c_str(), pd3dDevice, bREPRESH  );
	}

	DxSkinAniControl::ClassifyAnimation ();

	DxSkinAniControl::SELECTANI ( AN_GUARD_N );

	if ( !DxSkinAniControl::GETCURANIMNODE() )
	{
		CDebugSet::ToLogFile ( "select ani fail %s", szFile );
	}

	StringCchCopy( m_szFileName, FILE_LENGTH, szFile );

	return TRUE;
}

// ================================================================================
// Container >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ================================================================================
DxSkinVehicleDataContainer::DxSkinVehicleDataContainer ()
{
	memset( m_szPath, 0, sizeof(char)*MAX_PATH );
}

DxSkinVehicleDataContainer::~DxSkinVehicleDataContainer ()
{
}
DxSkinVehicleDataContainer& DxSkinVehicleDataContainer::GetInstance()
{
	static DxSkinVehicleDataContainer Instance;
	return Instance;
}

HRESULT DxSkinVehicleDataContainer::CleanUp ()
{
	SKINCHARDATAMAP_ITER iter = m_mapSkinCharData.begin ();
	SKINCHARDATAMAP_ITER iterEnd = m_mapSkinCharData.end ();
	
	for ( ; iter!=iterEnd; iter++ )
	{
		delete (*iter).second;
	}

	m_mapSkinCharData.clear ();

	return S_OK;
}

DxSkinVehicleData* DxSkinVehicleDataContainer::FindData ( const char* szFile )
{
	SKINCHARDATAMAP_ITER iter = m_mapSkinCharData.find ( std::string(szFile) );
	if ( iter != m_mapSkinCharData.end() )	return iter->second;

	return NULL;
}

BOOL DxSkinVehicleDataContainer::DeleteData ( const char* szFile )
{
	SKINCHARDATAMAP_ITER iter = m_mapSkinCharData.find ( std::string(szFile) );
	if ( iter == m_mapSkinCharData.end() )	return FALSE;

	delete (*iter).second;
	m_mapSkinCharData.erase ( iter );

	return TRUE;
}

void DxSkinVehicleDataContainer::ReleaseData ( const char* szFile )
{
	DxSkinVehicleData* pRes = FindData ( szFile );
	if ( !pRes )	return;
	
	if ( pRes->m_dwRef<=1 )
	{
		DeleteData ( szFile );
		return;
	}

	pRes->m_dwRef--;
	return;
}

DxSkinVehicleData* DxSkinVehicleDataContainer::LoadData( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread )
{
	DxSkinVehicleData* pCharData;

	pCharData = FindData( szFile );
	if ( pCharData )
	{
		pCharData->m_dwRef++;
		return pCharData;
	}

	pCharData = new DxSkinVehicleData;
	BOOL bOk = pCharData->LoadFile( szFile, pd3dDevice, bThread );
	if ( !bOk )
	{
		SAFE_DELETE(pCharData);
		return NULL;
	}
	pCharData->m_dwRef++;

	CDebugSet::ToListView ( "DxSkinVehicleData::LoadFile, %s", szFile );

	m_mapSkinCharData[std::string( szFile )] = pCharData;

	return pCharData;
}