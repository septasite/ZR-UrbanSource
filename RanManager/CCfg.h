
#ifndef CToolCfg_H_
#define CToolCfg_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRSAFE_LIB
#define STRSAFE_NO_DEPRECATE

#include "strsafe.h" // Safe string function

#pragma comment (lib,"strsafe.lib")

#define USER_ID_LENGTH				20
#define	USER_PASS_LENGTH				20

#define DB_SVR_NAME_LENGTH			50
#define DB_NAME_LENGTH				50

#define SM_MAX_PHONE_LIST 10

class CToolCfg
{
protected:
	
public:
	static CToolCfg* GetInstance();
	static void	ReleaseInstance();

	int			Process(char* szLine);
	BOOL		Load();
	CString		GetAppPath();

	char		szGame[DB_SVR_NAME_LENGTH+1];
	char		szLog[DB_SVR_NAME_LENGTH+1];
	char		szShop[DB_SVR_NAME_LENGTH+1];
	char		szUser[DB_SVR_NAME_LENGTH+1];

	char		szGameDb[DB_NAME_LENGTH+1];
	char		szLogDb[DB_NAME_LENGTH+1];
	char		szShopDb[DB_NAME_LENGTH+1];
	char		szUserDb[DB_NAME_LENGTH+1];

	char		szUserId[USER_ID_LENGTH+1];
	char		szUserPass[USER_PASS_LENGTH+1];
	

private:
	CToolCfg();
	virtual ~CToolCfg();
	static CToolCfg* SelfInstance;

};

#endif // CToolCfg_H_