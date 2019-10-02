#pragma once

#include "GLCharDefine.h"

#define RANKING_PNUM		10
#define CHAR_NAME		33

struct SRR_TIME
{
	DWORD dwWeekDay; // 일 월 화 수 목 금 토 1 2 3 4 5 6 7
	DWORD dwStartTime; // 시간 (0-23까지)

	SRR_TIME () :
		dwWeekDay(0),
		dwStartTime(0)
	{
	}
};

struct SRRP_RANK_EX
{
	WORD	wCharRanking;
	WORD	wKillNum;
	WORD	wDeathNum;

	SRRP_RANK_EX()
		: wCharRanking(0)
		, wKillNum (0)
		, wDeathNum(0)
	{
	}

	void Init()
	{
		wCharRanking = 0;
		wKillNum = 0;
		wDeathNum = 0;
	}
};

struct SRRP_RANK_INFO
{
	int		nIndex;   
	DWORD	dwCharID;
	WORD	wCharRanking;
	WORD	wKillNum;
	WORD	wDeathNum;
	char	szCharName[CHAR_NAME+1];	
	
	SRRP_RANK_INFO()
        : nIndex ( -1 )
		, dwCharID( CLUB_NULL )
		, wCharRanking(0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szCharName, 0, sizeof(char) * (CHAR_NAME+1) );
	}

	SRRP_RANK_INFO ( const SRRP_RANK_INFO &value )
	{
		operator=(value);
	}

	SRRP_RANK_INFO& operator = ( const SRRP_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		dwCharID = rvalue.dwCharID;
		wCharRanking = rvalue.wCharRanking;
		StringCchCopy( szCharName, CHAR_NAME+1, rvalue.szCharName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	bool operator < ( const SRRP_RANK_INFO& sRrPlayerRank )
	{			
		if ( wKillNum > sRrPlayerRank.wKillNum ) return true;
		else if ( wKillNum == sRrPlayerRank.wKillNum && wDeathNum < sRrPlayerRank.wDeathNum ) return true;
		
		return  false;
	}

	bool operator == ( const SRRP_RANK_INFO& sRrPlayerRank ) 
	{
		if ( wKillNum == sRrPlayerRank.wKillNum && wDeathNum == sRrPlayerRank.wDeathNum ) return true;

		return false;

	}
};

struct SRRP_RANK
{
	int nIndex;
	WORD wCharRanking;
	char szCharName[CHAR_NAME+1];

	WORD wKillNum;
	WORD wDeathNum;

	SRRP_RANK() 
		: nIndex(-1)
		, wCharRanking (0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szCharName, 0, sizeof(char) * (CHAR_NAME+1) );
	}

	SRRP_RANK ( const SRRP_RANK &value )
	{
		operator=(value);
	}

	SRRP_RANK& operator = ( const SRRP_RANK& rvalue )
	{
		nIndex = rvalue.nIndex;
		wCharRanking = rvalue.wCharRanking;
		StringCchCopy( szCharName, CHAR_NAME+1, rvalue.szCharName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	SRRP_RANK ( const SRRP_RANK_INFO &value )
	{
		operator=(value);
	}

	SRRP_RANK& operator = ( const SRRP_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		wCharRanking = rvalue.wCharRanking;
		StringCchCopy( szCharName, CHAR_NAME+1, rvalue.szCharName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}
};

typedef std::vector<SRRP_RANK_INFO>		RRP_RANK_INFO_VEC;
typedef RRP_RANK_INFO_VEC::iterator		RRP_RANK_INFO_VEC_ITER;

typedef std::vector<SRRP_RANK>			RRP_RANK_VEC;
typedef RRP_RANK_VEC::iterator			RRP_RANK_VEC_ITER;

typedef std::map<DWORD,SRRP_RANK_INFO>	RRP_RANK_INFO_MAP;
typedef RRP_RANK_INFO_MAP::iterator		RRP_RANK_INFO_MAP_ITER;

typedef std::set<DWORD>					RRP_AWARD_CHAR;	
typedef RRP_AWARD_CHAR::iterator		RRP_AWARD_CHAR_ITER;

struct SRRP_AWARD_ITEM
{
	SNATIVEID	nAwardItem[10];
	DWORD		dwAwardLimit;

	SRRP_AWARD_ITEM()
		: dwAwardLimit(10)
	{	
		memset( nAwardItem, -1, sizeof( SNATIVEID ) * 10 );
	}
};