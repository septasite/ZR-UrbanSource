#include "stdafx.h"
#include "LogScript.h"


namespace LOGSCRIPT
{
	char m_szFullDir[MAX_PATH] = "";
	TCHAR RM_SAVE[MAX_PATH]			= _T("\\RanManagerLogs\\");

	void	InitLog(const char *szAppPath)
	{
		StringCchCopy( m_szFullDir, MAX_PATH, szAppPath );
		StringCchCat( m_szFullDir, MAX_PATH, RM_SAVE );
		CreateDirectory ( m_szFullDir, NULL );
	}

	void	LogToFile( const char *szFileName, const char *szFormat, ... )
	{
		va_list argList;
		char szBuffer[2048] = "";

		va_start(argList, szFormat);
		StringCbVPrintf(szBuffer, 2048, szFormat, argList);
		va_end(argList);

		char	szFullPathFileName[256] = "";

		StringCchCopy( szFullPathFileName, 256, m_szFullDir );
		StringCchCat( szFullPathFileName, 256, szFileName );

		FILE *fp;
		fp = fopen ( szFullPathFileName, "at" );
		if ( fp )
		{
			fprintf ( fp, "%s\n", szBuffer );
			fclose(fp);
		}
	}
};