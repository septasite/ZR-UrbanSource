#pragma once

#ifndef COdbc_H_
#define COdbc_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Windows.h>
#include <sqlext.h> // ODBC library
#include <stdio.h>

#include <odbcinst.h>

// Auto Link Library Files
// To use the installer DLL functions, you must: 
// Use #include < ODBCINST.H>.
// Link with Odbcinst.lib for 16-bit applications.
// Link with Odbccp32.lib for 32-bit applications. 
// #pragma comment (lib,"Odbccp32.lib")
#pragma comment (lib,"odbc32.lib")


// Seconds of database response time
#define DB_RESPONSE_TIME	30
#define DB_CONNECTION_COUNT 10

#define DB_ERROR			-1
#define DB_OK				0

#define DB_USE				1
#define DB_NOT_USE			0

#define DB_CHA_MAX			-2

// string data size
#define USER_ID_LENGTH				20
#define	USER_PASS_LENGTH			20

//#define CHAT_MSG_SIZE				100
#define DB_SVR_NAME_LENGTH			50
#define DB_NAME_LENGTH				50
#define SERVER_NAME_LENGTH			50
//#define MAP_NAME_LENGTH				50

//#define MAX_ONESERVERCHAR_NUM		16 // 한 서버에서 만들수 있는 캐릭터 갯수

class COdbc
{
public:
	static COdbc* GetInstance();	
	static void	ReleaseInstance();

private:
	COdbc(void);
	~COdbc(void);

	static COdbc* SelfInstance;

protected:
   	SQLHENV hEnvGame;  // Handle of sql (void*)	
	SQLHDBC hOdbcGame; // Handle of ODBC (void*)	
	SQLHENV hEnvLog;  // Handle of sql (void*)	
	SQLHDBC hOdbcLog; // Handle of ODBC (void*)
	SQLHENV hEnvShop;  // Handle of sql (void*)	
	SQLHDBC hOdbcShop; // Handle of ODBC (void*)
	SQLHENV hEnvUser;  // Handle of sql (void*)	
	SQLHDBC hOdbcUser; // Handle of ODBC (void*)

	int			nDBTimeOut;

public:	

	int			OpenGameDB();
	int			OpenLogDB();
	int			OpenShopDB();
	int			OpenUserDB();
		
	void		CloseGameDB();
	void		CloseLogDB();
	void		CloseShopDB();
	void		CloseUserDB();

	SQLHDBC		ConnectUser() {return hOdbcUser;}
	SQLHDBC		ConnectShop() {return hOdbcShop;}
	SQLHDBC		ConnectGame() {return hOdbcGame;}


	int			ExecuteSQL	(CString strSQL);
};

#endif COdbc_H_