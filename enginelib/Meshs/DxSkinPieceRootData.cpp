#include "stdafx.h"
#include "../Common/SerialFile.h"

#include "../G-Logic/GLogic.h"

#include "DxSkinPieceRootData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DxSkinPieceRootData::DxSkinPieceRootData(void):
	m_dwType(0)
	,m_dwWeaponSlot(0)

	,m_bCPS(FALSE)

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	,m_vRot(0,0,0)
	,m_vRoot(0,0,0)
	,m_vScale(1,1,1)
	,m_vRot_F(0,0,0)
	,m_vRoot_F(0,0,0)
	,m_vScale_F(1,1,1)
{
	memset( m_szFileName, 0, FILE_LENGTH );
	m_strAbf = "";
	m_strCPS = "";
	m_strSkeleton = "";
	m_strBoneLink = "";
}

DxSkinPieceRootData::~DxSkinPieceRootData(void)
{
	//DxSkinPieceDataContainer::GetInstance().CleanUp();
	//ClearAll();
}

HRESULT DxSkinPieceRootData::ClearAll ()
{
	SAFE_DELETE( m_pSkinPieceData );
	DxSkinPieceDataContainer::GetInstance().CleanUp();
	return S_OK;
}

BOOL DxSkinPieceRootData::SaveFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice )
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

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	SFile << m_vRoot;
	SFile << m_vRot;
	SFile << m_vScale;
	SFile << m_vRoot_F;
	SFile << m_vRot_F;
	SFile << m_vScale_F;

	return TRUE;
}

BOOL DxSkinPieceRootData::LOAD_Ver100( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice )
{
	/*
	SFile >> m_strAbf;
	//âËÅ´ä¿Åì CPS
	SFile >> m_strCPS;
	//âËÅ´¡ÃÐ´Ù¡
	SFile >> m_strSkeleton;
	//âËÅ´ª×èÍ¢éÍµèÍ¡ÃÐ´Ù¡
	SFile >> m_strBoneLink;
	//µÓáË¹è§¢Í§ Piece
	SFile >> m_dwType;
	SFile >> m_dwWeaponSlot;

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	// read old neo
	SFile >> m_vRot;
	SFile >> m_vRoot;
	//SFile >> m_vScale;
	SFile >> m_vRot_F;
	SFile >> m_vRoot_F;
	//SFile >> m_vScale_F;

	*/

	DWORD dwDummy;

	SFile >> dwDummy;
	SFile >> m_strAbf;
	SFile >> m_strCPS;
	SFile >> m_strSkeleton;
	SFile >> m_strBoneLink;
	SFile >> dwDummy;
	SFile >> m_dwType;
	SFile >> m_dwWeaponSlot;

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	SFile >> m_vRoot;
	SFile >> m_vRot;
	SFile >> m_vScale;
	SFile >> m_vRoot_F;
	SFile >> m_vRot_F;
	SFile >> m_vScale_F;


return TRUE;
}

BOOL DxSkinPieceRootData::LOAD_Ver101( basestream &SFile, LPDIRECT3DDEVICEQ pd3dDevice )
{
	DWORD dwDummy;

	SFile >> dwDummy;
	SFile >> m_strAbf;
	SFile >> m_strCPS;
	SFile >> m_strSkeleton;
	SFile >> m_strBoneLink;
	SFile >> dwDummy;
	SFile >> dwDummy;
	SFile >> m_dwType;
	SFile >> m_dwWeaponSlot;

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	SFile >> m_vRoot;
	SFile >> m_vRot;
	SFile >> m_vScale;
	SFile >> m_vRoot_F;
	SFile >> m_vRot_F;
	SFile >> m_vScale_F;

return TRUE;
}

