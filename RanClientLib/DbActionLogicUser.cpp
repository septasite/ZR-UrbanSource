#include "stdafx.h"
#include "./DbActionLogic.h"

#include "../NetServerLib/s_CSessionServer.h"
#include "../NetServerLib/s_CFieldServer.h"
#include "../NetServerLib/s_CAgentServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGetPoints::CGetPoints(
    int   nChaNum,
	DWORD dwUserID,
	DWORD dwClientID )
	: m_nChaNum( nChaNum )
	, CDbAction( dwClientID )
{
	m_dwClient = dwClientID;
	m_dwUserID = dwUserID;
}

int CGetPoints::Execute( CServer* pServer )
{
	
	GLMSG::SNETPC_RETRIEVE_POINTS_FB NetMsgFB;
	int PPoints = 0, VPPoints = 0;
	int nResult = m_pDbManager->GetPoints( m_nChaNum, m_dwUserID , m_dwClient , &PPoints , &VPPoints );

	if ( nResult != DB_ERROR )
	{
		NetMsgFB.emFB		 = EMREQ_RETRIEVE_POINTS_OK;
		NetMsgFB.PPoints		 = PPoints;
		NetMsgFB.VPoints		 = VPPoints;
	}
	else
	{
		NetMsgFB.emFB		 = EMREQ_RETRIEVE_POINTS_FAIL;
	}

	CFieldServer* pTemp = reinterpret_cast<CFieldServer*> (pServer);
	pTemp->InsertMsg ( m_dwClient, (char*) &NetMsgFB );

	return nResult;
}