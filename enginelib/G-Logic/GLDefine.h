#ifndef GLDEFINE_H_
#define GLDEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "../Common/seqrandom.h"

#define RANDOM_POS		(((FLOAT)rand())/RAND_MAX)		// 0.f ~ 1.f
#define RANDOM_NUM		( (RANDOM_POS*2.f)-1.f )		// -1.f ~ 1.f
#define RANDOM_GATE		( rand() % 20 )	//royal rumble random respawn fix

#define FLOAT_SET	0xe021f

inline bool cast_bool ( BOOL b )	{ return b ? true : false; }

inline BOOL RANDOM_GEN ( float fRate )
{
	return ( fRate >= seqrandom::getpercent() );
}

inline float RandomNumber( float fMin, float fMax )
{
	if( fMin == fMax ) return fMin;
	float fRandom = (float)rand() / (float)RAND_MAX;
	return ((fRandom * (float)fabs(fMax-fMin))+fMin);
}

inline int RandomNumber( int iMin, int iMax )
{
	if( iMin == iMax ) return iMin;
	return ((rand() % (abs(iMax-iMin)+1))+iMin);
}

inline unsigned int SetControlfp( bool bSet )
{
	if ( bSet ) 
	{
		_controlfp( _PC_24, _MCW_PC ); 
		_controlfp( _RC_UP, _MCW_RC ); 
		_controlfp( _IC_AFFINE, _MCW_IC );
	}
	else
	{
		_controlfp( _CW_DEFAULT, 0xfffff );
	}
	
	return _controlfp( 0,0 );
}

inline unsigned int GetControlfp()
{
	return _controlfp( 0,0 );
}

inline unsigned int CheckControlfp()
{
	unsigned int nFloat = GetControlfp();
	if( nFloat != FLOAT_SET ) 
	{
		return SetControlfp( true );	
	}

	return nFloat;
}

template < typename TYPE >
TYPE DECREASE ( TYPE &Value, const TYPE Dec )
{
	if ( Value >= Dec )	return Value -= Dec;
	return Value = 0;
}

template < typename TYPE >
TYPE LIMIT ( TYPE &Value, const TYPE Max )
{
	if ( Value >= Max ) return Value = Max;
	return Value;
}

template < typename TYPE >
TYPE LIMIT ( TYPE &Value, const TYPE Max, const TYPE Min )
{
	GASSERT(Min<Max);

	if ( Value >= Max ) return Value = Max;
	if ( Value <= Min ) return Value = Min;

	return Value;
}

enum EMGLSTEP
{
	GL_VERYHIGH		= 1,		//	∏≈øÅE≥Ù¿Ω.
	GL_HIGH			= 2,		//	≥Ù¿Ω.
	GL_NORMAL		= 3,		//	∫∏≈ÅE
	GL_LOW			= 4,		//	≥∑¿Ω.
	GL_VERYLOW		= 5,		//	∏≈øÅE≥∑¿Ω.
};

struct SNATIVEID
{
	enum
	{
		ID_NULL	= 0xFFFF,
	};

	union
	{
		struct
		{
			DWORD	dwID;
		};

		struct
		{
			WORD	wMainID;		//	¡÷ ID.
			WORD	wSubID;			//	∫∏¡∂ ID.
		};
	};

	SNATIVEID () 
		: wMainID(0)
		, wSubID(0)
	{
	}

	SNATIVEID ( bool bvalid ) 
		: wMainID(0)
		, wSubID(0)
	{
		if ( !bvalid )
		{
			wMainID = ID_NULL;
			wSubID = ID_NULL;
		}
	}

	SNATIVEID ( DWORD dwid ) 
		: dwID(dwid)
	{
	}

	SNATIVEID ( WORD wid, WORD wsubid ) 
		: wMainID(wid)
		, wSubID(wsubid)
	{
	}

	bool operator== ( const SNATIVEID& nID ) const
	{
		return (wMainID==nID.wMainID) && (wSubID==nID.wSubID);
	}

	bool operator!= ( const SNATIVEID& nID ) const
	{
		return !( (wMainID==nID.wMainID) && (wSubID==nID.wSubID) );
	}

