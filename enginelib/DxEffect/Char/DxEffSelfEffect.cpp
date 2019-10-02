#include "stdafx.h"
#include <algorithm>
#include "./DxEffSelfEffect.h"
#include "../G-Logic/GLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DxEffSelfEffectMan& DxEffSelfEffectMan::GetInstance()
{
	static DxEffSelfEffectMan Instance;
	return Instance;
}

DxEffSelfEffect::DxEffSelfEffect(void) 
{
}

DxEffSelfEffect::~DxEffSelfEffect(void)
{
	CleanUp ();
}

void DxEffSelfEffect::CleanUp ()
{
	std::for_each ( m_listEffData.begin(), m_listEffData.end(), std_afunc::DeleteObject() );
	m_listEffData.clear ();
}

BOOL DxEffSelfEffect::SetPart ( DxCharPart *pCharPart, LPDIRECT3DDEVICEQ	pd3dDevice )
{
	HRESULT hr;

	EFFDATALIST_ITER iter = m_listEffData.begin();
	EFFDATALIST_ITER iter_end = m_listEffData.end();
	for ( ; iter!=iter_end; iter++ )
	{
		DWORD dwTypeID;
		SEFFDATA *pEffData = (*iter);

		pEffData->m_byteStream.ResetIter ();
		pEffData->m_byteStream >> dwTypeID;

		DxEffChar* pNewEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( dwTypeID );
		if ( !pNewEffChar )		return FALSE;

		pNewEffChar->SetFileName ( m_strFileName );
		pNewEffChar->SetLinkObj ( pCharPart, NULL );
		pNewEffChar->SetDirection ( &D3DXVECTOR3(0,0,1), 0.0f );
		hr = pNewEffChar->LoadFile ( pEffData->m_byteStream, pd3dDevice, false, false );
		if (FAILED(hr))
		{
			SAFE_DELETE(pNewEffChar);
			continue;
		}

		pCharPart->AddEffList ( pNewEffChar );
	}

	return TRUE;
}

BOOL DxEffSelfEffect::LoadFile ( basestream &SFile )
{
	DWORD dwType;
	DWORD dwSize;
	SFile >> dwType;

	SFile >> dwSize;

	for ( DWORD i=0; i<dwSize; i++ )
	{
		DWORD dwBuffSize;
		SFile >> dwBuffSize;
		LPBYTE pBuffer = new BYTE[dwBuffSize];
		
		SFile.ReadBuffer ( pBuffer, dwBuffSize );

		SEFFDATA* pEFFDATA = new SEFFDATA;
		pEFFDATA->m_byteStream.WriteBuffer ( pBuffer, dwBuffSize );
		m_listEffData.push_back ( pEFFDATA );

		delete[] pBuffer;
	}

	return TRUE;
}

BOOL DxEffSelfEffect::SaveFile ( CSerialFile &SFile )
{
	SFile << DWORD(10211989);
	SFile << DWORD(m_listEffData.size());

	EFFDATALIST_ITER iter = m_listEffData.begin();
	EFFDATALIST_ITER iter_end = m_listEffData.end();
	for ( ; iter!=iter_end; iter++ )
	{
		SEFFDATA *pEffData = (*iter);

		LPBYTE pBuff;
		DWORD dwSize;
		pEffData->m_byteStream.GetBuffer( pBuff, dwSize );

		SFile << dwSize;
		SFile.WriteBuffer ( pBuff, dwSize );
	}

	return TRUE;
}

BOOL DxEffSelfEffect::LoadFile ( const char* szFile )
{
	m_strFileName = szFile;

	std::string strPathName;
	strPathName = DxEffSelfEffectMan::GetInstance().GetPath ();
	strPathName += szFile;

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strEFFECT_CHAR_ZIPFILE.c_str(),
																	strPathName.c_str(), 
																	szFile ) );

	if ( !pBStream.get() )
		return FALSE;

	basestream &SFile = *pBStream;

	return LoadFile ( SFile );
}

