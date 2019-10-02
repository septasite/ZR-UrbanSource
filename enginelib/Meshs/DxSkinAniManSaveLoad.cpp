#include "stdafx.h"

#include "../Common/SerialFile.h"
#include "../G-Logic/GLogic.h"

#include "DxBoneCollector.h"
#include "../DxEffect/EffAni/DxEffAni.h"

#include "DxSkinAniMan.h"
#include "../Common/StringUtils.h"
#include "../Common/StlFunctions.h"

#include "../DxFrame/dsutil.h"
#include "../DxCommon/DxViewPort.h"
#include "../../EngineSoundLib/DxSound/DxSoundMan.h"
#include "DxAniBoneScale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL SANIMCONINFO::LoadFile ( const char *szFileName, LPDIRECT3DDEVICEQ pd3dDevice )
{
	CleanUp();

	char szFilePath[MAX_PATH] = "";
	StringCchCopy( szFilePath, MAX_PATH, DxSkinAniMan::GetInstance().GetPath() );
	StringCchCat( szFilePath, MAX_PATH, szFileName );

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strANIMATION_ZIPFILE.c_str(),
																	szFilePath, 
																	szFileName ) );

	if ( !pBStream.get() )
		return FALSE;

	basestream &SFile = *pBStream;

	char szFileType[FILETYPESIZE] = {0};
	DWORD dwVersion;
	SFile.GetFileType( szFileType, FILETYPESIZE, dwVersion );

	if ( 0x0101 == dwVersion )
	{
		SANIMCONINFO_101 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(OldAnimInfo) );
		
		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

        m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );			
	}
	else if ( 0x0102 == dwVersion )
	{
		SANIMCONINFO_102 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(OldAnimInfo) );
		
		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

        m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );

		m_ChaSoundData = OldAnimInfo.m_ChaSoundData;
	}
	else if ( 0x0103 == dwVersion )
	{
		SANIMCONINFO_103 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(OldAnimInfo) );

		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

		m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );

		m_wStrikeCount = 0;

		m_ChaSoundData = OldAnimInfo.m_ChaSoundData;
	}
	else if ( 0x0104 == dwVersion )
	{
		SANIMCONINFO_104 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(SANIMCONINFO_104) );

		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

		m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );

		m_wStrikeCount = OldAnimInfo.m_wStrikeCount;
		memcpy ( m_sStrikeEff, OldAnimInfo.m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		m_ChaSoundData = OldAnimInfo.m_ChaSoundData;
	}
	else if( 0x0105 == dwVersion )
	{
		//SFile.ReadBuffer ( this, sizeof(SANIMCONINFO) );
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SChaSoundData_103 ChaSoundData;
		SFile.ReadBuffer ( &ChaSoundData, sizeof(SChaSoundData_103) );
		m_ChaSoundData = ChaSoundData;		

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}
	}
	else if( 0x0106 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}
	}
	else if( 0x0107 == dwVersion )
	{
		//SFile.ReadBuffer ( this, sizeof(SANIMCONINFO) );
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}
	else if( 0x0108 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_UNITTIME;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		
		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );	
	}

	else if( 0x0109 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_UNITTIME;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );


		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );
	}

	else if( 0x0110 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_UNITTIME;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );
	}
	else if( 0x0111 == dwVersion )
	{
		DWORD dwSize;

		SFile >> dwSize;
		char *szCfgName = new char[dwSize];
		SFile.ReadBuffer ( szCfgName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szXName = new char[dwSize];
		SFile.ReadBuffer ( szXName, sizeof(char)*dwSize );

		strcpy (m_szName,szXName);
		//m_szName = szXName;

		SFile >> dwSize;
		char *szBinName = new char[dwSize];
		SFile.ReadBuffer ( szBinName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szSKName = new char[dwSize];
		SFile.ReadBuffer ( szSKName, sizeof(char)*dwSize );

		strcpy (m_szSkeletion,szSKName);

		SAFE_DELETE_ARRAY(szCfgName); //fix memory leak
		SAFE_DELETE_ARRAY(szXName);
		SAFE_DELETE_ARRAY(szBinName);
		SAFE_DELETE_ARRAY(szSKName);

		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		//DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}


	else if( 0x0112 == dwVersion )
	{
		DWORD dwSize;

		SFile >> dwSize;
		char *szCfgName = new char[dwSize];
		SFile.ReadBuffer ( szCfgName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szXName = new char[dwSize];
		SFile.ReadBuffer ( szXName, sizeof(char)*dwSize );

		strcpy (m_szName,szXName);
		//m_szName = szXName;

		SFile >> dwSize;
		char *szBinName = new char[dwSize];
		SFile.ReadBuffer ( szBinName, sizeof(char)*dwSize );

		strcpy (m_szBin,szBinName);

		SFile >> dwSize;
		char *szSKName = new char[dwSize];
		SFile.ReadBuffer ( szSKName, sizeof(char)*dwSize );

		strcpy (m_szSkeletion,szSKName);

		SAFE_DELETE_ARRAY(szCfgName); //fix memory leak
		SAFE_DELETE_ARRAY(szXName);
		SAFE_DELETE_ARRAY(szBinName);
		SAFE_DELETE_ARRAY(szSKName);



		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		//DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}

	else if( 0x0113 == dwVersion )
	{
		DWORD dwSize;

		SFile >> dwSize;
		char *szCfgName = new char[dwSize];
		SFile.ReadBuffer ( szCfgName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szXName = new char[dwSize];
		SFile.ReadBuffer ( szXName, sizeof(char)*dwSize );

		strcpy (m_szName,szXName);
		//m_szName = szXName;

		SFile >> dwSize;
		char *szBinName = new char[dwSize];
		SFile.ReadBuffer ( szBinName, sizeof(char)*dwSize );

		strcpy (m_szBin,szBinName);

		SFile >> dwSize;
		char *szSKName = new char[dwSize];
		SFile.ReadBuffer ( szSKName, sizeof(char)*dwSize );

		strcpy (m_szSkeletion,szSKName);

		SAFE_DELETE_ARRAY(szCfgName); //fix memory leak
		SAFE_DELETE_ARRAY(szXName);
		SAFE_DELETE_ARRAY(szBinName);
		SAFE_DELETE_ARRAY(szSKName);



		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		//DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}
// add animation 114 start
	else if( 0x0114 == dwVersion )
	{
		DWORD dwSize;

		SFile >> dwSize;
		char *szCfgName = new char[dwSize];
		SFile.ReadBuffer ( szCfgName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szXName = new char[dwSize];
		SFile.ReadBuffer ( szXName, sizeof(char)*dwSize );

		strcpy (m_szName,szXName);
		//m_szName = szXName;

		SFile >> dwSize;
		char *szBinName = new char[dwSize];
		SFile.ReadBuffer ( szBinName, sizeof(char)*dwSize );

		strcpy (m_szBin,szBinName);

		SFile >> dwSize;
		char *szSKName = new char[dwSize];
		SFile.ReadBuffer ( szSKName, sizeof(char)*dwSize );

		strcpy (m_szSkeletion,szSKName);

		SAFE_DELETE_ARRAY(szCfgName); //fix memory leak
		SAFE_DELETE_ARRAY(szXName);
		SAFE_DELETE_ARRAY(szBinName);
		SAFE_DELETE_ARRAY(szSKName);



		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		//DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false );
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}
// add animation 114 ended
	else if( dwVersion==SANIMCONINFO::VERSION )
	{
		DWORD dwSize;

		SFile >> dwSize;
		char *szCfgName = new char[dwSize];
		SFile.ReadBuffer ( szCfgName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szXName = new char[dwSize];
		SFile.ReadBuffer ( szXName, sizeof(char)*dwSize );

		strcpy (m_szName,szXName);
		//m_szName = szXName;

		SFile >> dwSize;
		char *szBinName = new char[dwSize];
		SFile.ReadBuffer ( szBinName, sizeof(char)*dwSize );

		strcpy (m_szBin,szBinName);

		SFile >> dwSize;
		char *szSKName = new char[dwSize];
		SFile.ReadBuffer ( szSKName, sizeof(char)*dwSize );

		strcpy (m_szSkeletion,szSKName);

		SAFE_DELETE_ARRAY(szCfgName); //fix memory leak
		SAFE_DELETE_ARRAY(szXName);
		SAFE_DELETE_ARRAY(szBinName);
		SAFE_DELETE_ARRAY(szSKName);



		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		//DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,false );
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}
	else
	{
		//MessageBox ( NULL, "SANIMCONINFO::LoadFile() unknown file version.", szFileName, MB_OK );
		/*CString strTemp = "";
		strTemp.Format( "SANIMCONINFO::LoadFile Error! Name:%s Version:%d Current Version:%d" ,SFile.GetFileName(),dwVersion,SANIMCONINFO::VERSION );
		if ( CCrypt::bEngineDebug )  MessageBox (NULL,strTemp,"Need New Version",MB_OK);
		if ( CCrypt::bEngineDebugLog )  CDebugSet::ToFile ( "EngineLoadError.txt",strTemp );
		strTemp.Empty();*/
	}

	m_dwFlag = m_dwFlag & ~ACF_NEWINFO;

	return TRUE;
}

BOOL SANIMCONINFO::LoadFileTool ( const char *szFileName, LPDIRECT3DDEVICEQ pd3dDevice )
{
	CleanUp();

	char szFilePath[MAX_PATH] = "";
	StringCchCopy( szFilePath, MAX_PATH, DxSkinAniMan::GetInstance().GetPath() );
	StringCchCat( szFilePath, MAX_PATH, szFileName );

	std::auto_ptr<basestream> pBStream( GLOGIC::openfile_basestream(GLOGIC::bENGLIB_ZIPFILE, 
																	GLOGIC::strANIMATION_ZIPFILE.c_str(),
																	szFilePath, 
																	szFileName ) );

	if ( !pBStream.get() )
		return FALSE;

	basestream &SFile = *pBStream;

	char szFileType[FILETYPESIZE] = {0};
	DWORD dwVersion;
	SFile.GetFileType( szFileType, FILETYPESIZE, dwVersion );

	if ( 0x0101 == dwVersion )
	{
		SANIMCONINFO_101 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(OldAnimInfo) );
		
		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

        m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );			
	}
	else if ( 0x0102 == dwVersion )
	{
		SANIMCONINFO_102 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(OldAnimInfo) );
		
		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

        m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );

		m_ChaSoundData = OldAnimInfo.m_ChaSoundData;
	}
	else if ( 0x0103 == dwVersion )
	{
		SANIMCONINFO_103 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(OldAnimInfo) );

		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

		m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );

		m_wStrikeCount = 0;

		m_ChaSoundData = OldAnimInfo.m_ChaSoundData;
	}
	else if ( 0x0104 == dwVersion )
	{
		SANIMCONINFO_104 OldAnimInfo;
		SFile.ReadBuffer ( &OldAnimInfo, sizeof(SANIMCONINFO_104) );

		StringCchCopy( m_szName, ACF_SZNAME, OldAnimInfo.m_szName );
		StringCchCopy( m_szSkeletion, ACF_SZNAME, OldAnimInfo.m_szSkeletion );

		m_dwFlag = OldAnimInfo.m_dwFlag;
		m_dwSTime = OldAnimInfo.m_dwSTime;
		m_dwETime = OldAnimInfo.m_dwETime;
		m_dwETimeOrig = OldAnimInfo.m_dwETimeOrig;
		m_UNITTIME = OldAnimInfo.m_UNITTIME;

		m_MainType = OldAnimInfo.m_MainType;
		m_SubType = OldAnimInfo.m_SubType;

		m_wDivCount = OldAnimInfo.m_wDivCount;
		memcpy ( m_wDivFrame, OldAnimInfo.m_wDivFrame, sizeof(WORD)*ACF_DIV );

		m_wStrikeCount = OldAnimInfo.m_wStrikeCount;
		memcpy ( m_sStrikeEff, OldAnimInfo.m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		m_ChaSoundData = OldAnimInfo.m_ChaSoundData;
	}
	else if( 0x0105 == dwVersion )
	{
		//SFile.ReadBuffer ( this, sizeof(SANIMCONINFO) );
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SChaSoundData_103 ChaSoundData;
		SFile.ReadBuffer ( &ChaSoundData, sizeof(SChaSoundData_103) );
		m_ChaSoundData = ChaSoundData;		

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,true);
				m_listEffAni.push_back ( pEff );
			}
		}
	}
	else if( 0x0106 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,true);
				m_listEffAni.push_back ( pEff );
			}
		}
	}
	else if( 0x0107 == dwVersion )
	{
		//SFile.ReadBuffer ( this, sizeof(SANIMCONINFO) );
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,true);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}
	else if( 0x0108 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_UNITTIME;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		
		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,true);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );	
	}

	else if( 0x0109 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_UNITTIME;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );


		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,true);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );
	}

	else if( 0x0110 == dwVersion )
	{
		SFile.ReadBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
		SFile.ReadBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

		SFile >> m_dwFlag;
		SFile >> m_UNITTIME;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,true);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );
	}
	else if( dwVersion==SANIMCONINFO::VERSION )
	{
		DWORD dwSize;

		SFile >> dwSize;
		char *szCfgName = new char[dwSize];
		SFile.ReadBuffer ( szCfgName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szXName = new char[dwSize];
		SFile.ReadBuffer ( szXName, sizeof(char)*dwSize );

		strcpy (m_szName,szXName);
		//m_szName = szXName;

		SFile >> dwSize;
		char *szBinName = new char[dwSize];
		SFile.ReadBuffer ( szBinName, sizeof(char)*dwSize );

		SFile >> dwSize;
		char *szSKName = new char[dwSize];
		SFile.ReadBuffer ( szSKName, sizeof(char)*dwSize );

		strcpy (m_szSkeletion,szSKName);


		SFile >> m_dwFlag;
		SFile >> m_dwSTime;
		SFile >> m_dwETime;
		SFile >> m_dwETimeOrig;
		SFile >> m_UNITTIME;

		DWORD	dwType;
		SFile >> dwType;
		m_MainType = (EMANI_MAINTYPE)dwType;
		SFile >> dwType;
		m_SubType = (EMANI_SUBTYPE)dwType;

		SFile >> m_wDivCount;
		SFile.ReadBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

		SFile >> m_wStrikeCount;
		SFile.ReadBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

		SFile.ReadBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

		//DWORD	dwSize;
		SFile >> dwSize;
		for ( DWORD i=0; i<dwSize; ++i )
		{
			DWORD	dwType;
			SFile >> dwType;
			DxEffAniData*	pEff = DxEffAniMan::GetInstance().CreateEffInstance ( dwType );
			if ( pEff )
			{
				pEff->LoadFile ( SFile, pd3dDevice ,true);
				m_listEffAni.push_back ( pEff );
			}
		}

		m_pAniScale->Load( SFile );
	}
	else
	{
		//MessageBox ( NULL, "SANIMCONINFO::LoadFile() unknown file version.", szFileName, MB_OK );
		CString strTemp = "";
		strTemp.Format( "SANIMCONINFO::LoadFile Error! Name:%s Version:%d Current Version:%d" ,SFile.GetFileName(),dwVersion,SANIMCONINFO::VERSION );
		//MessageBox (NULL,strTemp,"Need New Version",MB_OK);
		CDebugSet::ToFile ( "EngineLoadError.txt",strTemp );
		strTemp.Empty();
	}

	m_dwFlag = m_dwFlag & ~ACF_NEWINFO;

	return TRUE;
}



