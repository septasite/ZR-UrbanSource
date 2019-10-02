#include "StdAfx.h"
//#include <strstream>
#include "COdbc.h"
#include "strsafe.h" // Safe string function
#include "CCfg.h"

COdbc* COdbc::SelfInstance = NULL;

COdbc::COdbc(void)
{
	hEnvGame = NULL;  // Handle of sql (void*)	
	hOdbcGame= NULL;; // Handle of ODBC (void*)	
	hEnvLog = NULL;  // Handle of sql (void*)	
	hOdbcLog= NULL;; // Handle of ODBC (void*)	
	hEnvShop = NULL;  // Handle of sql (void*)	
	hOdbcShop= NULL;; // Handle of ODBC (void*)	
	hEnvUser = NULL;  // Handle of sql (void*)	
	hOdbcUser= NULL;; // Handle of ODBC (void*)	
}

COdbc* COdbc::GetInstance()
{
	if (SelfInstance == NULL)
		SelfInstance = new COdbc();

	return SelfInstance;
}

void COdbc::ReleaseInstance()
{
	if (SelfInstance != NULL)
	{
		delete SelfInstance;
		SelfInstance = NULL;
	}
}

COdbc::~COdbc(void)
{
	if (hOdbcGame != NULL)
	{
		::SQLDisconnect(hOdbcGame);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcGame);
		hOdbcGame = NULL;
	}

	if (hEnvGame != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvGame);
		hEnvGame = NULL;
	}

	if (hOdbcLog != NULL)
	{
		::SQLDisconnect(hOdbcLog);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcLog);
		hOdbcLog = NULL;
	}

	if (hEnvLog != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvLog);
		hEnvLog = NULL;
	}

	if (hOdbcShop != NULL)
	{
		::SQLDisconnect(hOdbcShop);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcShop);
		hOdbcShop = NULL;
	}

	if (hEnvShop != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvShop);
		hEnvShop = NULL;
	}

	if (hOdbcUser != NULL)
	{
		::SQLDisconnect(hOdbcUser);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcUser);
		hOdbcUser = NULL;
	}

	if (hEnvUser != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvUser);
		hEnvUser = NULL;
	}
}

int	COdbc::OpenGameDB()
{
	SQLRETURN sReturn = 0; // SQL return value (short)

	// ODBC allocate environment memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvGame);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		return DB_ERROR;
	}

	// ODBC set environment
	// version
	sReturn = ::SQLSetEnvAttr(hEnvGame, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvGame);
		hEnvGame = NULL;
		return DB_ERROR;
	}
    
	// ODBC allocate connection memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_DBC, hEnvGame, &hOdbcGame);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcGame);
		hOdbcGame = NULL;
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvGame);
		hEnvGame = NULL;
		return DB_ERROR;
	}

	// ODBC connect
	// Login time out 5 sec
	sReturn = ::SQLSetConnectAttr(hOdbcGame, 50, (void*) SQL_LOGIN_TIMEOUT, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{	
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvGame);
		hEnvGame = NULL;
		return DB_ERROR;
	}

	sReturn = ::SQLConnect(hOdbcGame, 
		(SQLCHAR*) CToolCfg::GetInstance()->szGame,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserId,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserPass,
		SQL_NTS);

	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
	{	
		return DB_OK;
	}
	else
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvGame);
		hEnvGame = NULL;
		return DB_ERROR;
	}
}

int	COdbc::OpenLogDB()
{
	SQLRETURN sReturn = 0; // SQL return value (short)

	// ODBC allocate environment memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvLog);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		return DB_ERROR;
	}

	// ODBC set environment
	// version
	sReturn = ::SQLSetEnvAttr(hEnvLog, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvLog);
		hEnvLog = NULL;
		return DB_ERROR;
	}
    
	// ODBC allocate connection memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_DBC, hEnvLog, &hOdbcLog);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcLog);
		hOdbcLog = NULL;
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvLog);
		hEnvLog = NULL;
		return DB_ERROR;
	}

	// ODBC connect
	// Login time out 5 sec
	sReturn = ::SQLSetConnectAttr(hOdbcLog, 50, (void*) SQL_LOGIN_TIMEOUT, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{	
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvLog);
		hEnvLog = NULL;
		return DB_ERROR;
	}

	sReturn = ::SQLConnect(hOdbcLog, 
		(SQLCHAR*) CToolCfg::GetInstance()->szLog,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserId,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserPass,
		SQL_NTS);

	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
	{	
		return DB_OK;
	}
	else
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvLog);
		hEnvLog = NULL;
		return DB_ERROR;
	}
}

