#include "stdafx.h"
#include "CItemSetLists.h"
#include "./GLogicData.h"

#include "../../EngineLib/Common/IniLoader.h"
#include "../../EngineLib/G-Logic/GLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemSetLists::CItemSetLists()
{
};
CItemSetLists::~CItemSetLists()
{
};

CItemSetLists& CItemSetLists::GetInstance ()
{
	static CItemSetLists Instance;
	return Instance;
}

BOOL CItemSetLists::FindData( SNATIVEID sNATIVEID )
{
	return FALSE;
}

BOOL CItemSetLists::LoadDataSet()
{
	std::string strPATH( GLOGIC::GetPath() );
	strPATH += "itemsetlists.ini";

	CIniLoader cFILE;

	if( GLOGIC::bGLOGIC_ZIPFILE )
		cFILE.SetZipFile( GLOGIC::strGLOGIC_ZIPFILE );

	if( !cFILE.open( strPATH, true, GLOGIC::bGLOGIC_PACKFILE ) )
	{
		CDebugSet::ToLogFile( "ERROR : CItemSetLists::LOAD()" );
		return FALSE;
	}
	DWORD dwNUM = cFILE.GetKeyDataSize( "ITEMSETLISTS_OPTION", "FILE_LIST" );
	for( DWORD i=0; i<dwNUM; ++i )
	{
		std::string strFileName;
		cFILE.getflag( "ITEMSETLISTS_OPTION", "FILE_LIST", i, dwNUM, strFileName );

		m_listFileName.push_back( strFileName );
	}

	STRING_LIST_ITER iter = m_listFileName.begin();
	STRING_LIST_ITER iter_end = m_listFileName.end();
	for( ; iter != iter_end; ++iter )
	{
		CItemSetListsOption * pItemSetListsOption = new CItemSetListsOption;
		if( !pItemSetListsOption->Load( *iter ) )
		{
			CDebugSet::ToLogFile ( "ERROR : CItemSetListsOption::LOAD(), File Open %s", iter->c_str() );
			return false;
		}

		m_listItemSet.push_back( pItemSetListsOption );
	}
	return TRUE;
};