BOOL DxSkinPieceRootData::LoadFile ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, bool bREPRESH )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinPieceDataContainer::GetInstance().GetPath() );
	StringCchCat( szPathName, MAX_PATH, szFile );

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strSKINOBJ_ZIPFILE.c_str(), 
																	szPathName, 
																	szFile ) );
	CString strFindExtenstion = "";
	strFindExtenstion.Format("%s",szFile);
	int CheckABL = strFindExtenstion.Find(_T('.abl'));
	if ( CheckABL == -1 ) return false;

	if ( !pBStream.get() )
		return FALSE;
	basestream &SFile = *pBStream;


	DWORD dwVer;
	SFile >> dwVer;


	switch ( dwVer )
	{
	case VERSION:
		LOAD_Ver101( SFile, pd3dDevice );
		break;
	case VERSIONOLD:
		LOAD_Ver100( SFile, pd3dDevice );
		break;
	default:
		return FALSE;
	};

	DxSkinPieceData* pCharData;

	m_pSkeleton = DxBoneCollector::GetInstance().Load ( m_strSkeleton.c_str(), pd3dDevice );
	
	if ( !m_pSkeleton )		return FALSE;
	
	DxBoneTrans* pBone;
	pBone = new DxBoneTrans;
	
	pBone = m_pSkeleton->FindBone( m_strBoneLink.c_str() );
	if ( !pBone ) return FALSE;

	pCharData = new DxSkinPieceData;
	pCharData = DxSkinPieceDataContainer::GetInstance().LoadData( m_strAbf.c_str() , pd3dDevice , true );
	if ( !pCharData )
	{
		SAFE_DELETE(pCharData);
		CDebugSet::ToLogFile( "Load ABF File : %s Fail",m_strAbf.c_str() );
		return FALSE;
	}

	if ( strcmp( m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_bCPS = TRUE;
	}
	
	pCharData->m_strAbf2 = m_strAbf;
	pCharData->m_strCPS2 = m_strCPS;
	pCharData->m_strSkeleton2 = m_strSkeleton;
	pCharData->m_strBoneLink2 = m_strBoneLink;

	pCharData->m_bCPS = m_bCPS;

	pCharData->m_dwType = m_dwType;
	pCharData->m_dwWeaponSlot = m_dwWeaponSlot;

	// Ramispo 14-12-2013 Fix ABL Position & Scale
	pCharData->m_vRoot = m_vRoot;
	pCharData->m_vRot = m_vRot;
	pCharData->m_vScale = m_vScale;
	pCharData->m_vRoot_F = m_vRoot_F;
	pCharData->m_vRot_F = m_vRot_F;
	pCharData->m_vScale_F = m_vScale_F;

	pCharData->m_dwRef++;

	StringCchCopy( m_szFileName, FILE_LENGTH, szFile );

	m_pSkinPieceData = pCharData;

	return TRUE;
}

// Container!!!!!!!!!!!!!!!!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\=======================

DxSkinPieceRootDataContainer::DxSkinPieceRootDataContainer ()
{
	memset( m_szPath, 0, sizeof(char)*MAX_PATH );
}

DxSkinPieceRootDataContainer::~DxSkinPieceRootDataContainer ()
{
	//CleanUp();
}

DxSkinPieceRootDataContainer& DxSkinPieceRootDataContainer::GetInstance()
{
	static DxSkinPieceRootDataContainer Instance;
	return Instance;
}

HRESULT DxSkinPieceRootDataContainer::CleanUp ()
{
	SKINPIECEROOTDATAMAP_ITER iter = m_mapSkinRootData.begin ();
	SKINPIECEROOTDATAMAP_ITER iterEnd = m_mapSkinRootData.end ();
	
	for ( ; iter!=iterEnd; iter++ )
	{
		delete (*iter).second;
	}

	m_mapSkinRootData.clear ();

	return S_OK;
}

DxSkinPieceRootData* DxSkinPieceRootDataContainer::FindData ( const char* szFile )
{
	CString strTemp;
	strTemp.Format( "%s",szFile );

	SKINPIECEROOTDATAMAP_ITER iter = m_mapSkinRootData.find ( strTemp );
	if ( iter != m_mapSkinRootData.end() )
	{
		//CDebugSet::ToLogFile( "Find %s Found %s",strTemp.GetString(),iter->first.GetString() );
		return iter->second;
	}

	return NULL;
}

BOOL DxSkinPieceRootDataContainer::DeleteData ( const char* szFile )
{
	CString strTemp;
	strTemp.Format( "%s",szFile );

	SKINPIECEROOTDATAMAP_ITER iter = m_mapSkinRootData.find ( strTemp );
	if ( iter == m_mapSkinRootData.end() )	return FALSE;

	delete (*iter).second;
	m_mapSkinRootData.erase ( iter );

	return TRUE;
}

void DxSkinPieceRootDataContainer::ReleaseData ( const char* szFile )
{
	DxSkinPieceRootData* pRes = FindData ( szFile );
	if ( !pRes )	return;
	
	if ( pRes->GetData()->m_dwRef<=1 )
	{
		DeleteData ( szFile );
		return;
	}

	pRes->GetData()->m_dwRef--;
	return;
}

DxSkinPieceRootData* DxSkinPieceRootDataContainer::LoadData( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread )
{
	if ( !szFile ) return NULL;
	if ( strlen(szFile) == 0 ) return NULL;

	//CDebugSet::ToLogFile("ABL Load %s ",szFile);

	DxSkinPieceRootData* pRootData;

	pRootData = FindData( szFile );
	if ( pRootData )
	{
		//CDebugSet::ToLogFile( "Find %s",szFile );
		pRootData->GetData()->m_dwRef++;
		return pRootData;
	}

	pRootData = new DxSkinPieceRootData;
	BOOL bOk = pRootData->LoadFile( szFile, pd3dDevice, bThread );
	if ( !bOk )
	{
		//CDebugSet::ToLogFile("ABL Error Load %s",szFile);
		SAFE_DELETE(pRootData);
		return NULL;
	}
	pRootData->GetData()->m_dwRef++;

	CString strTemp;
	strTemp.Format( "%s",szFile );
	//CDebugSet::ToLogFile( "Save To %s",strTemp.GetString() );

	//m_mapSkinRootData.insert(std::pair<CString, DxSkinPieceRootData*>(strTemp,pRootData));
	m_mapSkinRootData[ strTemp ] = pRootData;

	//CDebugSet::ToLogFile("ABL Load %s Done",szFile);

	return pRootData;
}