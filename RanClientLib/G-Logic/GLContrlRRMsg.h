#pragma once

#include "GLContrlBaseMsg.h"

namespace GLMSG
{
	#pragma pack(1)
	
	struct SNET_ROYAL_RUMBLE_START_BRD
	{
		enum { TEXT_LEN = 33, };

		NET_MSG_GENERIC			nmg;
		
		int						nTIME;
		char					szName[TEXT_LEN];

		SNET_ROYAL_RUMBLE_START_BRD () 
			: nTIME(0)
		{
			nmg.dwSize = sizeof(SNET_ROYAL_RUMBLE_START_BRD);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_START_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(szName, 0, sizeof(char) * TEXT_LEN);
		}
	};

	struct SNET_ROYAL_RUMBLE_READY_FLD
	{
		NET_MSG_GENERIC			nmg;

		DWORD					dwID;

		SNET_ROYAL_RUMBLE_READY_FLD () 
			: dwID(0)
		{
			nmg.dwSize = sizeof(*this);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_READY_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_ROYAL_RUMBLE_START_FLD
	{
		NET_MSG_GENERIC			nmg;

		DWORD					dwID;

		SNET_ROYAL_RUMBLE_START_FLD () 
			: dwID(0)
		{
			nmg.dwSize = sizeof(*this);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_START_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_ROYAL_RUMBLE_END_FLD
	{
		NET_MSG_GENERIC			nmg;
		DWORD					dwID;

		SNET_ROYAL_RUMBLE_END_FLD () 
			: dwID(0)
		{
			nmg.dwSize = sizeof(SNET_ROYAL_RUMBLE_END_FLD);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_END_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_ROYAL_RUMBLE_END_BRD
	{
		enum { TEXT_LEN = 33, };

		NET_MSG_GENERIC			nmg;
		char					szName[TEXT_LEN];
		char					szCharName[CHAR_SZNAME];

		SNET_ROYAL_RUMBLE_END_BRD ()
		{
			nmg.dwSize = sizeof(SNET_ROYAL_RUMBLE_END_BRD);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_END_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(szName, 0, sizeof(char) * TEXT_LEN);
			memset(szCharName, 0, sizeof(char) * CHAR_SZNAME);
		}
	};

	struct SNET_ROYAL_RUMBLE_REMAIN_BRD
	{
		NET_MSG_GENERIC			nmg;

		DWORD					dwTime;

		SNET_ROYAL_RUMBLE_REMAIN_BRD ()
			: dwTime(0)
		{
			nmg.dwSize = sizeof ( SNET_ROYAL_RUMBLE_REMAIN_BRD );
			nmg.nType  = NET_MSG_GCTRL_ROYAL_RUMBLE_REMAIN_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_ROYAL_RUMBLE_PPOINT_UPDATE
	{
		NET_MSG_GENERIC			nmg;
		
		bool					bKillPoint;

		SNET_ROYAL_RUMBLE_PPOINT_UPDATE () 
			: bKillPoint(false)		
		{
			nmg.dwSize = sizeof(SNET_ROYAL_RUMBLE_PPOINT_UPDATE);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_PPOINT_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}        
	};

	struct SNET_ROYAL_RUMBLE_MYPRANK_UPDATE
	{
		NET_MSG_GENERIC			nmg;
		
		SRRP_RANK_EX			sMyRrPRank;		

		SNET_ROYAL_RUMBLE_MYPRANK_UPDATE () 
		{
			nmg.dwSize = sizeof(SNET_ROYAL_RUMBLE_MYPRANK_UPDATE);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_MYPRANK_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}        
	};

	struct SNET_ROYAL_RUMBLE_PRANKING_UPDATE
	{
		NET_MSG_GENERIC		nmg;

        WORD				wRankNum;		
		SRRP_RANK			sRrPRank[RANKING_NUM];

		SNET_ROYAL_RUMBLE_PRANKING_UPDATE () 
			: wRankNum(0)
		{
			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_PRANKING_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}

		bool RRADDCHAR ( const SRRP_RANK& sRank )
		{
			if ( RANKING_NUM==wRankNum )		return false;

			sRrPRank[wRankNum] = sRank;

			++wRankNum;

			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD) + sizeof(SRRP_RANK)*wRankNum;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
			return true;
		}

		void RESET ()
		{
			wRankNum = 0;
			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD);
		}
	};

	struct SNET_ROYAL_RUMBLE_PRANKING_REQ
	{
		NET_MSG_GENERIC		nmg;    
		
		DWORD				dwMapID;		
		
		SNET_ROYAL_RUMBLE_PRANKING_REQ () 
			: dwMapID(UINT_MAX)		
		{
			nmg.dwSize = sizeof(SNET_ROYAL_RUMBLE_PRANKING_REQ);
			nmg.nType = NET_MSG_GCTRL_ROYAL_RUMBLE_PRANKING_REQ;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}       

	};

	// Revert to default structure packing
	#pragma pack()
};