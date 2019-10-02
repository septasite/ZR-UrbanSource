#include "stdafx.h"
#include "CnvClass.h"
#include "GLOGIC.h"
#include "Crypt.h"


#include <algorithm>
#include "../Common/stlfunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const TCHAR BinManager::szFILETYPE[] = _T("AnimContainer");

HRESULT InnerBin::SaveToFile ( CSerialFile &SFile )
{
	SFile << VERSION_BIN_INNER_SAVE;
	SFile << m_strBone;

	SFile << m_cRotateKeys;
	if ( m_cRotateKeys>0 )
	{
		SFile.WriteBuffer ( m_pRotateKeys, sizeof(BSRotateKey)*m_cRotateKeys );
	}

	SFile << m_cPositionKeys;
	if ( m_cPositionKeys>0 )
	{
		SFile.WriteBuffer ( m_pPositionKeys, sizeof(BSPositionKey)*m_cPositionKeys );
	}

	DWORD dwGabageData = (DWORD)m_strBone.length();
	SFile << dwGabageData;

	SFile << m_cQuatPosKeys;
	if ( m_cQuatPosKeys>0 )
	{
		SFile.WriteBuffer ( m_pQuatPosKeys, sizeof(BSQuatPosKey)*m_cQuatPosKeys );
	}

	dwGabageData = (DWORD)m_strBone.length() + VERSION;
	SFile << dwGabageData;

	SFile << m_cMatrixKeys;
	if ( m_cMatrixKeys>0 )
	{
		SFile.WriteBuffer ( m_pMatrixKeys, sizeof(BSMatrixKey)*m_cMatrixKeys );
	}

	SFile << m_cScaleKeys;
	if ( m_cScaleKeys>0 )
	{
		SFile.WriteBuffer ( m_pScaleKeys, sizeof(BSScaleKey)*m_cScaleKeys );
	}	

	return S_OK;
}

HRESULT InnerBin::LoadFromFile ( CSerialFile &SFile  )
{
	DWORD dwVER(0);
	SFile >> dwVER;
	
	if ( VERSION==dwVER )		Load( SFile );
	else if ( 0x102==dwVER )	Load_0102( SFile );
	else if ( 0x101==dwVER )	Load_0101( SFile );
	else if ( 0x100==dwVER )	Load_0100( SFile );
	else
	{
		CString strTemp = "";
		strTemp.Format( "InnerBin::LoadFromFile Error! Name:%s Version:%d Current Version:%d" ,SFile.GetFileName(),dwVER,VERSION);
		if ( CCrypt::bEngineDebug )  MessageBox (NULL,strTemp,"Need New Version",MB_OK);
		if ( CCrypt::bEngineDebugLog )  CDebugSet::ToFile ( "EngineLoadError.txt",strTemp );
		strTemp.Empty();

		return E_FAIL;
	}

	return S_OK;
}

HRESULT InnerBin::Load_0100( CSerialFile &SFile )
{
	SFile >> m_cPositionKeys;
	if ( m_cPositionKeys>0 )
	{
		m_pPositionKeys = new BSPositionKey[m_cPositionKeys];
		SFile.ReadBuffer ( m_pPositionKeys, sizeof(BSPositionKey)*m_cPositionKeys );
	}

	SFile >> m_cRotateKeys;
	if ( m_cRotateKeys>0 )
	{
		m_pRotateKeys = new BSRotateKey[m_cRotateKeys];
		SFile.ReadBuffer ( m_pRotateKeys, sizeof(BSRotateKey)*m_cRotateKeys );
	}

	SFile >> m_cScaleKeys;
	if ( m_cScaleKeys>0 )
	{
		m_pScaleKeys = new BSScaleKey[m_cScaleKeys];
		SFile.ReadBuffer ( m_pScaleKeys, sizeof(BSScaleKey)*m_cScaleKeys );
	}

	SFile >> m_cMatrixKeys;
	if ( m_cMatrixKeys>0 )
	{
		m_pMatrixKeys = new BSMatrixKey[m_cMatrixKeys];
		SFile.ReadBuffer ( m_pMatrixKeys, sizeof(BSMatrixKey)*m_cMatrixKeys );

		m_fDivFullTime = 1.f/m_pMatrixKeys[m_cMatrixKeys-1].dwTime;
		m_fMatrixKeys = (float)m_cMatrixKeys;
	}

	SFile >> m_strBone;

	return S_OK;
}