	bool IsValidNativeID()
	{
		return ( (wMainID!=ID_NULL) && (wSubID!=ID_NULL) );
	}
};


struct SChinaTime
{
	int	userAge;
	// ¿˙¿Âµ» ø¿«¡∂Û¿Œ ¥©¿ÅEΩ√∞£
	int offlineTime;
	// ¿˙¿Âµ» ∞‘¿” ¥©¿ÅEΩ√∞£
	LONGLONG gameTime;
	// «ˆ¿ÅE∞‘¿” ¥©¿ÅEΩ√∞£
	LONGLONG currentGameTime;
	// ∑Œ±◊¿Œ«— Ω√∞£
	__time64_t loginTime;
	// ∏∂¡ˆ∏∑ ∑Œ±◊ø¿«¡«— Ω√∞£
	__time64_t lastOffLineTime;

	SChinaTime()
	{
		Init();
	}
	void Init()
	{
		userAge			= 0;
		offlineTime		= 0;
		gameTime		= 0;
		loginTime		= 0;
		lastOffLineTime = 0;
		currentGameTime = 0;
	}
};

struct SVietnamGainSystem
{	
	// ¿˙¿Âµ» ∞‘¿” ¥©¿ÅEΩ√∞£
	LONGLONG gameTime;
	// «ˆ¿ÅE∞‘¿” ¥©¿ÅEΩ√∞£
	LONGLONG currentGameTime;
	// ∑Œ±◊¿Œ«— Ω√∞£
	__time64_t loginTime;
	// ∏∂¡ˆ∏∑ ∑Œ±◊ø¿«¡«— ≥Ø¬•, Ω√∞£
	__time64_t lastOffLineTime;


	SVietnamGainSystem()
	{
		Init();
	}
	void Init()
	{
		gameTime		= 0;
		loginTime		= 0;
		lastOffLineTime = 0;
		currentGameTime = 0;
	}
};


struct SPETSKINPACKDATA 
{
	SNATIVEID sMobID;			// πŸ≤ÅE∏ÅEID
	float	  fScale;			// πŸ≤ÅE∏˜¿« ≈©±ÅE
	DWORD	  dwPetSkinTime;		// ¿˚øÅEµ«¥¬ Ω√∞£
	bool	  bUsePetSkinPack;  // ¿˚øÅE«æ˙¥¬¡ÅEæ∆¥—¡ÅE
	CTime	  startTime;

	SPETSKINPACKDATA()
		: sMobID(false)
		, fScale(1.0f)
		, dwPetSkinTime(0)
		, bUsePetSkinPack(false)
	{
	}

	void Init()
	{
		sMobID			= false;
		fScale			= 1.0f;
		dwPetSkinTime   = 0;
		bUsePetSkinPack = false;
	}

};

struct STracingData 
{
	std::string strAccount;
	DWORD  dwUserNum;
	BYTE   dwOnLine;
	int	   nConnectServer;

	STracingData()
	{
		dwUserNum     = 0;
		strAccount    = "";
		dwOnLine = 255;
		nConnectServer = -1;
	}

	STracingData( std::string str )
	{
		dwUserNum      = 0;
		strAccount     = str;
		dwOnLine = 255;
		nConnectServer = -1;
	}

	STracingData( DWORD dwUserNum )
	{
		dwUserNum      = dwUserNum;
		strAccount     = "";
		dwOnLine = 255;
		nConnectServer = -1;
	}
};


struct SEventTime
{
	// «ˆ¿ÅE∞‘¿” ¥©¿ÅEΩ√∞£
	LONGLONG currentGameTime;
	// ∑Œ±◊¿Œ«— Ω√∞£
	__time64_t loginTime;
	SEventTime()
	{
		Init();
	}
	void Init()
	{
		loginTime		 = 0;
		currentGameTime  = 0;
	}
};

inline SNATIVEID NATIVEID_NULL()	{ return SNATIVEID(SNATIVEID::ID_NULL,SNATIVEID::ID_NULL); }

struct GLPADATA
{
	union
	{
		struct
		{
			DWORD	dwData;
		};
		struct
		{
			DWORD	dwNow;
			DWORD	dwMax;
		};
		struct
		{
			DWORD	dwLow;
			DWORD	dwHigh;
		};
	};

