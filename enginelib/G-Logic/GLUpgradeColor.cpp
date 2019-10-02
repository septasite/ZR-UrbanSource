#include "stdafx.h"
#include "GLUpgradeColor.h"
#include "GLOGIC.h"

#include "../Common/IniLoader.h"
#include "../Common/GLTexFile.h"

#include "../RanClientLib/G-Logic/GLogicData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace GLUPGRADECOLOR
{	
	 DWORD	A0010_G_A= 0;
	 DWORD	A0010_G_R= 0;
	 DWORD	A0010_G_G= 0;
	 DWORD	A0010_G_B= 0;

	 DWORD	A0010_A_A= 0;
	 DWORD	A0010_A_R= 0;
	 DWORD	A0010_A_G= 0;
	 DWORD	A0010_A_B= 0;

	 DWORD	A0010_R_A= 0;
	 DWORD	A0010_R_R= 0;
	 DWORD	A0010_R_G= 0;
	 DWORD	A0010_R_B= 0;
//////////////
//////////////(+11)
	 DWORD	A0011_G_A= 0;
	 DWORD	A0011_G_R= 0;
	 DWORD	A0011_G_G= 0;
	 DWORD	A0011_G_B= 0;

	 DWORD	A0011_A_A= 0;
	 DWORD	A0011_A_R= 0;
	 DWORD	A0011_A_G= 0;
	 DWORD	A0011_A_B= 0;

	 DWORD	A0011_R_A= 0;
	 DWORD	A0011_R_R= 0;
	 DWORD	A0011_R_G= 0;
	 DWORD	A0011_R_B= 0;
//////////////
//////////////(+12)
	 DWORD	A0012_G_A= 0;
	 DWORD	A0012_G_R= 0;
	 DWORD	A0012_G_G= 0;
	 DWORD	A0012_G_B= 0;

	 DWORD	A0012_A_A= 0;
	 DWORD	A0012_A_R= 0;
	 DWORD	A0012_A_G= 0;
	 DWORD	A0012_A_B= 0;

	 DWORD	A0012_R_A= 0;
	 DWORD	A0012_R_R= 0;
	 DWORD	A0012_R_G= 0;
	 DWORD	A0012_R_B= 0;
//////////////
//////////////(+13)
	 DWORD	A0013_G_A= 0;
	 DWORD	A0013_G_R= 0;
	 DWORD	A0013_G_G= 0;
	 DWORD	A0013_G_B= 0;

	 DWORD	A0013_A_A= 0;
	 DWORD	A0013_A_R= 0;
	 DWORD	A0013_A_G= 0;
	 DWORD	A0013_A_B= 0;

	 DWORD	A0013_R_A= 0;
	 DWORD	A0013_R_R= 0;
	 DWORD	A0013_R_G= 0;
	 DWORD	A0013_R_B= 0;
//////////////
//////////////(+14)
	 DWORD	A0014_G_A= 0;
	 DWORD	A0014_G_R= 0;
	 DWORD	A0014_G_G= 0;
	 DWORD	A0014_G_B= 0;

	 DWORD	A0014_A_A= 0;
	 DWORD	A0014_A_R= 0;
	 DWORD	A0014_A_G= 0;
	 DWORD	A0014_A_B= 0;

	 DWORD	A0014_R_A= 0;
	 DWORD	A0014_R_R= 0;
	 DWORD	A0014_R_G= 0;
	 DWORD	A0014_R_B= 0;
//////////////
//////////////(+15)
	 DWORD	A0015_G_A= 0;
	 DWORD	A0015_G_R= 0;
	 DWORD	A0015_G_G= 0;
	 DWORD	A0015_G_B= 0;

	 DWORD	A0015_A_A= 0;
	 DWORD	A0015_A_R= 0;
	 DWORD	A0015_A_G= 0;
	 DWORD	A0015_A_B= 0;

	 DWORD	A0015_R_A= 0;
	 DWORD	A0015_R_R= 0;
	 DWORD	A0015_R_G= 0;
	 DWORD	A0015_R_B= 0;
//////////////
//////////////(+16)
	 DWORD	A0016_G_A= 0;
	 DWORD	A0016_G_R= 0;
	 DWORD	A0016_G_G= 0;
	 DWORD	A0016_G_B= 0;

	 DWORD	A0016_A_A= 0;
	 DWORD	A0016_A_R= 0;
	 DWORD	A0016_A_G= 0;
	 DWORD	A0016_A_B= 0;

	 DWORD	A0016_R_A= 0;
	 DWORD	A0016_R_R= 0;
	 DWORD	A0016_R_G= 0;
	 DWORD	A0016_R_B= 0;
//////////////
//////////////(+17)
	 DWORD	A0017_G_A= 0;
	 DWORD	A0017_G_R= 0;
	 DWORD	A0017_G_G= 0;
	 DWORD	A0017_G_B= 0;

	 DWORD	A0017_A_A= 0;
	 DWORD	A0017_A_R= 0;
	 DWORD	A0017_A_G= 0;
	 DWORD	A0017_A_B= 0;

	 DWORD	A0017_R_A= 0;
	 DWORD	A0017_R_R= 0;
	 DWORD	A0017_R_G= 0;
	 DWORD	A0017_R_B= 0;

	 BOOL  GRINDCOLOR_LOADFILE ()
	{
			

	std::string strPath;
	strPath = GLOGIC::GetPath();
	strPath += "UpgradeColor.ini";


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

	if( !cFILE.open( strPath, true, GLOGIC::bGLOGIC_PACKFILE ) )
	{
		CDebugSet::ToLogFile ( "ERROR Cannot Load Upgrade Color Set File");
		return FALSE;
	}

////////////////////////////////////////////////////
	cFILE.getflag( "A0010_G", 1, 4, A0010_G_A );
	cFILE.getflag( "A0010_G", 2, 4, A0010_G_R );
	cFILE.getflag( "A0010_G", 3, 4, A0010_G_G );
	cFILE.getflag( "A0010_G", 4, 4, A0010_G_B );

	cFILE.getflag( "A0010_A", 1, 4, A0010_A_A );
	cFILE.getflag( "A0010_A", 2, 4, A0010_A_R );
	cFILE.getflag( "A0010_A", 3, 4, A0010_A_G );
	cFILE.getflag( "A0010_A", 4, 4, A0010_A_B );

	cFILE.getflag( "A0010_R", 1, 4, A0010_R_A );
	cFILE.getflag( "A0010_R", 2, 4, A0010_R_R );
	cFILE.getflag( "A0010_R", 3, 4, A0010_R_G );
	cFILE.getflag( "A0010_R", 4, 4, A0010_R_B );
	/////////////////
	cFILE.getflag( "A0011_G", 1, 4, A0011_G_A );
	cFILE.getflag( "A0011_G", 2, 4, A0011_G_R );
	cFILE.getflag( "A0011_G", 3, 4, A0011_G_G );
	cFILE.getflag( "A0011_G", 4, 4, A0011_G_B );

	cFILE.getflag( "A0011_A", 1, 4, A0011_A_A );
	cFILE.getflag( "A0011_A", 2, 4, A0011_A_R );
	cFILE.getflag( "A0011_A", 3, 4, A0011_A_G );
	cFILE.getflag( "A0011_A", 4, 4, A0011_A_B );

	cFILE.getflag( "A0011_R", 1, 4, A0011_R_A );
	cFILE.getflag( "A0011_R", 2, 4, A0011_R_R );
	cFILE.getflag( "A0011_R", 3, 4, A0011_R_G );
	cFILE.getflag( "A0011_R", 4, 4, A0011_R_B );

	/////////////////				
	cFILE.getflag( "A0012_G", 1, 4, A0012_G_A );				
	cFILE.getflag( "A0012_G", 2, 4, A0012_G_R );				
	cFILE.getflag( "A0012_G", 3, 4, A0012_G_G );				
	cFILE.getflag( "A0012_G", 4, 4, A0012_G_B );				
					
	cFILE.getflag( "A0012_A", 1, 4, A0012_A_A );				
	cFILE.getflag( "A0012_A", 2, 4, A0012_A_R );				
	cFILE.getflag( "A0012_A", 3, 4, A0012_A_G );				
	cFILE.getflag( "A0012_A", 4, 4, A0012_A_B );				
					
	cFILE.getflag( "A0012_R", 1, 4, A0012_R_A );				
	cFILE.getflag( "A0012_R", 2, 4, A0012_R_R );				
	cFILE.getflag( "A0012_R", 3, 4, A0012_R_G );				
	cFILE.getflag( "A0012_R", 4, 4, A0012_R_B );				
	/////////////////				
	cFILE.getflag( "A0013_G", 1, 4, A0013_G_A );				
	cFILE.getflag( "A0013_G", 2, 4, A0013_G_R );				
	cFILE.getflag( "A0013_G", 3, 4, A0013_G_G );				
	cFILE.getflag( "A0013_G", 4, 4, A0013_G_B );				
					
	cFILE.getflag( "A0013_A", 1, 4, A0013_A_A );				
	cFILE.getflag( "A0013_A", 2, 4, A0013_A_R );				
	cFILE.getflag( "A0013_A", 3, 4, A0013_A_G );				
	cFILE.getflag( "A0013_A", 4, 4, A0013_A_B );				
					
	cFILE.getflag( "A0013_R", 1, 4, A0013_R_A );				
	cFILE.getflag( "A0013_R", 2, 4, A0013_R_R );				
	cFILE.getflag( "A0013_R", 3, 4, A0013_R_G );				
	cFILE.getflag( "A0013_R", 4, 4, A0013_R_B );				
	/////////////////				
	cFILE.getflag( "A0014_G", 1, 4, A0014_G_A );				
	cFILE.getflag( "A0014_G", 2, 4, A0014_G_R );				
	cFILE.getflag( "A0014_G", 3, 4, A0014_G_G );				
	cFILE.getflag( "A0014_G", 4, 4, A0014_G_B );				
					
	cFILE.getflag( "A0014_A", 1, 4, A0014_A_A );				
	cFILE.getflag( "A0014_A", 2, 4, A0014_A_R );				
	cFILE.getflag( "A0014_A", 3, 4, A0014_A_G );				
	cFILE.getflag( "A0014_A", 4, 4, A0014_A_B );				
					
	cFILE.getflag( "A0014_R", 1, 4, A0014_R_A );				
	cFILE.getflag( "A0014_R", 2, 4, A0014_R_R );				
	cFILE.getflag( "A0014_R", 3, 4, A0014_R_G );				
	cFILE.getflag( "A0014_R", 4, 4, A0014_R_B );				
	/////////////////				
	cFILE.getflag( "A0015_G", 1, 4, A0015_G_A );				
	cFILE.getflag( "A0015_G", 2, 4, A0015_G_R );				
	cFILE.getflag( "A0015_G", 3, 4, A0015_G_G );				
	cFILE.getflag( "A0015_G", 4, 4, A0015_G_B );				
					
	cFILE.getflag( "A0015_A", 1, 4, A0015_A_A );				
	cFILE.getflag( "A0015_A", 2, 4, A0015_A_R );				
	cFILE.getflag( "A0015_A", 3, 4, A0015_A_G );				
	cFILE.getflag( "A0015_A", 4, 4, A0015_A_B );				
					
	cFILE.getflag( "A0015_R", 1, 4, A0015_R_A );				
	cFILE.getflag( "A0015_R", 2, 4, A0015_R_R );				
	cFILE.getflag( "A0015_R", 3, 4, A0015_R_G );				
	cFILE.getflag( "A0015_R", 4, 4, A0015_R_B );				
	/////////////////				
	cFILE.getflag( "A0016_G", 1, 4, A0016_G_A );				
	cFILE.getflag( "A0016_G", 2, 4, A0016_G_R );				
	cFILE.getflag( "A0016_G", 3, 4, A0016_G_G );				
	cFILE.getflag( "A0016_G", 4, 4, A0016_G_B );				
					
	cFILE.getflag( "A0016_A", 1, 4, A0016_A_A );				
	cFILE.getflag( "A0016_A", 2, 4, A0016_A_R );				
	cFILE.getflag( "A0016_A", 3, 4, A0016_A_G );				
	cFILE.getflag( "A0016_A", 4, 4, A0016_A_B );				
					
	cFILE.getflag( "A0016_R", 1, 4, A0016_R_A );				
	cFILE.getflag( "A0016_R", 2, 4, A0016_R_R );				
	cFILE.getflag( "A0016_R", 3, 4, A0016_R_G );				
	cFILE.getflag( "A0016_R", 4, 4, A0016_R_B );				
	/////////////////				
	cFILE.getflag( "A0017_G", 1, 4, A0017_G_A );				
	cFILE.getflag( "A0017_G", 2, 4, A0017_G_R );				
	cFILE.getflag( "A0017_G", 3, 4, A0017_G_G );				
	cFILE.getflag( "A0017_G", 4, 4, A0017_G_B );				
					
	cFILE.getflag( "A0017_A", 1, 4, A0017_A_A );				
	cFILE.getflag( "A0017_A", 2, 4, A0017_A_R );				
	cFILE.getflag( "A0017_A", 3, 4, A0017_A_G );				
	cFILE.getflag( "A0017_A", 4, 4, A0017_A_B );				
					
	cFILE.getflag( "A0017_R", 1, 4, A0017_R_A );				
	cFILE.getflag( "A0017_R", 2, 4, A0017_R_R );				
	cFILE.getflag( "A0017_R", 3, 4, A0017_R_G );				
	cFILE.getflag( "A0017_R", 4, 4, A0017_R_B );				
	/////////////////					
	
	return TRUE;
	
	}

};

