///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include <stdio.h>
#include <string.h>
#include <time.h>
#include "CCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CToolCfg* CToolCfg::SelfInstance = NULL;

CToolCfg::CToolCfg()
{
}

CToolCfg* CToolCfg::GetInstance()
{
	if (SelfInstance == NULL)
		SelfInstance = new CToolCfg();

	return SelfInstance;
}

void CToolCfg::ReleaseInstance()
{
	if (SelfInstance != NULL)
	{
		delete SelfInstance;
		SelfInstance = NULL;
	}
}

CToolCfg::~CToolCfg()
{
}

CString	CToolCfg::GetAppPath ()
{
	CString strFullPath;
	CString strCommandLine;

	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(::AfxGetInstanceHandle(), szPath, MAX_PATH);
	strCommandLine = szPath;

	if ( !strCommandLine.IsEmpty() )
	{
		DWORD dwFind = strCommandLine.ReverseFind ( '\\' );
		if ( dwFind != -1 )
		{
			strFullPath = strCommandLine.Left ( dwFind );
			
			if ( !strFullPath.IsEmpty() )
			if ( strFullPath.GetAt(0) == '"' )
				strFullPath = strFullPath.Right ( strFullPath.GetLength() - 1 );
		}
	}

	return strFullPath;
}

BOOL CToolCfg::Load()
{
	CString strFileName = GetAppPath() + "\\RanManager.ini";
	
	FILE *oFile = NULL;
	char szLine[1024+1];

	if ((oFile = fopen(strFileName.GetString(), "r")) == NULL) 
	{
		CString strTemp;
		strTemp.Format("%s Not Found!. %s Must be in Root Folder!",strFileName,strFileName);
		MessageBox(NULL,strTemp,"Error",MB_OK);
		return FALSE;
	}

	while (::fgets(szLine, 1024, oFile)) Process(szLine);
	
	fclose(oFile);
	return TRUE;
}

int CToolCfg::Process(char* szLine)
{
	char seps[]   = " ,\t\n";
	char *token;

	token = strtok(szLine, seps);
	while (token != NULL)
	{	
		if (strcmp(token, "//") == 0) return 0;
			
		if (::strcmp(token, "RAN_GAME_ODBC") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szGame, DB_SVR_NAME_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "RAN_LOG_ODBC") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szLog, DB_NAME_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "RAN_SHOP_ODBC") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szShop, DB_NAME_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "RAN_USER_ODBC") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szUser, DB_NAME_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "RAN_GAME_DB") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szGameDb, DB_SVR_NAME_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "RAN_LOG_DB") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szLogDb, DB_NAME_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "RAN_SHOP_DB") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szShopDb, DB_NAME_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "RAN_USER_DB") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szUserDb, DB_NAME_LENGTH, token);		
			else	return 0;	}
		else if (::strcmp(token, "USERNAME") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szUserId, USER_ID_LENGTH, token);	
			else	return 0;	}
		else if (::strcmp(token, "PASSWORD") == 0) {
			token = ::strtok(NULL, seps );
			if (token)	::StringCchCopy(szUserPass, USER_PASS_LENGTH, token);	
			else	return 0;	}
		else	{}

		token = ::strtok( NULL, seps );
	}
	return 0;
}