	GLPADATA () 
		: dwData(0)
		,dwNow(0)
		,dwMax(0)
		,dwLow(0)
		,dwHigh(0)
	{
	}

	GLPADATA ( DWORD dwL, DWORD dwH )
	{
		dwLow = dwL;
		dwHigh = dwH;
	}

	void LIMIT ()					{ if ( dwNow > dwMax )	dwNow = dwMax; }
	void CHECKMIN ( DWORD dwMin )		{ if ( dwNow < dwMin )	dwNow = dwMin; }
	void TO_FULL ()					{ dwNow = dwMax; }
	
	void DECREASE ( const DWORD dwValue )
	{
		if ( dwNow >= dwValue )	dwNow -= dwValue;
		else					dwNow = 0;
	}

	//add direct val
	void INCREASE ( const DWORD dwValue, const BOOL bRate=FALSE ,const DWORD dwRate = 0 )
	{
		//if ( bRate )	dwNow += ( (dwMax*dwValue) / 100 );
		//else			dwNow += dwValue;

		//jdev revise *will add some checking to avoid overflow
		DWORD	dwIncTemp = 0;
		if ( bRate )	dwIncTemp += ( (dwMax*dwValue) / 100 );
		else			dwIncTemp += dwValue;
		dwIncTemp += dwRate; //this is from item data (increase pot recovery)
		
		DWORD	dwThisCheck = dwNow + dwIncTemp;
		if ( dwThisCheck >= dwMax ) dwNow = dwMax;
		else dwNow += dwIncTemp;

		LIMIT ();
		dwIncTemp = 0;
		dwThisCheck = 0;
	}

	DWORD VARIATION ( const int nValue )
	{
		int nOld = int(dwLow);

		if ( (int(dwLow)+nValue) < 0 )				dwLow = 0;
		else if ( (int(dwLow)+nValue)>int(dwMax) )	dwLow = dwMax;
		else										dwLow += nValue;

		LIMIT ();

		DWORD dwDX = (DWORD) abs(nOld-int(dwLow));
		return dwDX;
	}

	void VAR_PARAM ( const int nValue )
	{
		if ( (int(dwLow)+nValue) < 1 )	dwLow = 1;
		else							dwLow += nValue;

		if ( (int(dwHigh)+nValue) < 1 )	dwHigh = 1;
		else							dwHigh += nValue;
	}

	BOOL operator== ( const GLPADATA& nID ) const
	{
		return (dwNow==nID.dwNow) && (dwMax==nID.dwMax);
	}

	BOOL operator!= ( const GLPADATA& nID ) const
	{
		return !( (dwNow==nID.dwNow) && (dwMax==nID.dwMax) );
	}

	GLPADATA& operator += ( const GLPADATA& nID )
	{
		dwNow+=nID.dwNow;
		dwMax+=nID.dwMax;

		return *this;
	}

	GLPADATA& operator + ( const GLPADATA& nID )
	{
		dwNow+=nID.dwNow;
		dwMax+=nID.dwMax;

		return *this;
	}
};

struct GLPWDATA
{
	union
	{
		struct
		{
			DWORD	dwData1;
			DWORD	dwData2;
		};
		struct
		{
			DWORD	dwNow;
			DWORD	dwMax;
		};
		struct
		{
			DWORD	dwLow;
			DWORD	dwHigh;
		};
	};

	GLPWDATA () :
		dwData1(0),
		dwData2(0)
		,dwNow(0)
		,dwMax(0)
		,dwLow(0)
		,dwHigh(0)
	{
	}

	GLPWDATA ( DWORD dwL, DWORD dwH )
	{
		dwLow = dwL;
		dwHigh = dwH;
	}

	GLPWDATA ( const GLPADATA& nID )
	{
		dwNow = nID.dwNow;
		dwMax = nID.dwMax;
	}

	BOOL operator== ( const GLPWDATA& nID ) const
	{
		return (dwNow==nID.dwNow) && (dwMax==nID.dwMax);
	}