BOOL DxEffSelfEffect::SaveFile ( const char* szFile )
{
	std::string strPathName;
	strPathName = DxEffSelfEffectMan::GetInstance().GetPath ();
	strPathName += szFile;

	CSerialFile SFile;
	BOOL bOk = SFile.OpenFile ( FOT_WRITE, strPathName.c_str() );
	if ( !bOk )		return FALSE;

	return SaveFile ( SFile );
}

HRESULT DxEffSelfEffectMan::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	m_pd3dDevice = pd3dDevice;
	return TRUE;
}

BOOL DxEffSelfEffectMan::PutEffect ( DxCharPart *pCharPart, const char* szEffFile )
{
	if ( !pCharPart )	return FALSE;

	DxEffSelfEffect *pEffCharData = NULL;
	EFFDATA_MAP_ITER iter = m_mapEffData.find ( std::string(szEffFile) );
	if ( iter == m_mapEffData.end() )
	{
		pEffCharData = new DxEffSelfEffect;
		BOOL bOk = pEffCharData->LoadFile ( szEffFile );
		if ( !bOk )
		{
			delete pEffCharData;
			return FALSE;
		}

		m_mapEffData[std::string(szEffFile)] = pEffCharData;
	}else{
		pEffCharData = iter->second;
	}

	pEffCharData->SetPart ( pCharPart, m_pd3dDevice );

	return TRUE;
}

BOOL DxEffSelfEffectMan::PutEffect ( DxSkinCharPiece *pAttBone, const char* szEffFile )
{
	if ( !pAttBone )	return FALSE;
	if ( !szEffFile || szEffFile[0]==NULL )	return E_FAIL;

	DxEffSelfEffect *pEffCharData = NULL;
	EFFDATA_MAP_ITER iter = m_mapEffData.find ( std::string(szEffFile) );
	if ( iter == m_mapEffData.end() )
	{
		pEffCharData = new DxEffSelfEffect;
		BOOL bOk = pEffCharData->LoadFile ( szEffFile );
		if ( !bOk )
		{
			delete pEffCharData;
			return FALSE;
		}

		m_mapEffData[std::string(szEffFile)] = pEffCharData;
	}else{
		pEffCharData = iter->second;
	}

	for ( int i=0; i<PIECE_SIZE; i++ )
	{
		PDXCHARPART pCharPart = pAttBone->GetPiece(i);
		if (!pCharPart)	continue;
		BOOL bFind = pCharPart->FindEffList ( szEffFile );
		if ( !bFind )
		{
			pEffCharData->SetPart( pCharPart, m_pd3dDevice );
		}
	}

	return TRUE;
}

BOOL DxEffSelfEffectMan::PutEffect ( DxSkinVehicle *pVehicle, const char* szEffFile )
{
	if ( !pVehicle )	return FALSE;
	if ( !szEffFile || szEffFile[0]==NULL )	return E_FAIL;

	DxEffSelfEffect *pEffCharData = NULL;

	EFFDATA_MAP_ITER iter = m_mapEffData.find ( std::string(szEffFile) );
	if ( iter == m_mapEffData.end() )
	{
		pEffCharData = new DxEffSelfEffect;
		BOOL bOk = pEffCharData->LoadFile ( szEffFile );
		if ( !bOk )
		{
			delete pEffCharData;
			return FALSE;
		}

		m_mapEffData[std::string(szEffFile)] = pEffCharData;
	}else{
		pEffCharData = iter->second;
	}

	for ( int i=0; i<PIECE_SIZE; i++ )
	{
		PDXCHARPART pCharPart = pVehicle->GetPiece(i);
		if (!pCharPart)	continue;
		BOOL bFind = pCharPart->FindEffList ( szEffFile );
		if ( !bFind )
		{
			pEffCharData->SetPart( pCharPart, m_pd3dDevice );
		}
	}

	return TRUE;
}

void DxEffSelfEffectMan::CleanUp ()
{
	std::for_each ( m_mapEffData.begin(), m_mapEffData.end(), std_afunc::DeleteMapObject() );
	m_mapEffData.clear ();
}



