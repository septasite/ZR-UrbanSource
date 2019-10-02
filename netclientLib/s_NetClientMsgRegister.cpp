///////////////////////////////////////////////////////////////////////////////
// s_NetClientMsg.cpp
//
// class CNetClient
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "s_NetClient.h"
#include "s_CClientConsoleMsg.h"
#include <stdlib.h>
#include "GLContrlMsg.h"
#include "china_md5.h"
#include <string.h>
#include <wchar.h>
#include "s_CRandomNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int CNetClient::SndRegister( 
				const TCHAR* szUserID,
		        const TCHAR* szUserPassword,
				const TCHAR* szUserPassword2,
				const TCHAR* szUserEmail,
				const TCHAR* szCaptcha )
{

	CHINA_NET_REGISTER_DATA nld;
		

	CHINA_MD5::MD5 md5;
	CHINA_MD5::MD5 md52;

	size_t nLength = 0;
	size_t nLength2 = 0;
	HRESULT sRet = StringCchLength( szUserPassword, USR_PASS_LENGTH, &nLength );

	HRESULT sRet2 = StringCchLength( szUserPassword2, USR_PASS_LENGTH, &nLength2 );
	
	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;
	
	if (sRet2 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword), nLength );	
	md52.update( reinterpret_cast<const unsigned char*> (szUserPassword2), nLength2 );	

	std::string strPass = md5.asString();
	std::string strPass2 = md52.asString();

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szUserid,   USR_ID_LENGTH+1, szUserID ); 
	StringCchCopy( nld.szUserEmail,   USR_EMAIL+1, szUserEmail ); 
	StringCchCopy( nld.szPassword, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( nld.szPassword2, USR_PASS_LENGTH, strPass2.c_str() );
	
	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szUserid, USR_ID_LENGTH+1 );
	m_Tea.encrypt( nld.szUserEmail, USR_EMAIL+1 );
	m_Tea.encrypt( nld.szPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szPassword2, USR_PASS_LENGTH );

	return Send((char *) &nld);
}
int CNetClient::SndChangePin( 
		        const TCHAR* szUserOPassword2,
		        const TCHAR* szUserPassword,
				const TCHAR* szUserPassword2,
				const TCHAR* szCaptcha )
{

	CHINA_NET_CPN_DATA nld;
		

	CHINA_MD5::MD5 md5;
	CHINA_MD5::MD5 md52;
	CHINA_MD5::MD5 md53;

	size_t nLength = 0;
	size_t nLength2 = 0;
	size_t nLength3 = 0;

	HRESULT sRet = StringCchLength( szUserPassword, USR_PASS_LENGTH, &nLength );
	
	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	HRESULT sRet2 = StringCchLength( szUserPassword2, USR_PASS_LENGTH, &nLength2 );
	
	if (sRet2 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;
	
	HRESULT sRet3 = StringCchLength( szUserOPassword2, USR_PASS_LENGTH, &nLength3 );
	
	if (sRet3 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword), nLength );	
	std::string strPass = md5.asString();
	md52.update( reinterpret_cast<const unsigned char*> (szUserPassword2), nLength2 );
	std::string strPass2 = md52.asString();
	md53.update( reinterpret_cast<const unsigned char*> (szUserOPassword2), nLength3 );	
	std::string stroPass2 = md53.asString();


	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szPassword, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( nld.szPassword2, USR_PASS_LENGTH, strPass2.c_str() );
	StringCchCopy( nld.szOPassword2, USR_PASS_LENGTH, stroPass2.c_str() );
	
	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szPassword2, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szOPassword2, USR_PASS_LENGTH );

	return Send((char *) &nld);
}
int CNetClient::SndChangePassword(
				const TCHAR* szUserOPassword,
		        const TCHAR* szUserPassword,
				const TCHAR* szUserPassword2,
				const TCHAR* szCaptcha )
{

	CHINA_NET_CP_DATA nld;
		

	CHINA_MD5::MD5 md5;
	CHINA_MD5::MD5 md52;
	CHINA_MD5::MD5 md53;

	size_t nLength = 0;
	size_t nLength2 = 0;
	size_t nLength3 = 0;

	HRESULT sRet = StringCchLength( szUserPassword, USR_PASS_LENGTH, &nLength );
	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	HRESULT sRet2 = StringCchLength( szUserPassword2, USR_PASS_LENGTH, &nLength2 );
	if (sRet2 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	HRESULT sRet3 = StringCchLength( szUserOPassword, USR_PASS_LENGTH, &nLength3 );
	if (sRet3 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	
	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword), nLength );	
	std::string strPass = md5.asString();
	md52.update( reinterpret_cast<const unsigned char*> (szUserPassword2), nLength2 );	
	std::string strPass2 = md52.asString();
	md53.update( reinterpret_cast<const unsigned char*> (szUserOPassword), nLength3 );	
	std::string strOPass = md53.asString();
	

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szPassword, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( nld.szOPassword, USR_PASS_LENGTH, strOPass.c_str() );
	StringCchCopy( nld.szPassword2, USR_PASS_LENGTH, strPass2.c_str() );

	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szOPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szPassword2, USR_PASS_LENGTH );

	return Send((char *) &nld);
}
int CNetClient::SndChangeEmail( 
		        const TCHAR* szUserPassword,
				const TCHAR* szUserPassword2,
				const TCHAR* szUserEmail,
				const TCHAR* szCaptcha )
{

	CHINA_NET_CE_DATA nld;
		

	CHINA_MD5::MD5 md5;
	CHINA_MD5::MD5 md52;

	size_t nLength = 0;
	size_t nLength2 = 0;
	HRESULT sRet = StringCchLength( szUserPassword, USR_PASS_LENGTH, &nLength );

	HRESULT sRet2 = StringCchLength( szUserPassword2, USR_PASS_LENGTH, &nLength2 );
	
	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;
	
	if (sRet2 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword), nLength );	
	md52.update( reinterpret_cast<const unsigned char*> (szUserPassword2), nLength2 );	

	std::string strPass = md5.asString();
	std::string strPass2 = md52.asString();

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szUserEmail,   USR_EMAIL+1, szUserEmail ); 
	StringCchCopy( nld.szPassword, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( nld.szPassword2, USR_PASS_LENGTH, strPass2.c_str() );
	
	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szUserEmail, USR_EMAIL+1 );
	m_Tea.encrypt( nld.szPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szPassword2, USR_PASS_LENGTH );

	return Send((char *) &nld);
}
int CNetClient::SndTopUp( 
		        const TCHAR* szCode,
				const TCHAR* szPin,
				const TCHAR* szCaptcha )
{

	CHINA_NET_TOPUP_DATA nld;

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szPin,   USR_PASS_LENGTH, szPin ); 
	StringCchCopy( nld.szCode, USR_PASS_LENGTH, szCode );
	
	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szPin, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szCode, USR_PASS_LENGTH );

	return Send((char *) &nld);
}