	BOOL operator!= ( const GLPWDATA& nID ) const
	{
		return !( (dwNow==nID.dwNow) && (dwMax==nID.dwMax) );
	}

	GLPWDATA& operator += ( const GLPWDATA& nID )
	{
		dwNow+=nID.dwNow;
		dwMax+=nID.dwMax;

		return *this;
	}

	GLPWDATA& operator + ( const GLPWDATA& nID )
	{
		dwNow+=nID.dwNow;
		dwMax+=nID.dwMax;

		return *this;
	}

	void TO_FULL ()					{ dwNow = dwMax; }
};

struct GLLLDATA
{
	union
	{
		struct
		{
			LONGLONG	lnData1;
			LONGLONG	lnData2;
		};
		struct
		{
			LONGLONG	lnNow;
			LONGLONG	lnMax;
		};
		struct
		{
			LONGLONG	lnLow;
			LONGLONG	lnHigh;
		};
	};

	GLLLDATA () :
		lnData1(0),
		lnData2(0)
		,lnNow(0)
		,lnMax(0)
		,lnLow(0)
		,lnHigh(0)
	{
	}

	GLLLDATA ( DWORD lnwL, DWORD lnH )
	{
		lnLow = lnwL;
		lnHigh = lnH;
	}

	void LIMIT ()
	{
		if ( lnNow > lnMax )	lnNow = lnMax;
	}

	BOOL ISOVER  ()
	{
		if ( lnNow > lnMax )	return TRUE;
		return FALSE;
	}

	void DECREASE ( const WORD wValue )
	{
		if ( lnNow >= wValue )	lnNow -= wValue;
		else					lnNow = 0;
	}

	BOOL operator== ( const GLLLDATA& nID ) const
	{
		return (lnNow==nID.lnNow) && (lnMax==nID.lnMax);
	}

	BOOL operator!= ( const GLLLDATA& nID ) const
	{
		return !( (lnNow==nID.lnNow) && (lnMax==nID.lnMax) );
	}

	GLLLDATA& operator += ( const GLLLDATA& nID )
	{
		lnNow+=nID.lnNow;
		lnMax+=nID.lnMax;

		return *this;
	}

	GLLLDATA& operator + ( const GLLLDATA& nID )
	{
		lnNow+=nID.lnNow;
		lnMax+=nID.lnMax;

		return *this;
	}
};

enum EMCROW
{
	CROW_PC			= 0,
	CROW_NPC		= 1,
	CROW_MOB		= 2,
	CROW_ITEM		= 3,
	CROW_MONEY		= 4,
	CROW_PET		= 5,	// PetData
	CROW_SUMMON		= 6,	// PetData
	CROW_MATERIAL	= 7,	// ¿Á∑·NPC

	CROW_NUM		= 8
};

enum EMCROW_EX
{
	CROW_EX_PC			= 0x0001,
	CROW_EX_NPC			= 0x0002,
	CROW_EX_MOB			= 0x0004, 
	CROW_EX_ITEM		= 0x0008,
	CROW_EX_MONEY		= 0x0010,
	CROW_EX_PET			= 0x0020,
	CROW_EX_SUMMON		= 0x0040,
	CROW_EX_MATERIAL	= 0x0080,

	CROW_EX_ALL		= ( CROW_EX_PC | CROW_EX_NPC | CROW_EX_MOB | CROW_EX_ITEM | CROW_EX_MONEY | CROW_EX_PET | 
						CROW_EX_SUMMON | CROW_EX_MATERIAL )
};

enum EM_TARGETCONST
{
	EMTARGET_NULL	= -1,
	EMTARGET_NET	= 24,
};

enum EMSKILLCHECK
{
	EMSKILL_OK			= 0,
	EMSKILL_NOTLEARN	= 1,
	EMSKILL_DELAYTIME	= 2,

	EMSKILL_NOTITEM		= 3,
	EMSKILL_NOTARROW	= 4,
	EMSKILL_NOTCHARM	= 5,

	EMSKILL_NOTHP		= 6,
	EMSKILL_NOTMP		= 7,
	EMSKILL_NOTSP		= 8,
	EMSKILL_NOTEXP		= 9, //test skill bullet


	EMSKILL_NOTBULLET	= 10,
	EMSKILL_NOTCP		= 11,

