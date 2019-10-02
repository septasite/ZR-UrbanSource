#pragma once

#include "GLCharDefine.h"

#define RANKING_NUM		9
#define SCHOOL_NAME		15

struct SSW_TIME
{
	DWORD dwWeekDay; // 일 월 화 수 목 금 토 1 2 3 4 5 6 7
	DWORD dwStartTime; // 시간 (0-23까지)

	SSW_TIME () :
		dwWeekDay(0),
		dwStartTime(0)
	{
	}
};

struct SSW_RANK_EX
{
	WORD	wClubRanking;
	WORD	wKillNum;
	WORD	wDeathNum;

	SSW_RANK_EX()
		: wClubRanking(0)
		, wKillNum (0)
		, wDeathNum(0)
	{
	}

	void Init()
	{
		wClubRanking = 0;
		wKillNum = 0;
		wDeathNum = 0;
	}
};

struct SSW_RANK_INFO
{
	int		nIndex;   
	DWORD	dwClubID;
	WORD	wClubRanking;
	WORD	wKillNum;
	WORD	wDeathNum;
	char	szClubName[SCHOOL_NAME+1];	
	
	SSW_RANK_INFO()
        : nIndex ( -1 )
		, dwClubID( CLUB_NULL )
		, wClubRanking(0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szClubName, 0, sizeof(char) * (SCHOOL_NAME+1) );
	}

	SSW_RANK_INFO ( const SSW_RANK_INFO &value )
	{
		operator=(value);
	}

	SSW_RANK_INFO& operator = ( const SSW_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		dwClubID = rvalue.dwClubID;
		wClubRanking = rvalue.wClubRanking;
		StringCchCopy( szClubName, SCHOOL_NAME+1, rvalue.szClubName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	bool operator < ( const SSW_RANK_INFO& sSwRank )
	{			
		if ( wKillNum > sSwRank.wKillNum ) return true;
		else if ( wKillNum == sSwRank.wKillNum && wDeathNum < sSwRank.wDeathNum ) return true;
		
		return  false;
	}

	bool operator == ( const SSW_RANK_INFO& sSwRank ) 
	{
		if ( wKillNum == sSwRank.wKillNum && wDeathNum == sSwRank.wDeathNum ) return true;

		return false;

	}
};

struct SSW_RANK
{
	int nIndex;
	WORD wClubRanking;
	char szClubName[SCHOOL_NAME+1];

	//	디버그용
	WORD wKillNum;
	WORD wDeathNum;

	SSW_RANK() 
		: nIndex(-1)
		, wClubRanking (0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szClubName, 0, sizeof(char) * (SCHOOL_NAME+1) );
	}

	SSW_RANK ( const SSW_RANK &value )
	{
		operator=(value);
	}

	SSW_RANK& operator = ( const SSW_RANK& rvalue )
	{
		nIndex = rvalue.nIndex;
		wClubRanking = rvalue.wClubRanking;
		StringCchCopy( szClubName, SCHOOL_NAME+1, rvalue.szClubName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	SSW_RANK ( const SSW_RANK_INFO &value )
	{
		operator=(value);
	}

	SSW_RANK& operator = ( const SSW_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		wClubRanking = rvalue.wClubRanking;
		StringCchCopy( szClubName, SCHOOL_NAME+1, rvalue.szClubName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}
};

typedef std::vector<SSW_RANK_INFO>		SW_RANK_INFO_VEC;
typedef SW_RANK_INFO_VEC::iterator		SW_RANK_INFO_VEC_ITER;

typedef std::vector<SSW_RANK>			SW_RANK_VEC;
typedef SW_RANK_VEC::iterator			SW_RANK_VEC_ITER;

typedef std::map<DWORD,SSW_RANK_INFO>	SW_RANK_INFO_MAP;
typedef SW_RANK_INFO_MAP::iterator		SW_RANK_INFO_MAP_ITER;

typedef std::set<DWORD>					SW_AWARD_CHAR;			//	보상을 받은 캐릭터
typedef SW_AWARD_CHAR::iterator		SW_AWARD_CHAR_ITER;

struct SSW_AWARD_ITEM
{
	SNATIVEID	nAwardItem[4];		// 1,2,3,기타
	DWORD		dwAwardLimit;

	SSW_AWARD_ITEM()
		: dwAwardLimit(4)
	{	
		memset( nAwardItem, -1, sizeof( SNATIVEID ) * 4 );
	}
};