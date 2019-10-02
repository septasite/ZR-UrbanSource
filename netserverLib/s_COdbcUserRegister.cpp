#include "stdafx.h"
#include "s_COdbcManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int COdbcManager::UserRegister(
	const TCHAR* szUsrID, 
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szUsrEmail,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strPasswd = szPasswd;
	strPasswd.Trim(_T(" "));
	strPasswd.Replace(_T("'"), _T("''"));

	CString strPasswd2 = szPasswd2;
	strPasswd2.Trim(_T(" "));
	strPasswd2.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	CString strEmail = szUsrEmail;
	strEmail.Trim(_T(" "));
	strEmail.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_register('%s','%s','%s','%s',?)}", 
												strUserID.GetString(),
												strPasswd.GetString(),
												strPasswd2.GetString(),
												strEmail.GetString());

	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}

int COdbcManager::UserChangePass(
	const TCHAR* szUsrID, 
	const TCHAR* szOPasswd, 
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strOPasswd = szOPasswd;
	strOPasswd.Trim(_T(" "));
	strOPasswd.Replace(_T("'"), _T("''"));

	CString strPasswd = szPasswd;
	strPasswd.Trim(_T(" "));
	strPasswd.Replace(_T("'"), _T("''"));

	CString strPasswd2 = szPasswd2;
	strPasswd2.Trim(_T(" "));
	strPasswd2.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_changepass('%s','%s','%s','%s',?)}", 
												strUserID.GetString(),
												strOPasswd.GetString(),
												strPasswd.GetString(),
												strPasswd2.GetString());

	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}
int COdbcManager::UserChangePin(
	const TCHAR* szUsrID, 
	const TCHAR* szOPasswd2, 
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strOPasswd2 = szOPasswd2;
	strOPasswd2.Trim(_T(" "));
	strOPasswd2.Replace(_T("'"), _T("''"));

	CString strPasswd = szPasswd;
	strPasswd.Trim(_T(" "));
	strPasswd.Replace(_T("'"), _T("''"));

	CString strPasswd2 = szPasswd2;
	strPasswd2.Trim(_T(" "));
	strPasswd2.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_changepin('%s','%s','%s','%s',?)}", 
												strUserID.GetString(),
												strOPasswd2.GetString(),
												strPasswd.GetString(),
												strPasswd2.GetString());

	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}
int COdbcManager::UserChangeEmail(
	const TCHAR* szUsrID, 
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szUsrEmail,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strPasswd = szPasswd;
	strPasswd.Trim(_T(" "));
	strPasswd.Replace(_T("'"), _T("''"));

	CString strPasswd2 = szPasswd2;
	strPasswd2.Trim(_T(" "));
	strPasswd2.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	CString strEmail = szUsrEmail;
	strEmail.Trim(_T(" "));
	strEmail.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_changeemail('%s','%s','%s','%s',?)}", 
												strUserID.GetString(),
												strPasswd.GetString(),
												strPasswd2.GetString(),
												strEmail.GetString());

	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}
int COdbcManager::UserTopUp(
	const TCHAR* szUsrID, 
	const TCHAR* szCode, 
	const TCHAR* szPin,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strCode = szCode;
	strCode.Trim(_T(" "));
	strCode.Replace(_T("'"), _T("''"));

	CString strPin = szPin;
	strPin.Trim(_T(" "));
	strPin.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_topup('%s','%s','%s','%s',?)}", 
												strUserID.GetString(),
												strCode.GetString(),
												strPin.GetString(),
												strCaptcha.GetString());

	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}
int COdbcManager::UserGameTimeCVT(
	const TCHAR* szUsrID, 
	const DWORD	dwGameTime,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));


	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_gametimecvt('%s',?)}", 
												strUserID.GetString());

	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}
int COdbcManager::UserPremiumPointCVT(
	const TCHAR* szUsrID, 
	const TCHAR* szValue,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	CString strValue = szValue;
	strValue.Trim(_T(" "));
	strValue.Replace(_T("'"), _T("''"));


	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_premiumpointcvt('%s','%s',?)}", 
												strUserID.GetString(),strValue.GetString());

	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}

int COdbcManager::UserResetPass(
	const TCHAR* szUsrID, 
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strPass2 = szPasswd2;
	strPass2.Trim(_T(" "));
	strPass2.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_resetpass('%s','%s',?)}", 
												strUserID.GetString(),
												strPass2.GetString());
	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}

int COdbcManager::UserResetPass2(
	const TCHAR* szUsrID, 
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	
	CString strPass = szPasswd;
	strPass.Trim(_T(" "));
	strPass.Replace(_T("'"), _T("''"));

	CString strPass2 = szPasswd2;
	strPass2.Trim(_T(" "));
	strPass2.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_resetpass2('%s','%s','%s',?)}", 
												strUserID.GetString(),
												strPass.GetString(),
												strPass2.GetString());
	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}

int COdbcManager::UserResetPin(
	const TCHAR* szUsrID, 
	const TCHAR* szUsrEmail,
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha)
{
	CString strUserID = szUsrID;
	strUserID.Trim(_T(" "));
	strUserID.Replace(_T("'"), _T("''"));

	CString strEmail = szUsrEmail;
	strEmail.Trim(_T(" "));
	strEmail.Replace(_T("'"), _T("''"));
	
	CString strPass = szPasswd;
	strPass.Trim(_T(" "));
	strPass.Replace(_T("'"), _T("''"));

	CString strPass2 = szPasswd2;
	strPass2.Trim(_T(" "));
	strPass2.Replace(_T("'"), _T("''"));

	CString strCaptcha = szCaptcha;
	strCaptcha.Trim(_T(" "));
	strCaptcha.Replace(_T("'"), _T("''"));

	TCHAR szTemp[512] = {0};

	_snprintf( szTemp, 512, "{call user_resetpin('%s','%s','%s','%s',?)}", 
												strUserID.GetString(),
												strEmail.GetString(),
												strPass.GetString(),
												strPass2.GetString());
	int nReturn = m_pUserDB->ExecuteSpInt(szTemp);

	return nReturn;
}