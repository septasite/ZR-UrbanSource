#include "StdAfx.h"
#include "PartyDisplayBuff.h"
#include "PartyDisplayBuffInfo.h"

#include "GLGaeaClient.h"
#include "GLPartyClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartyDisplayBuff::CPartyDisplayBuff ()
{
	for(int i = 0; i < MAXPARTY; i++ )
	{
		m_pBUFF[i] = NULL;
	}
}

CPartyDisplayBuff::~CPartyDisplayBuff ()
{
}

void CPartyDisplayBuff::CreateSubControl ()
{		
	CString strBuff[MAXPARTY] = 
	{
		"PARTYDISPLAY_BUFF_INFO",
		"PARTYDISPLAY_BUFF_INFO1",
		"PARTYDISPLAY_BUFF_INFO2",
		"PARTYDISPLAY_BUFF_INFO3",
		"PARTYDISPLAY_BUFF_INFO4",
		"PARTYDISPLAY_BUFF_INFO5",
		"PARTYDISPLAY_BUFF_INFO6",
		"PARTYDISPLAY_BUFF_INFO7"
	};

	for(int i = 0; i < MAXPARTY; i++ )
	{
		CPartyDisplayBuffInfo* pPartyDisplayBuffInfo = new CPartyDisplayBuffInfo;
		pPartyDisplayBuffInfo->CreateSub ( this, strBuff[i].GetString(), UI_FLAG_DEFAULT, PARTYDISPLAY_BUFF_INFO0 + i );
		pPartyDisplayBuffInfo->CreateSubControl ();
		RegisterControl ( pPartyDisplayBuffInfo );
		m_pBUFF[i] = pPartyDisplayBuffInfo;
	}
}

void CPartyDisplayBuff::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();
	if ( pMaster )
	{
		ResetAll();
		m_pBUFF[0]->SetPartyID(0);
		m_pBUFF[0]->SetVisibleSingle(TRUE);

		DWORD nMEMBER_NUM = GLPartyClient::GetInstance().GetMemberNum();
		if( nMEMBER_NUM > 1 )
		{
			nMEMBER_NUM -= 1;
			for ( DWORD i = 0; i < nMEMBER_NUM; i++ )
			{
				GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember ( i );			
				if ( pMember )
				{				
					m_pBUFF[i+1]->SetPartyID(i+1);
					m_pBUFF[i+1]->SetVisibleSingle(TRUE);
				}
			}
		}
	}

	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CPartyDisplayBuff::ResetAll()
{
	for(int i = 0; i < MAXPARTY; i++ )
	{
		if ( m_pBUFF[i] )
		{
			m_pBUFF[i]->SetVisibleSingle(FALSE);
		}
	}
}