HRESULT InnerBin::Load_0101( CSerialFile &SFile )
{
	SFile >> m_cPositionKeys;
	if ( m_cPositionKeys>0 )
	{
		m_pPositionKeys = new BSPositionKey[m_cPositionKeys];
		SFile.ReadBuffer ( m_pPositionKeys, sizeof(BSPositionKey)*m_cPositionKeys );
	}

	SFile >> m_cRotateKeys;
	if ( m_cRotateKeys>0 )
	{
		m_pRotateKeys = new BSRotateKey[m_cRotateKeys];
		SFile.ReadBuffer ( m_pRotateKeys, sizeof(BSRotateKey)*m_cRotateKeys );
	}

	SFile >> m_cScaleKeys;
	if ( m_cScaleKeys>0 )
	{
		m_pScaleKeys = new BSScaleKey[m_cScaleKeys];
		SFile.ReadBuffer ( m_pScaleKeys, sizeof(BSScaleKey)*m_cScaleKeys );
	}

	SFile >> m_cMatrixKeys;
	if ( m_cMatrixKeys>0 )
	{
		m_pMatrixKeys = new BSMatrixKey[m_cMatrixKeys];
		SFile.ReadBuffer ( m_pMatrixKeys, sizeof(BSMatrixKey)*m_cMatrixKeys );

		m_fDivFullTime = 1.f/m_pMatrixKeys[m_cMatrixKeys-1].dwTime;
		m_fMatrixKeys = (float)m_cMatrixKeys;
	}

	SFile >> m_cQuatPosKeys;
	if ( m_cQuatPosKeys>0 )
	{
		m_pQuatPosKeys = new BSQuatPosKey[m_cQuatPosKeys];
		SFile.ReadBuffer ( m_pQuatPosKeys, sizeof(BSQuatPosKey)*m_cQuatPosKeys );
	}

	SFile >> m_strBone;

	return S_OK;
}

HRESULT InnerBin::Load_0102( CSerialFile &SFile  )
{

	SFile >> m_strBone;

	SFile >> m_cRotateKeys;
	if ( m_cRotateKeys>0 )
	{
		m_pRotateKeys = new BSRotateKey[m_cRotateKeys];
		SFile.ReadBuffer ( m_pRotateKeys, sizeof(BSRotateKey)*m_cRotateKeys );
	}
	
	SFile >> m_cPositionKeys;
	if ( m_cPositionKeys>0 )
	{
		m_pPositionKeys = new BSPositionKey[m_cPositionKeys];
		SFile.ReadBuffer ( m_pPositionKeys, sizeof(BSPositionKey)*m_cPositionKeys );
	}

	DWORD dwGabageValue;
	SFile >> dwGabageValue;

	SFile >> m_cQuatPosKeys;
	if ( m_cQuatPosKeys>0 )
	{
		m_pQuatPosKeys = new BSQuatPosKey[m_cQuatPosKeys];
		SFile.ReadBuffer ( m_pQuatPosKeys, sizeof(BSQuatPosKey)*m_cQuatPosKeys );
	}

	SFile >> dwGabageValue;

	SFile >> m_cMatrixKeys;
	if ( m_cMatrixKeys>0 )
	{
		m_pMatrixKeys = new BSMatrixKey[m_cMatrixKeys];
		SFile.ReadBuffer ( m_pMatrixKeys, sizeof(BSMatrixKey)*m_cMatrixKeys );

		m_fDivFullTime = 1.f/m_pMatrixKeys[m_cMatrixKeys-1].dwTime;
		m_fMatrixKeys = (float)m_cMatrixKeys;
	}

	SFile >> m_cScaleKeys;
	if ( m_cScaleKeys>0 )
	{
		m_pScaleKeys = new BSScaleKey[m_cScaleKeys];
		SFile.ReadBuffer ( m_pScaleKeys, sizeof(BSScaleKey)*m_cScaleKeys );
	}

	return S_OK;
}

