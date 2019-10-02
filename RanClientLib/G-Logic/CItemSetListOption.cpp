#include "stdafx.h"
#include "CItemSetListOption.h"
#include "./GLogicData.h"
#include "../../EngineLib/Common/GLTexFile.h"
#include "../../EngineLib/G-Logic/GLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemSetListsOption::CItemSetListsOption() : m_dwPartCount( 0 )
{
	memset( m_sItemSetLists , 0 , sizeof( SIDSETITEMLIST ) * MAX_PIECE_TYPE );
	memset( m_sPartOption , 0 , sizeof( SPARTOPTION ) * MAX_PARTOPTION_TYPE );
}

CItemSetListsOption::~CItemSetListsOption()
{
}

BOOL CItemSetListsOption::Load( const std::string & strFileName )
{
	std::string strPATH( GLOGIC::GetPath() );
	strPATH += strFileName;

	gltexfile cFILE;
	cFILE.reg_sep ( '\t' );
	cFILE.reg_sep ( ' ' );
	cFILE.reg_sep ( ',' );
	cFILE.reg_sep ( '{' );
	cFILE.reg_sep ( '}' );
	cFILE.reg_sep ( '[' );
	cFILE.reg_sep ( ']' );
	cFILE.reg_sep ( '(' );
	cFILE.reg_sep ( ')' );
	cFILE.reg_sep ( '|' );
	cFILE.reg_sep ( '\"' );

	if( GLOGIC::bGLOGIC_ZIPFILE )
		cFILE.SetZipFile( GLOGIC::strGLOGIC_ZIPFILE );

	if( !cFILE.open( strPATH, true, GLOGIC::bGLOGIC_PACKFILE ) )
	{
		CDebugSet::ToLogFile( "ERROR : CItemSetListsOption::LOAD()" );
		return FALSE;
	}
	SIDSETITEMLIST sID;
	char szSetType[SLOT_MAX][MAX_PATH] = { "HEADGEAR"
											,"UPPER"
											,"LOWER"
											,"HAND"
											,"FOOT"
											,"RHAND"
											,"LHAND"
											,"NECK"
											,"WRIST"
											,"RFINGER"
											,"LFINGER"
											,"RHAND_S"
											,"LHAND_S"
											,"VEHICLE"
											,"WING"
											,"BELT"
											,"REARRING"
											,"LEARRING"
											,"ACCESSORY"
	};
	for( DWORD i = 0 ; i < SLOT_MAX ; i ++ )
	{
		CString strFLAG;
		strFLAG.Format ( "%s", szSetType[i] );
		cFILE.getflag( strFLAG.GetString(), 1, 2, sID.fMainID );
		cFILE.getflag( strFLAG.GetString(), 2, 2, sID.fSubID );
		m_sItemSetLists[ i ] = sID;
		//CDebugSet::ToLogFile( "%d : %d" , sID.fMainID , sID.fSubID );
	}
	cFILE.getflag( "dwPartCount", 1, 1, m_dwPartCount );

	if ( m_dwPartCount > (DWORD)MAX_PARTOPTION_TYPE ) m_dwPartCount = (DWORD)MAX_PARTOPTION_TYPE;

	for ( DWORD i=0; i<m_dwPartCount; ++i )
	{
		CString strFLAG;

		strFLAG.Format ( "PARTOPTION_%02d", i+1 );
		cFILE.getflag( strFLAG.GetString(), 1, 3, m_sPartOption[i].dwContPart );
		cFILE.getflag( strFLAG.GetString(), 2, 3, m_sPartOption[i].dwType );
		cFILE.getflag( strFLAG.GetString(), 3, 3, m_sPartOption[i].dwValue );
		//CDebugSet::ToLogFile( "%d : %d" , m_sPartOption[i].dwType , m_sPartOption[i].dwValue );
	}
	return TRUE;
};