int CNetClient::SndGameTimeCVT( 
				const TCHAR* szCaptcha )
{

	CHINA_NET_GTCVT_DATA nld;

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	
	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	return Send((char *) &nld);
}

int CNetClient::SndPremiumPointCVT(
				const TCHAR* szValue,
				const TCHAR* szCaptcha )
{

	CHINA_NET_PPCVT_DATA nld;

	StringCchCopy( nld.szValue,   USR_CAPTCHA+1, szValue ); 
	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	
	m_Tea.encrypt( nld.szValue, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	return Send((char *) &nld);
}

int CNetClient::SndResetPassword(
				const TCHAR* szUserID,
				const TCHAR* szUserPassword2,
				const TCHAR* szCaptcha )
{

	CHINA_NET_RPS_DATA nld;
		
	CHINA_MD5::MD5 md5;

	size_t nLength = 0;

	HRESULT sRet = StringCchLength( szUserPassword2, USR_PASS_LENGTH, &nLength );
	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	
	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword2), nLength );	
	std::string strPass2 = md5.asString();

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szUserid,   USR_ID_LENGTH+1, szUserID ); 
	StringCchCopy( nld.szPassword2, USR_PASS_LENGTH, strPass2.c_str() );

	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szUserid, USR_ID_LENGTH+1 );
	m_Tea.encrypt( nld.szPassword2, USR_PASS_LENGTH );

	return Send((char *) &nld);
}

