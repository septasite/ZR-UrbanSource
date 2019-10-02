#pragma once

#include "GLCharDefine.h"

#define RANKING_PNUM		10
#define CHAR_NAME		33

struct SSWP_RANK_EX
{
	WORD	wCharRanking;
	WORD	wKillNum;
	WORD	wDeathNum;

	SSWP_RANK_EX()
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

struct SSWP_RANK_INFO
{
	int		nIndex;   
	DWORD	dwCharID;
	WORD	wCharRanking;
	WORD	wKillNum;
	WORD	wDeathNum;
	char	szCharName[CHAR_NAME+1];	
	
	SSWP_RANK_INFO()
        : nIndex ( -1 )
		, dwCharID( CLUB_NULL )
		, wCharRanking(0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szCharName, 0, sizeof(char) * (CHAR_NAME+1) );
	}

	SSWP_RANK_INFO ( const SSWP_RANK_INFO &value )
	{
		operator=(value);
	}

	SSWP_RANK_INFO& operator = ( const SSWP_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		dwCharID = rvalue.dwCharID;
		wCharRanking = rvalue.wCharRanking;
		StringCchCopy( szCharName, CHAR_NAME+1, rvalue.szCharName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	bool operator < ( const SSWP_RANK_INFO& sSwPlayerRank )
	{			
		if ( wKillNum > sSwPlayerRank.wKillNum ) return true;
		else if ( wKillNum == sSwPlayerRank.wKillNum && wDeathNum < sSwPlayerRank.wDeathNum ) return true;
		
		return  false;
	}

	bool operator == ( const SSWP_RANK_INFO& sSwPlayerRank ) 
	{
		if ( wKillNum == sSwPlayerRank.wKillNum && wDeathNum == sSwPlayerRank.wDeathNum ) return true;

		return false;

	}
};

struct SSWP_RANK
{
	int nIndex;
	WORD wCharRanking;
	char szCharName[CHAR_NAME+1];

	WORD wKillNum;
	WORD wDeathNum;

	SSWP_RANK() 
		: nIndex(-1)
		, wCharRanking (0)
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szCharName, 0, sizeof(char) * (CHAR_NAME+1) );
	}

	SSWP_RANK ( const SSWP_RANK &value )
	{
		operator=(value);
	}

	SSWP_RANK& operator = ( const SSWP_RANK& rvalue )
	{
		nIndex = rvalue.nIndex;
		wCharRanking = rvalue.wCharRanking;
		StringCchCopy( szCharName, CHAR_NAME+1, rvalue.szCharName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}

	SSWP_RANK ( const SSWP_RANK_INFO &value )
	{
		operator=(value);
	}

	SSWP_RANK& operator = ( const SSWP_RANK_INFO& rvalue )
	{
		nIndex = rvalue.nIndex;
		wCharRanking = rvalue.wCharRanking;
		StringCchCopy( szCharName, CHAR_NAME+1, rvalue.szCharName );
		
		wKillNum = rvalue.wKillNum;
		wDeathNum = rvalue.wDeathNum;

		return *this;
	}
};

typedef std::vector<SSWP_RANK_INFO>		SWP_RANK_INFO_VEC;
typedef SWP_RANK_INFO_VEC::iterator		SWP_RANK_INFO_VEC_ITER;

typedef std::vector<SSWP_RANK>			SWP_RANK_VEC;
typedef SWP_RANK_VEC::iterator			SWP_RANK_VEC_ITER;

typedef std::map<DWORD,SSWP_RANK_INFO>	SWP_RANK_INFO_MAP;
typedef SWP_RANK_INFO_MAP::iterator		SWP_RANK_INFO_MAP_ITER;

typedef std::set<DWORD>					SWP_AWARD_CHAR;	
typedef SWP_AWARD_CHAR::iterator		SWP_AWARD_CHAR_ITER;

struct SSWP_AWARD_ITEM
{
	SNATIVEID	nAwardItem[10];
	DWORD		dwAwardLimit;

	SSWP_AWARD_ITEM()
		: dwAwardLimit(10)
	{	
		memset( nAwardItem, -1, sizeof( SNATIVEID ) * 10 );
	}
};