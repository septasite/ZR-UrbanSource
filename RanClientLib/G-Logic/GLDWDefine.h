#pragma once

#include "GLCharDefine.h"

#define RANKING_NUM		9
#define SCHOOL_NUM		3
#define PLAYER_NAME		15
#define SCHOOL_NAME		15

struct SDW_TIME
{
	DWORD dwWeekDay; // 일 월 화 수 목 금 토 1 2 3 4 5 6 7
	DWORD dwStartTime; // 시간 (0-23까지)

	SDW_TIME () :
		dwWeekDay(0),
		dwStartTime(0)
	{
	}
};

struct SDW_RANK_EX
{
	WORD	wPlayerRanking;
	WORD	wKillNum;
	WORD	wDeathNum;

	SDW_RANK_EX()
		: wPlayerRanking (0)
		, wKillNum (0)
		, wDeathNum (0)
	{
	}

	void Init()
	{
		wPlayerRanking = 0;
		wKillNum = 0;
		wDeathNum = 0;
	}
};

struct SDW_RANK_INFO
{
	int		nIndex;   
	DWORD	dwCharID;
	WORD	wPlayerRanking;
	WORD	wKillNum;
	WORD	wDeathNum;
	char	szPlayerName[PLAYER_NAME+1];	
	
	SDW_RANK_INFO()
        : nIndex ( -1 )
		, dwCharID( GAEAID_NULL )
		, wPlayerRanking(0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szPlayerName, 0, sizeof(char) * (PLAYER_NAME+1) );
	}

	SDW_RANK_INFO ( const SDW_RANK_INFO &value )
	{
		operator=(value);
	}

	SDW_RANK_INFO& operator = ( const SDW_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		dwCharID = rvalue.dwCharID;
		wPlayerRanking = rvalue.wPlayerRanking;
		StringCchCopy( szPlayerName, PLAYER_NAME+1, rvalue.szPlayerName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	bool operator < ( const SDW_RANK_INFO& sDWRank )
	{			
		if ( wKillNum > sDWRank.wKillNum ) return true;
		else if ( wKillNum == sDWRank.wKillNum && wDeathNum < sDWRank.wDeathNum ) return true;
	
		return  false;
	}

	bool operator == ( const SDW_RANK_INFO& sDWRank ) 
	{
		if ( wKillNum == sDWRank.wKillNum && wDeathNum == sDWRank.wDeathNum ) return true;
		return false;

	}
};

struct SDW_RANK
{
	int nIndex;
	WORD wPlayerRanking;
	char szPlayerName[PLAYER_NAME+1];
	//	디버그용
	WORD wKillNum;
	WORD wDeathNum;

	SDW_RANK() 
		: nIndex(-1)
		, wPlayerRanking (0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szPlayerName, 0, sizeof(char) * (PLAYER_NAME+1) );
	}

	SDW_RANK ( const SDW_RANK &value )
	{
		operator=(value);
	}

	SDW_RANK& operator = ( const SDW_RANK& rvalue )
	{
		nIndex = rvalue.nIndex;
		wPlayerRanking = rvalue.wPlayerRanking;
		StringCchCopy( szPlayerName, PLAYER_NAME+1, rvalue.szPlayerName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	SDW_RANK ( const SDW_RANK_INFO &value )
	{
		operator=(value);
	}

	SDW_RANK& operator = ( const SDW_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		wPlayerRanking = rvalue.wPlayerRanking;
		StringCchCopy( szPlayerName, PLAYER_NAME+1, rvalue.szPlayerName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}
};

typedef std::vector<SDW_RANK_INFO>		DW_RANK_INFO_VEC;
typedef DW_RANK_INFO_VEC::iterator		DW_RANK_INFO_VEC_ITER;

typedef std::vector<SDW_RANK>			DW_RANK_VEC;
typedef DW_RANK_VEC::iterator			DW_RANK_VEC_ITER;

typedef std::map<DWORD,SDW_RANK_INFO>	DW_RANK_INFO_MAP;
typedef DW_RANK_INFO_MAP::iterator		DW_RANK_INFO_MAP_ITER;

typedef std::set<DWORD>					DW_AWARD_CHAR;			//	보상을 받은 캐릭터
typedef DW_AWARD_CHAR::iterator			DW_AWARD_CHAR_ITER;

struct SDW_AWARD_ITEM
{
	SNATIVEID	nAwardItem[9];		// 1,2,3,기타
	DWORD		dwAwardLimit;

	SDW_AWARD_ITEM()
		: dwAwardLimit(9)
	{	
		memset( nAwardItem, -1, sizeof( SNATIVEID ) * 9 );
	}
};