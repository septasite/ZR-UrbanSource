#include "stdafx.h"

#include "s_CDbAction.h"
#include "s_CSessionServer.h"
#include "s_CFieldServer.h"
#include "s_CAgentServer.h"

#include "../RanClientLib/G-Logic/GLCharData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CAgentUserRegister::CAgentUserRegister(
	const TCHAR* szUserID,
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szUserEmail,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )
	, m_strPasswd( szPasswd )	
	, m_strPasswd2( szPasswd2 )	
	, m_strUserEmail ( szUserEmail )
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserRegister::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserRegister(m_strUserID.GetString(),
													     m_strPasswd.GetString(),
													     m_strPasswd2.GetString(),
													     m_strUserEmail.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_REGISTER_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_REGISTER_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szUserEmail,	USR_EMAIL+1, m_strUserEmail.GetString()); // id
	StringCchCopy(NetMsgFB.szUserpass,		USR_PASS_LENGTH+1, m_strPasswd.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass2,		USR_PASS_LENGTH+1, m_strPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_REGISTER_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserREGISTER result %d DB ERROR", nResult);
		 pTemp->ChinaMsgRegisterBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_REGISTER_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserRegister result %d REGISTER FAIL", nResult);
		 pTemp->ChinaMsgRegisterBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_REGISTER_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserRegister result UserNum %d success!", nResult);
		 pTemp->ChinaMsgRegisterBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}
CAgentUserChangePin::CAgentUserChangePin(
	const TCHAR* szUserID,
	const TCHAR* szOPasswd2,
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )
	, m_strOPasswd2( szOPasswd2 )	
	, m_strPasswd( szPasswd )	
	, m_strPasswd2( szPasswd2 )	
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserChangePin::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserChangePin(m_strUserID.GetString(),
														 m_strOPasswd2.GetString(),
													     m_strPasswd.GetString(),
													     m_strPasswd2.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_CPN_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_PIN_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szUserOpass2,		USR_PASS_LENGTH+1, m_strOPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass,		USR_PASS_LENGTH+1, m_strPasswd.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass2,		USR_PASS_LENGTH+1, m_strPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_PIN_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserCPIN result %d DB ERROR", nResult);
		 pTemp->MsgChangePinBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_PIN_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserCPIN result %d UPDATE FAIL", nResult);
		 pTemp->MsgChangePinBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_PIN_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserCPIN result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgChangePinBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}
CAgentUserChangePassword::CAgentUserChangePassword(
	const TCHAR* szUserID,
	const TCHAR* szOPasswd, 
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )
	, m_strOPasswd( szOPasswd )	
	, m_strPasswd( szPasswd )	
	, m_strPasswd2( szPasswd2 )	
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserChangePassword::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserChangePass(m_strUserID.GetString(),
														 m_strOPasswd.GetString(),
													     m_strPasswd.GetString(),
													     m_strPasswd2.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_CP_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_PASS_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szUseropass,		USR_PASS_LENGTH+1, m_strOPasswd.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass,		USR_PASS_LENGTH+1, m_strPasswd.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass2,		USR_PASS_LENGTH+1, m_strPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_PASS_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserCPASS result %d DB ERROR", nResult);
		 pTemp->MsgChangePassBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_PASS_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserCPASS result %d UPDATE FAIL", nResult);
		 pTemp->MsgChangePassBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_PASS_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserCPASS result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgChangePassBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}