	EMSKILL_NOTREBIRTH  = 12,

	EMSKILL_NOTSKILL	= 13, //add antiskill

	EMSKILL_UNKNOWN		= 999
};


struct STARGETID
{
	EMCROW		emCrow;
	DWORD		dwID;
	D3DXVECTOR3	vPos;

	STARGETID () :
		emCrow(CROW_MOB),
		dwID(EMTARGET_NULL),
		vPos(0,0,0)
	{
	}

	STARGETID ( EMCROW _emcrow, DWORD _dwid ) :
		emCrow(_emcrow),
		dwID(_dwid),
		vPos(0,0,0)
	{
	}
	STARGETID ( EMCROW _emcrow, DWORD _dwid, D3DXVECTOR3 _vpos ) :
		emCrow(_emcrow),
		dwID(_dwid),
		vPos(_vpos)
	{
	}

	void RESET ()
	{
		emCrow = CROW_MOB;
		dwID   = EMTARGET_NULL;
		vPos   = D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX);
	}

	bool operator < ( const STARGETID &starget ) const
	{
		if ( std::make_pair(emCrow,dwID) < std::make_pair(starget.emCrow,starget.dwID) )	return true;
		return false;
	}
	
	bool operator == ( const STARGETID &starget ) const
	{
		return ( starget.dwID == dwID && starget.emCrow == emCrow );
	}

	bool operator != ( const STARGETID &starget ) const
	{
		return ( starget.dwID != dwID || starget.emCrow != emCrow );
	}
};
typedef std::vector<STARGETID>	TARID_VEC;
typedef TARID_VEC::iterator		TARID_VEC_ITER;



struct STARID
{
	WORD		wCrow;
	WORD		wID;

	STARID () 
		: wCrow(0)
		, wID(USHRT_MAX)
	{
	}

	STARID ( WORD _wcrow, WORD _wid ) 
		: wCrow(_wcrow)
		, wID(_wid)
	{
	}

	STARID ( EMCROW _emcrow, DWORD _dwid ) 
		: wCrow((WORD)_emcrow)
		, wID((WORD)_dwid)
	{
	}

	void SET ( const STARGETID &sTARID )
	{
		wCrow = static_cast<WORD>(sTARID.emCrow);
		wID = static_cast<WORD>(sTARID.dwID);
	}

	EMCROW GETCROW () const		{ return static_cast<EMCROW>(wCrow); }
	DWORD GETID() const
	{
		if ( wID==USHRT_MAX )	{ return EMTARGET_NULL; }
		return wID;
	}
};


//	Note : ∞¯∞› ∞≈∏Æ ¿Ø«ÅE
enum EMATT_RGTYPE
{
	EMATT_SHORT	= 0,
	EMATT_LONG	= 1,
	
	EMATT_SIZE	= 2,
};

enum EMDETECT_ENEMY
{
	EMD_PC	= 0x01,
	EMD_MOB	= 0x02,
	EMD_NPC	= 0x04,
};

enum DAMAGE_TYPE
{
	DAMAGE_TYPE_NONE				= 0x0000,
	DAMAGE_TYPE_SHOCK				= 0x0001,	// º˚·©
	DAMAGE_TYPE_CRITICAL			= 0x0002,	// ≈©∏Æ∆ºƒ√
	DAMAGE_TYPE_CRUSHING_BLOW		= 0x0004,	// ∞≠«—≈∏∞›
	DAMAGE_TYPE_PSY_REDUCE			= 0x0008,	// π∞∏Æ »˙ÿÅE
	DAMAGE_TYPE_MAGIC_REDUCE		= 0x0010,	// ∏∂π˝ »˙ÿÅE
	DAMAGE_TYPE_PSY_REFLECTION		= 0x0020,	// π∞∏Æ π›ªÅE
	DAMAGE_TYPE_MAGIC_REFLECTION	= 0x0040,	// ∏∂π˝ π›ªÅE
};

namespace COMMENT
{	
	extern std::string CROW[CROW_NUM];
	extern std::string ATTACK_RGTYPE[EMATT_SIZE];
};

#endif // GLDEFINE_H_