int	COdbc::OpenShopDB()
{
	SQLRETURN sReturn = 0; // SQL return value (short)

	// ODBC allocate environment memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvShop);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		return DB_ERROR;
	}

	// ODBC set environment
	// version
	sReturn = ::SQLSetEnvAttr(hEnvShop, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvShop);
		hEnvShop = NULL;
		return DB_ERROR;
	}
    
	// ODBC allocate connection memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_DBC, hEnvShop, &hOdbcShop);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcShop);
		hOdbcShop = NULL;
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvShop);
		hEnvShop = NULL;
		return DB_ERROR;
	}

	// ODBC connect
	// Shopin time out 5 sec
	sReturn = ::SQLSetConnectAttr(hOdbcShop, 50, (void*) SQL_LOGIN_TIMEOUT, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{	
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvShop);
		hEnvShop = NULL;
		return DB_ERROR;
	}

	sReturn = ::SQLConnect(hOdbcShop, 
		(SQLCHAR*) CToolCfg::GetInstance()->szShop,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserId,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserPass,
		SQL_NTS);

	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
	{	
		return DB_OK;
	}
	else
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvShop);
		hEnvShop = NULL;
		return DB_ERROR;
	}
}

int	COdbc::OpenUserDB()
{
	SQLRETURN sReturn = 0; // SQL return value (short)

	// ODBC allocate environment memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvUser);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		return DB_ERROR;
	}

	// ODBC set environment
	// version
	sReturn = ::SQLSetEnvAttr(hEnvUser, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{		
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvUser);
		hEnvUser = NULL;
		return DB_ERROR;
	}
    
	// ODBC allocate connection memory
	sReturn = ::SQLAllocHandle(SQL_HANDLE_DBC, hEnvUser, &hOdbcUser);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcUser);
		hOdbcUser = NULL;
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvUser);
		hEnvUser = NULL;
		return DB_ERROR;
	}

	// ODBC connect
	// Userin time out 5 sec
	sReturn = ::SQLSetConnectAttr(hOdbcUser, 50, (void*) SQL_LOGIN_TIMEOUT, 0);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{	
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvUser);
		hEnvUser = NULL;
		return DB_ERROR;
	}

	sReturn = ::SQLConnect(hOdbcUser, 
		(SQLCHAR*) CToolCfg::GetInstance()->szUser,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserId,
		SQL_NTS,
		(SQLCHAR*) CToolCfg::GetInstance()->szUserPass,
		SQL_NTS);

	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
	{	
		return DB_OK;
	}
	else
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvUser);
		hEnvUser = NULL;
		return DB_ERROR;
	}
}

void COdbc::CloseGameDB()
{
	if (hOdbcGame != NULL)
	{
		::SQLDisconnect(hOdbcGame);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcGame);
		hOdbcGame = NULL;
	}

	if (hEnvGame != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvGame);
		hEnvGame = NULL;
	}
}

void COdbc::CloseLogDB()
{
	if (hOdbcLog != NULL)
	{
		::SQLDisconnect(hOdbcLog);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcLog);
		hOdbcLog = NULL;
	}

	if (hEnvLog != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvLog);
		hEnvLog = NULL;
	}
}

void COdbc::CloseShopDB()
{
	if (hOdbcShop != NULL)
	{
		::SQLDisconnect(hOdbcShop);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcShop);
		hOdbcShop = NULL;
	}

	if (hEnvShop != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvShop);
		hEnvShop = NULL;
	}
}

void COdbc::CloseUserDB()
{
	if (hOdbcUser != NULL)
	{
		::SQLDisconnect(hOdbcUser);
		::SQLFreeHandle(SQL_HANDLE_DBC, hOdbcUser);
		hOdbcUser = NULL;
	}

	if (hEnvUser != NULL)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, hEnvUser);
		hEnvUser = NULL;
	}
}

int	COdbc::ExecuteSQL(CString strSQL)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)
	
	// Prepare statement handle
	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, hOdbcGame, &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return DB_ERROR;
	}
	
	sReturn = ::SQLExecDirect(hStmt, 
							(SQLCHAR*) strSQL.GetString(), 
							SQL_NTS);
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO || sReturn == SQL_NO_DATA)
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
		return DB_OK;
	}
	else
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
		return DB_ERROR;
	}
}