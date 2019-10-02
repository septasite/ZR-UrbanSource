#pragma once

#include "GLContrlBaseMsg.h"

namespace GLMSG
{
	#pragma pack(1)
	
	struct SNET_SCHOOL_WARS_START_BRD
	{
		enum { TEXT_LEN = 33, };

		NET_MSG_GENERIC			nmg;
		
		int						nTIME;
		char					szName[TEXT_LEN];

		SNET_SCHOOL_WARS_START_BRD () 
			: nTIME(0)
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_START_BRD);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_START_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(szName, 0, sizeof(char) * TEXT_LEN);
		}
	};

	struct SNET_SCHOOL_WARS_READY_FLD
	{
		NET_MSG_GENERIC			nmg;

		DWORD					dwID;

		SNET_SCHOOL_WARS_READY_FLD () 
			: dwID(0)
		{
			nmg.dwSize = sizeof(*this);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_READY_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_SCHOOL_WARS_START_FLD
	{
		NET_MSG_GENERIC			nmg;

		DWORD					dwID;

		SNET_SCHOOL_WARS_START_FLD () 
			: dwID(0)
		{
			nmg.dwSize = sizeof(*this);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_START_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_SCHOOL_WARS_END_FLD
	{
		NET_MSG_GENERIC			nmg;
		DWORD					dwID;

		SNET_SCHOOL_WARS_END_FLD () 
			: dwID(0)
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_END_FLD);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_END_FLD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_SCHOOL_WARS_END_BRD
	{
		enum { TEXT_LEN = 33, };

		NET_MSG_GENERIC			nmg;
		char					szName[TEXT_LEN];
		char					szClubName[CHAR_SZNAME];

		SNET_SCHOOL_WARS_END_BRD ()
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_END_BRD);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_END_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);

			memset(szName, 0, sizeof(char) * TEXT_LEN);
			memset(szClubName, 0, sizeof(char) * CHAR_SZNAME);
		}
	};

	struct SNET_SCHOOL_WARS_REMAIN_BRD
	{
		NET_MSG_GENERIC			nmg;

		DWORD					dwTime;

		SNET_SCHOOL_WARS_REMAIN_BRD ()
			: dwTime(0)
		{
			nmg.dwSize = sizeof ( SNET_SCHOOL_WARS_REMAIN_BRD );
			nmg.nType  = NET_MSG_GCTRL_SCHOOL_WARS_REMAIN_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNET_SCHOOL_WARS_POINT_UPDATE
	{
		NET_MSG_GENERIC			nmg;
		
		bool					bKillPoint;

		SNET_SCHOOL_WARS_POINT_UPDATE () 
			: bKillPoint(false)		
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_POINT_UPDATE);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_POINT_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}        
	};

	struct SNET_SCHOOL_WARS_PPOINT_UPDATE
	{
		NET_MSG_GENERIC			nmg;
		
		bool					bKillPoint;

		SNET_SCHOOL_WARS_PPOINT_UPDATE () 
			: bKillPoint(false)		
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_PPOINT_UPDATE);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_PPOINT_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}        
	};

	struct SNET_SCHOOL_WARS_MYRANK_UPDATE
	{
		NET_MSG_GENERIC			nmg;
		
		SSW_RANK_EX			sMySwRank;		

		SNET_SCHOOL_WARS_MYRANK_UPDATE () 
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_MYRANK_UPDATE);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_MYRANK_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}        
	};

	struct SNET_SCHOOL_WARS_MYPRANK_UPDATE
	{
		NET_MSG_GENERIC			nmg;
		
		SSWP_RANK_EX			sMySwPRank;		

		SNET_SCHOOL_WARS_MYPRANK_UPDATE () 
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_MYPRANK_UPDATE);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_MYPRANK_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}        
	};

	struct SNET_SCHOOL_WARS_RANKING_UPDATE
	{
		NET_MSG_GENERIC		nmg;

        WORD				wRankNum;		
		SSW_RANK			sSwRank[RANKING_NUM];

		SNET_SCHOOL_WARS_RANKING_UPDATE () 
			: wRankNum(0)
		{
			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_RANKING_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}

		bool ADDSCHOOL ( const SSW_RANK& sRank )
		{
			if ( RANKING_NUM==wRankNum )		return false;

			sSwRank[wRankNum] = sRank;

			++wRankNum;

			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD) + sizeof(SSW_RANK)*wRankNum;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
			return true;
		}

		void RESET ()
		{
			wRankNum = 0;
			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD);
		}
	};

	struct SNET_SCHOOL_WARS_PRANKING_UPDATE
	{
		NET_MSG_GENERIC		nmg;

        WORD				wRankNum;		
		SSWP_RANK			sSwPRank[RANKING_NUM];

		SNET_SCHOOL_WARS_PRANKING_UPDATE () 
			: wRankNum(0)
		{
			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_PRANKING_UPDATE;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}

		bool ADDCHAR ( const SSWP_RANK& sRank )
		{
			if ( RANKING_NUM==wRankNum )		return false;

			sSwPRank[wRankNum] = sRank;

			++wRankNum;

			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD) + sizeof(SSWP_RANK)*wRankNum;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
			return true;
		}

		void RESET ()
		{
			wRankNum = 0;
			nmg.dwSize = sizeof(NET_MSG_GENERIC) + sizeof(WORD);
		}
	};

	struct SNET_SCHOOL_WARS_RANKING_REQ
	{
		NET_MSG_GENERIC		nmg;    
		
		DWORD				dwMapID;		
		
		SNET_SCHOOL_WARS_RANKING_REQ () 
			: dwMapID(UINT_MAX)		
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_RANKING_REQ);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_RANKING_REQ;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}       

	};

	struct SNET_SCHOOL_WARS_PRANKING_REQ
	{
		NET_MSG_GENERIC		nmg;    
		
		DWORD				dwMapID;		
		
		SNET_SCHOOL_WARS_PRANKING_REQ () 
			: dwMapID(UINT_MAX)		
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_PRANKING_REQ);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_PRANKING_REQ;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);			
		}       

	};

	/*struct SNETPC_SERVER_SCHOOL_WARS_INFO
	{
		NET_MSG_GENERIC		nmg;
		bool				bSchoolWars;

		SNETPC_SERVER_SCHOOL_WARS_INFO () :
			bSchoolWars(false)
		{
			nmg.dwSize = sizeof(*this);
			nmg.nType = NET_MSG_GCTRL_SERVER_SCHOOL_WARS_INFO;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	struct SNETPC_SERVER_SCHOOL_WARS_REMAIN_AG
	{
		NET_MSG_GENERIC		nmg;
		DWORD				dwGaeaID;

		SNETPC_SERVER_SCHOOL_WARS_REMAIN_AG ()
			: dwGaeaID(0)
		{
			nmg.dwSize = sizeof(*this);
			nmg.nType = NET_MSG_GCTRL_REQ_SERVER_SCHOOL_WARS_REMAIN_AG;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};*/

	//add sw buff
	struct SNET_SCHOOL_WARS_SETWINSCHOOL_BRD
	{
		NET_MSG_GENERIC			nmg;
		WORD					wSchool;

		SNET_SCHOOL_WARS_SETWINSCHOOL_BRD () 
			: wSchool(GLSCHOOL_NUM)
		{
			nmg.dwSize = sizeof(SNET_SCHOOL_WARS_SETWINSCHOOL_BRD);
			nmg.nType = NET_MSG_GCTRL_SCHOOL_WARS_SETWINSCHOOL_BRD;
			GASSERT(nmg.dwSize<=NET_DATA_BUFSIZE);
		}
	};

	// Revert to default structure packing
	#pragma pack()
};