HRESULT InnerBin::Load( CSerialFile &SFile  )
{

	SFile >> m_strBone;

	SFile >> m_cRotateKeys;
	if ( m_cRotateKeys>0 )
	{
		m_pRotateKeys = new BSRotateKey[m_cRotateKeys];
		SFile.ReadBuffer ( m_pRotateKeys, sizeof(BSRotateKey)*m_cRotateKeys );
	}

	DWORD dwGabageValue;
	SFile >> dwGabageValue;
	
	SFile >> m_cPositionKeys;
	if ( m_cPositionKeys>0 )
	{
		m_pPositionKeys = new BSPositionKey[m_cPositionKeys];
		SFile.ReadBuffer ( m_pPositionKeys, sizeof(BSPositionKey)*m_cPositionKeys );
	}

	
	SFile >> m_cQuatPosKeys;
	if ( m_cQuatPosKeys>0 )
	{
		m_pQuatPosKeys = new BSQuatPosKey[m_cQuatPosKeys];
		SFile.ReadBuffer ( m_pQuatPosKeys, sizeof(BSQuatPosKey)*m_cQuatPosKeys );
	}
	
	SFile >> m_cMatrixKeys;
	if ( m_cMatrixKeys>0 )
	{
		m_pMatrixKeys = new BSMatrixKey[m_cMatrixKeys];
		SFile.ReadBuffer ( m_pMatrixKeys, sizeof(BSMatrixKey)*m_cMatrixKeys );

		m_fDivFullTime = 1.f/m_pMatrixKeys[m_cMatrixKeys-1].dwTime;
		m_fMatrixKeys = (float)m_cMatrixKeys;
	}

	SFile >> dwGabageValue;

	SFile >> m_cScaleKeys;
	if ( m_cScaleKeys>0 )
	{
		m_pScaleKeys = new BSScaleKey[m_cScaleKeys];
		SFile.ReadBuffer ( m_pScaleKeys, sizeof(BSScaleKey)*m_cScaleKeys );
	}


	return S_OK;
}


//
HRESULT  BinManager::Load_0100( CSerialFile &SFile )
{
	SANILIST listANI;

	DWORD dwNumAni(0);
	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		listANI.push_back ( pAnimation );
	}

	std::for_each(m_listAnimation.begin(),m_listAnimation.end(),std_afunc::DeleteObject());
	m_listAnimation = listANI;


	std::for_each(m_listAniUPBODY.begin(),m_listAniUPBODY.end(),std_afunc::DeleteObject());
	m_listAniUPBODY.clear();

	m_bVALID = true;

	return S_OK;
}
HRESULT  BinManager::Load_0101( CSerialFile &SFile )
{
	SANILIST listANI;

	DWORD dwNumAni(0);
	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		listANI.push_back ( pAnimation );
	}

	std::for_each(m_listAnimation.begin(),m_listAnimation.end(),std_afunc::DeleteObject());
	m_listAnimation = listANI;


	std::for_each(m_listAniUPBODY.begin(),m_listAniUPBODY.end(),std_afunc::DeleteObject());
	m_listAniUPBODY.clear();


	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		m_listAniUPBODY.push_back ( pAnimation );
	}

	m_bVALID = true;

	return S_OK;
}

HRESULT  BinManager::Load_0102( CSerialFile &SFile )
{
	SANILIST listANI;
	DWORD dwNumAni(0);

	std::for_each(m_listAniUPBODY.begin(),m_listAniUPBODY.end(),std_afunc::DeleteObject());
	m_listAniUPBODY.clear();

	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		m_listAniUPBODY.push_back ( pAnimation );
	}

	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		listANI.push_back ( pAnimation );
	}

	std::for_each(m_listAnimation.begin(),m_listAnimation.end(),std_afunc::DeleteObject());
	m_listAnimation = listANI;
	
	m_bVALID = true;

	return S_OK;
}