int CNetClient::SndResetPassword2(
				const TCHAR* szUserPassword,
				const TCHAR* szUserPassword2,
				const TCHAR* szCaptcha )
{

	CHINA_NET_RPS2_DATA nld;
		
	CHINA_MD5::MD5 md5;
	CHINA_MD5::MD5 md52;

	size_t nLength = 0;
	size_t nLength2 = 0;

	HRESULT sRet = StringCchLength( szUserPassword, USR_PASS_LENGTH, &nLength );
	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;
	HRESULT sRet2 = StringCchLength( szUserPassword2, USR_PASS_LENGTH, &nLength2 );
	if (sRet2 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	
	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword), nLength );	
	std::string strPass = md5.asString();
	md52.update( reinterpret_cast<const unsigned char*> (szUserPassword2), nLength2 );	
	std::string strPass2 = md52.asString();

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szPassword,   USR_ID_LENGTH+1, strPass.c_str() ); 
	StringCchCopy( nld.szPassword2, USR_PASS_LENGTH, strPass2.c_str() );

	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szPassword2, USR_PASS_LENGTH );

	return Send((char *) &nld);
}



int CNetClient::SndResetPin( 
				const TCHAR* szUserEmail,
		        const TCHAR* szUserPassword,
				const TCHAR* szCaptcha )
{

	CHINA_NET_RPN_DATA nld;
		

	CHINA_MD5::MD5 md5;
	CHINA_MD5::MD5 md52;
	TCHAR szPassword2[USR_PASS_LENGTH] = {0};
	
	SERVER_UTIL::CRandomNumber random;
	CString str;
	if ( random.GenerateRandomString( str, 8 , 3, 2, 3 ) )
	{	
		StringCchCopy( szPassword2, USR_PASS_LENGTH, str.GetString() );
	}
	size_t nLength = 0;
	size_t nLength2 = 0;

	HRESULT sRet = StringCchLength( szUserPassword, USR_PASS_LENGTH, &nLength );
	HRESULT sRet2 = StringCchLength( szPassword2, USR_PASS_LENGTH, &nLength2 );

	if (sRet == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;
	
	if (sRet2 == STRSAFE_E_INVALID_PARAMETER)
		return NET_ERROR;

	md5.update( reinterpret_cast<const unsigned char*> (szUserPassword), nLength );		
	md52.update( reinterpret_cast<const unsigned char*> (szPassword2), nLength2 );

	std::string strPass = md5.asString();
	std::string strPin = md52.asString();

	StringCchCopy( nld.szCaptcha,   USR_CAPTCHA+1, szCaptcha ); 
	StringCchCopy( nld.szUserEmail,   USR_EMAIL+1, szUserEmail ); 
	StringCchCopy( nld.szPassword, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( nld.szPassword2, USR_PASS_LENGTH, strPin.c_str()  );
	StringCchCopy( nld.szPassword2Hold, USR_PASS_LENGTH, str.GetString() );
	
	
	m_Tea.encrypt( nld.szCaptcha, USR_CAPTCHA+1 );
	m_Tea.encrypt( nld.szUserEmail, USR_EMAIL+1 );
	m_Tea.encrypt( nld.szPassword, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szPassword2, USR_PASS_LENGTH );
	m_Tea.encrypt( nld.szPassword2Hold, USR_PASS_LENGTH );

	return Send((char *) &nld);
}