CAgentUserChangeEmail::CAgentUserChangeEmail(
	const TCHAR* szUserID,
	const TCHAR* szPasswd, 
	const TCHAR* szPasswd2,
	const TCHAR* szUserEmail,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )
	, m_strPasswd( szPasswd )	
	, m_strPasswd2( szPasswd2 )	
	, m_strUserEmail ( szUserEmail )
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserChangeEmail::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserChangeEmail(m_strUserID.GetString(),
													     m_strPasswd.GetString(),
													     m_strPasswd2.GetString(),
													     m_strUserEmail.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_CE_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_EMAIL_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szUserEmail,	USR_EMAIL+1, m_strUserEmail.GetString()); // id
	StringCchCopy(NetMsgFB.szUserpass,		USR_PASS_LENGTH+1, m_strPasswd.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass2,		USR_PASS_LENGTH+1, m_strPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_EMAIL_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserCEMAIL result %d DB ERROR", nResult);
		 pTemp->MsgChangeEmailBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_EMAIL_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserCEMAIL result %d UPDATE FAIL", nResult);
		 pTemp->MsgChangeEmailBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_EMAIL_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserCEMAIL result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgChangeEmailBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}

CAgentUserTopUp::CAgentUserTopUp(
	const TCHAR* szUserID,
	const TCHAR* szCode, 
	const TCHAR* szPin,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )
	, m_strCode( szCode )	
	, m_strPin( szPin )	
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserTopUp::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserTopUp(m_strUserID.GetString(),
													     m_strCode.GetString(),
													     m_strPin.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_TOPUP_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_TOPUP_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szCode,		USR_PASS_LENGTH+1, m_strCode.GetString()); // ip
	StringCchCopy(NetMsgFB.szPin,		USR_PASS_LENGTH+1, m_strPin.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_TOPUP_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserTOPUP result %d DB ERROR", nResult);
		 pTemp->MsgTopUpBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_TOPUP_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserTOPUP result %d TOPUP FAIL", nResult);
		 pTemp->MsgTopUpBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_TOPUP_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserTOPUP result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgTopUpBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}

CAgentUserGameTimeCVT::CAgentUserGameTimeCVT(
	const TCHAR* szUserID,
	const TCHAR* szCaptcha,
	DWORD  dwGameTime,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )
	, m_strCaptcha( szCaptcha )
	, m_dwGameTime ( dwGameTime )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserGameTimeCVT::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	
	CConsoleMessage::GetInstance()->Write("CAgentUserTOPUP");
	int nResult = COdbcManager::GetInstance()->UserGameTimeCVT(m_strUserID.GetString(),
														 m_dwGameTime,
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_GTCVT_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_GT2VP_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip
	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_GT2VP_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserGT2VP result %d DB ERROR", nResult);
		 pTemp->MsgGameTimeCVTBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_GT2VP_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserGT2VP result %d CVT FAIL", nResult);
		 pTemp->MsgGameTimeCVTBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_GT2VP_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserGT2VP result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgGameTimeCVTBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}
//
CAgentUserPremiumPointCVT::CAgentUserPremiumPointCVT(
	const TCHAR* szUserID,
	const TCHAR* szValue,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )
	, m_strCaptcha( szCaptcha )
	, m_strValue ( szValue )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserPremiumPointCVT::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	
	CConsoleMessage::GetInstance()->Write("CAgentUserCONVERTPP");
	int nResult = COdbcManager::GetInstance()->UserPremiumPointCVT(m_strUserID.GetString(),
														 m_strValue.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_PPCVT_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_PP2VP_FB;
	NetMsgFB.nClient = m_dwClientNum;
	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_PP2VP_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserPP2VP result %d DB ERROR", nResult);
		 pTemp->MsgPremiumPointCVTBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_PP2VP_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserPP2VP result %d CVT FAIL", nResult);
		 pTemp->MsgPremiumPointCVTBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_PP2VP_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserPP2VP result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgPremiumPointCVTBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}

CAgentUserResetPassword::CAgentUserResetPassword(
	const TCHAR* szUserID,
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )	
	, m_strPasswd2( szPasswd2 )	
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserResetPassword::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserResetPass(m_strUserID.GetString(),
													     m_strPasswd2.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_RPS_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_RESETPASS_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szUserpass2,		USR_PASS_LENGTH+1, m_strPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_RESETPASS_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPASS result %d DB ERROR", nResult);
		 pTemp->MsgResetPassBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_RESETPASS_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPASS result %d UPDATE FAIL", nResult);
		 pTemp->MsgResetPassBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_RESETPASS_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPASS result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgResetPassBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}