BOOL SANIMCONINFO::SaveFile ( const char *szFileName )
{
	char szFilePath[MAX_PATH] = "";
	StringCchCopy( szFilePath, MAX_PATH, DxSkinAniMan::GetInstance().GetPath() );
	StringCchCat( szFilePath, MAX_PATH, szFileName );

	CSerialFile SFile;
	SFile.SetFileType ( "SANIMCONINFO", SANIMCONINFO::VERSION_CFGSAVE );
	if ( !SFile.OpenFile ( FOT_WRITE, szFilePath ) )	return FALSE;

	//SFile.WriteBuffer ( this, sizeof(SANIMCONINFO) );

	SFile.WriteBuffer ( m_szName, sizeof(char)*ACF_SZNAME );
	SFile.WriteBuffer ( m_szBin, sizeof(char)*ACF_SZNAME );
	SFile.WriteBuffer ( m_szSkeletion, sizeof(char)*ACF_SZNAME );

	SFile << m_dwFlag;
	SFile << m_dwSTime;
	SFile << m_dwETime;
	SFile << m_dwETimeOrig;
	SFile << m_UNITTIME;

	SFile << m_MainType;
	SFile << m_SubType;

	SFile << m_wDivCount;
	SFile.WriteBuffer ( m_wDivFrame, sizeof(WORD)*ACF_DIV );

	SFile << m_wStrikeCount;
	SFile.WriteBuffer ( m_sStrikeEff, sizeof(SANIMSTRIKE)*ACF_STRIKE );

	SFile.WriteBuffer ( &m_ChaSoundData, sizeof(SChaSoundData) );

	SFile << (DWORD) m_listEffAni.size();
	EFFANILIST_ITER iter = m_listEffAni.begin();
	EFFANILIST_ITER iter_end = m_listEffAni.end();
	for ( ; iter!=iter_end; ++iter )
	{
		SFile << (DWORD) (*iter)->GetTypeID();
		(*iter)->SaveFile ( SFile );
	}

	m_pAniScale->Save( SFile );

	return TRUE;
}