HRESULT  BinManager::Load_0103( CSerialFile &SFile )
{
	SANILIST listANI;
	DWORD dwNumAni(0);
	DWORD dwGarbageValue(0);

	std::for_each(m_listAniUPBODY.begin(),m_listAniUPBODY.end(),std_afunc::DeleteObject());
	m_listAniUPBODY.clear();

	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile  );

		m_listAniUPBODY.push_back ( pAnimation );
	}

	SFile >> dwGarbageValue;

	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		listANI.push_back ( pAnimation );
	}

	std::for_each(m_listAnimation.begin(),m_listAnimation.end(),std_afunc::DeleteObject());
	m_listAnimation = listANI;
	
	m_bVALID = true;

	return S_OK;
}
HRESULT  BinManager::Load( CSerialFile &SFile )
{
	SANILIST listANI;
	DWORD dwNumAni(0);
	DWORD dwNumAniUp(0);
	DWORD dwNum(0);

	SFile >> dwNumAni;
	for ( DWORD i=0; i<dwNumAni; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		listANI.push_back ( pAnimation );
	}
	std::for_each(m_listAnimation.begin(),m_listAnimation.end(),std_afunc::DeleteObject());
	m_listAnimation = listANI;

	std::for_each(m_listAniUPBODY.begin(),m_listAniUPBODY.end(),std_afunc::DeleteObject());
	m_listAniUPBODY.clear();

	SFile >> dwNumAniUp;
	for ( DWORD i=0; i<dwNumAniUp; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		m_listAniUPBODY.push_back ( pAnimation );
	}

	//std::for_each(m_listAniUPBODY.begin(),m_listAniUPBODY.end(),std_afunc::DeleteObject());
	//m_listAniUPBODY.clear();

	SFile >> dwNum;
	for ( DWORD i=0; i<dwNum; ++i )
	{
		InnerBin *pAnimation = new InnerBin;
		pAnimation->LoadFromFile(SFile );

		m_listAniUPBODY.push_back ( pAnimation );
	}
	
	m_bVALID = true;

	return S_OK;
}

BOOL BinManager::LoadFile ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinAniMan::GetInstance().GetPath () );
	StringCchCat( szPathName, MAX_PATH, szFile );


	CSerialFile SFile;
	if ( !SFile.OpenFile ( FOT_READ, szPathName ) )		return FALSE;

	TCHAR szFileType[FILETYPESIZE] = "";
	DWORD dwVersion;
	SFile.GetFileType( szFileType, FILETYPESIZE, dwVersion );

	switch ( dwVersion )
	{
	case 0x0100:		Load_0100( SFile );	break;
	case 0x0101:		Load_0101( SFile );	break;
	case 0x0102:		Load_0102( SFile );	break;
	case 0x0103:		Load_0103( SFile );	break;
	case VERSION:		Load( SFile );		break;
	default:
		CString strTemp = "";
		strTemp.Format( "BinManager::LoadFile Error! Name:%s Version:%d Current Version:%d" ,SFile.GetFileName(),dwVersion,VERSION);
		if ( CCrypt::bEngineDebug )  MessageBox (NULL,strTemp,"Need New Version",MB_OK);
		if ( CCrypt::bEngineDebugLog )  CDebugSet::ToFile ( "EngineLoadError.txt",strTemp );
		strTemp.Empty();

		return FALSE;
	}

	return TRUE;
}


BOOL BinManager::SaveFile ( const char* szFile )
{
	char szPathName[MAX_PATH] = "";
	StringCchCopy( szPathName, MAX_PATH, DxSkinAniMan::GetInstance().GetPath () );
	StringCchCat( szPathName, MAX_PATH, szFile );

	CSerialFile SFile;
	SFile.SetFileType ( szFILETYPE, VERSION_ANISAVE );

	if ( !SFile.OpenFile ( FOT_WRITE, szPathName ) )		return FALSE;

	SFile << (DWORD)m_listAniUPBODY.size();
	
	SANILIST_ITER iter = m_listAniUPBODY.begin();
	SANILIST_ITER iter_end = m_listAniUPBODY.end();
	for ( ; iter!=iter_end; ++iter )
	{
		(*iter)->SaveToFile(SFile);
	}

	SFile << (DWORD)m_listAnimation.size();
	
	iter = m_listAnimation.begin();
	iter_end = m_listAnimation.end();
	for ( ; iter!=iter_end; ++iter )
	{
		(*iter)->SaveToFile(SFile);
	}

	return TRUE;
}