CAgentUserResetPassword2::CAgentUserResetPassword2(
	const TCHAR* szUserID,
	const TCHAR* szPasswd,
	const TCHAR* szPasswd2,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )	
	, m_strPasswd( szPasswd )	
	, m_strPasswd2( szPasswd2 )	
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserResetPassword2::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserResetPass2(m_strUserID.GetString(),
													     m_strPasswd.GetString(),
													     m_strPasswd2.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_RPS2_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_RESETPASS2_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,	USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szUserpass,		USR_PASS_LENGTH+1, m_strPasswd.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass2,		USR_PASS_LENGTH+1, m_strPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_RESETPASS_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPASS result %d DB ERROR", nResult);
		 pTemp->MsgResetPassBack2( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_RESETPASS_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPASS result %d UPDATE FAIL", nResult);
		 pTemp->MsgResetPassBack2( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_RESETPASS_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPASS result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgResetPassBack2( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}

CAgentUserResetPin::CAgentUserResetPin(
	const TCHAR* szUserID,
	const TCHAR* szEmail,
	const TCHAR* szPasswd,
	const TCHAR* szPasswd2,
	const TCHAR* szPasswd2Hold,
	const TCHAR* szCaptcha,
	DWORD  dwClientNum)
	: m_strUserID( szUserID )	
	, m_strEmail( szEmail )	
	, m_strPasswd( szPasswd )
	, m_strPasswd2( szPasswd2 )	
	, m_strPasswd2Hold( szPasswd2Hold )	
	, m_strCaptcha( szCaptcha )
	, m_dwClientNum ( dwClientNum )
{	

}

int CAgentUserResetPin::Execute(CServer* pServer)
{
	CAgentServer* pTemp = reinterpret_cast<CAgentServer*> (pServer);

	int nRetCode = 0;	
	int nResult = COdbcManager::GetInstance()->UserResetPin(m_strUserID.GetString(),
													     m_strEmail.GetString(),
													     m_strPasswd.GetString(),
													     m_strPasswd2.GetString(),
														 m_strCaptcha.GetString());

	// 전송할 구조체를 세팅한다.
	NET_RPN_FEEDBACK_DATA2 NetMsgFB;
	NetMsgFB.nmg.nType = CHINA_NET_MSG_RESETPIN_FB;
	NetMsgFB.nClient = m_dwClientNum;

	StringCchCopy(NetMsgFB.szUserid,		USR_ID_LENGTH+1, m_strUserID.GetString()); // id
	StringCchCopy(NetMsgFB.szUserEmail,		USR_PASS_LENGTH+1, m_strPasswd.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass2,		USR_PASS_LENGTH+1, m_strPasswd2.GetString()); // ip
	StringCchCopy(NetMsgFB.szUserpass2Hold,	USR_PASS_LENGTH+1, m_strPasswd2Hold.GetString()); // ip
	StringCchCopy(NetMsgFB.szCaptcha,		USR_CAPTCHA+1, m_strCaptcha.GetString()); // ip

	
	switch (nResult)
	{
	case DB_ERROR : 
		{
		NetMsgFB.nResult = EM_RESETPIN_FB_SUB_SYSTEM;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPIN result %d DB ERROR", nResult);
		 pTemp->MsgResetPinBack( &NetMsgFB );
		}break;
	case 0 :
		{
		NetMsgFB.nResult = EM_RESETPIN_FB_SUB_FAIL;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPIN result %d UPDATE FAIL", nResult);
		 pTemp->MsgResetPinBack( &NetMsgFB );
		}break;
	default : 
		{
		NetMsgFB.nResult = EM_RESETPIN_FB_SUB_OK;
		CConsoleMessage::GetInstance()->Write("CAgentUserRPIN result ClientNum %d success!", m_dwClientNum);
		 pTemp->MsgResetPinBack( &NetMsgFB );
		}break;
	};

		
	return NET_OK;
}