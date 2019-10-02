
#include "GLCharDefine.h"
#include <set>

#pragma once

#define CTF_MAX_REVIVE_GATE			3 
#define CTF_RANKING_NUM				10	//ranking numbers 10 is from top 1 to top 11
#define CTF_RANKING_NAME			33	//number of characters for ranking name
#define CTF_TOWER_MAX				3	//max number of towers info //used in rankings //adjust if more towers is used
#define CTF_TOWER_DAMAGE_VAR		3	//number of damage variable per tower //in case 3 for 3 schools
#define CTF_TOWER_DEFAULT_HOLDER	10	//default value for tower holder

#define CTF_REWARD_NUM				11	// ( CTF_RANKING_NUM + 1 ) reward from top 1 ~ 20  and etch 


enum EMRANKINDEX
{
	EMRANKINDEX_SG		= 0,
	EMRANKINDEX_MP		= 1,
	EMRANKINDEX_PHX		= 2,
	EMRANKINDEX_ALL		= 3,
};

struct SCTF_SCHEDULE
{
	DWORD	dwID;  
	DWORD	dwWeekDay;
	DWORD	dwStartTime;

	SCTF_SCHEDULE()
		: dwID( 0 )
		, dwWeekDay(0)
		, dwStartTime(0)
	{
	}

	SCTF_SCHEDULE ( const SCTF_SCHEDULE &value )
	{
		operator=(value);
	}

	SCTF_SCHEDULE& operator = ( const SCTF_SCHEDULE& rvalue )
	{
		dwID			= rvalue.dwID;
		dwWeekDay		= rvalue.dwWeekDay;
		dwStartTime		= rvalue.dwStartTime;
		return *this;
	}

	bool operator < ( const SCTF_SCHEDULE& sData )
	{			
		if ( dwWeekDay > sData.dwWeekDay ) return true;
		else if ( dwWeekDay == sData.dwWeekDay && dwStartTime < sData.dwStartTime ) return true;
		return  false;
	}

	bool operator == ( const SCTF_SCHEDULE& sData ) 
	{
		if ( dwWeekDay == sData.dwWeekDay && dwStartTime == sData.dwStartTime ) return true;
		return false;
	}
};

struct SCTF_RANK_PLAYER
{
	int		nIndex;   
	DWORD	dwCharID;
	BYTE	cSCHOOL;
	BYTE	cCLASS;
	WORD	wRanking;
	LONGLONG llDAMAGE;
	WORD	wKillNum;
	WORD	wDeathNum;
	char	szCharName[CTF_RANKING_NAME+1];	

	SCTF_RANK_PLAYER()
		: nIndex ( -1 )
		, dwCharID( 0 )
		, cSCHOOL(0)
		, cCLASS(0)
		, wRanking(0)
		, llDAMAGE( 0 )
		, wKillNum(0)
		, wDeathNum(0)
	{
		memset( szCharName, 0, sizeof(char) * (CTF_RANKING_NAME+1) );
	}

	SCTF_RANK_PLAYER ( const SCTF_RANK_PLAYER &value )
	{
		operator=(value);
	}

	SCTF_RANK_PLAYER& operator = ( const SCTF_RANK_PLAYER& rvalue )
	{
		nIndex		= rvalue.nIndex;
		dwCharID	= rvalue.dwCharID;
		llDAMAGE	= rvalue.llDAMAGE;
		cSCHOOL		= rvalue.cSCHOOL;
		cCLASS		= rvalue.cCLASS;
		wRanking	= rvalue.wRanking;
		wKillNum	= rvalue.wKillNum;
		wDeathNum	= rvalue.wDeathNum;
		StringCchCopy( szCharName, CTF_RANKING_NAME+1, rvalue.szCharName );

		return *this;
	}

	bool operator < ( const SCTF_RANK_PLAYER& sRank )
	{		
		if ( llDAMAGE > sRank.llDAMAGE ) return true;
		else if ( llDAMAGE == sRank.llDAMAGE && wKillNum > sRank.wKillNum ) return true;
		else if ( llDAMAGE == sRank.llDAMAGE && wKillNum == sRank.wKillNum && wDeathNum < sRank.wDeathNum ) return true;
		return  false;
	}

	bool operator == ( const SCTF_RANK_PLAYER& sRank ) 
	{
		if ( llDAMAGE == sRank.llDAMAGE && wKillNum == sRank.wKillNum && wDeathNum == sRank.wDeathNum ) return true;
		return false;

	}
};

struct SCTF_RANK_PLAYER_CLIENT
{
	int		nIndex;
	DWORD	dwCharID;
	WORD	wRanking;
	BYTE	cSCHOOL;
	BYTE	cCLASS;
	LONGLONG llDAMAGE;
	WORD	wKillNum;
	WORD	wDeathNum;
	char	szCharName[CTF_RANKING_NAME+1];	

	SCTF_RANK_PLAYER_CLIENT() 
		: nIndex(-1)
		, wRanking (0)
		, llDAMAGE( 0 )
		, wKillNum(0)
		, wDeathNum(0)
		, cSCHOOL(0)
		, cCLASS(0)
	{
		memset( szCharName, 0, sizeof(char) * (CTF_RANKING_NAME+1) );
	}

	SCTF_RANK_PLAYER_CLIENT ( const SCTF_RANK_PLAYER_CLIENT &value )
	{
		operator=(value);
	}

	SCTF_RANK_PLAYER_CLIENT& operator = ( const SCTF_RANK_PLAYER_CLIENT& rvalue )
	{
		nIndex		= rvalue.nIndex;
		wRanking	= rvalue.wRanking;
		llDAMAGE	= rvalue.llDAMAGE;
		wKillNum	= rvalue.wKillNum;
		wDeathNum	= rvalue.wDeathNum;
		cSCHOOL		= rvalue.cSCHOOL;
		cCLASS		= rvalue.cCLASS;
		dwCharID	= rvalue.dwCharID;

		StringCchCopy( szCharName, CTF_RANKING_NAME+1, rvalue.szCharName );

		return *this;
	}

	SCTF_RANK_PLAYER_CLIENT ( const SCTF_RANK_PLAYER &value )
	{
		operator=(value);
	}

	SCTF_RANK_PLAYER_CLIENT& operator = ( const SCTF_RANK_PLAYER& rvalue )
	{
		nIndex		= rvalue.nIndex;
		wRanking	= rvalue.wRanking;
		llDAMAGE	= rvalue.llDAMAGE;
		wKillNum	= rvalue.wKillNum;
		wDeathNum	= rvalue.wDeathNum;
		cSCHOOL		= rvalue.cSCHOOL;
		cCLASS		= rvalue.cCLASS;
		dwCharID	= rvalue.dwCharID;

		StringCchCopy( szCharName, CTF_RANKING_NAME+1, rvalue.szCharName );

		return *this;
	}
};

struct SCTF_TOWERDATA
{
	LONGLONG 	llDAMAGE;
	WORD		wSCHOOL;

	SCTF_TOWERDATA() :
		llDAMAGE(0)
		, wSCHOOL(CTF_TOWER_DEFAULT_HOLDER)
	{
	}
};

//struct for holding tower damages
struct SCTF_SCORE_TOWER
{ 
	SNATIVEID		sCROWID;
	SCTF_TOWERDATA 	sDATA[CTF_TOWER_DAMAGE_VAR];
	WORD			wOWNER;
	WORD			wOWNERLAST;
	LONGLONG		llOwnerDamage;

	SCTF_SCORE_TOWER():
		sCROWID( false )
		, wOWNER( CTF_TOWER_DEFAULT_HOLDER )
		, wOWNERLAST( CTF_TOWER_DEFAULT_HOLDER )
	{
		for ( int i = 0; i < CTF_TOWER_DAMAGE_VAR; ++ i )
		{
			sDATA[i].llDAMAGE = 0;
			sDATA[i].wSCHOOL = i;
		}
	}

	SCTF_SCORE_TOWER ( const SCTF_SCORE_TOWER &value )
	{
		operator=(value);
	}

	SCTF_SCORE_TOWER& operator = ( const SCTF_SCORE_TOWER& rvalue )
	{
		sCROWID		= rvalue.sCROWID;
		wOWNER		= rvalue.wOWNER;
		wOWNERLAST	= rvalue.wOWNERLAST;

		for ( int i = 0; i < CTF_TOWER_DAMAGE_VAR; ++ i )
		{
			sDATA[i] = rvalue.sDATA[i];
		}

		return *this;
	}
};


struct SCTF_HOLDER
{
	int		nIndex;  
	WORD	wRanking;
	WORD	wSCHOOL;
	WORD	wOWNED;
	LONGLONG llDAMAGE;
	
	SCTF_HOLDER()
		: nIndex ( -1 )
		, wRanking(0)
		, wSCHOOL(0)
		, wOWNED(0)
		, llDAMAGE( 0 )
	{
	}

	SCTF_HOLDER ( const SCTF_HOLDER &value )
	{
		operator=(value);
	}

	SCTF_HOLDER& operator = ( const SCTF_HOLDER& rvalue )
	{
		nIndex		= rvalue.nIndex;
		wRanking	= rvalue.wRanking;
		wSCHOOL		= rvalue.wSCHOOL;
		wOWNED		= rvalue.wOWNED;
		llDAMAGE	= rvalue.llDAMAGE;
		return *this;
	}

	bool operator < ( const SCTF_HOLDER& sRank )
	{		
		if ( wOWNED > sRank.wOWNED ) return true;
		else if ( wOWNED == sRank.wOWNED && llDAMAGE > sRank.llDAMAGE ) return true;
		return  false;
	}

	bool operator == ( const SCTF_HOLDER& sRank ) 
	{
		if ( wOWNED == sRank.wOWNED && llDAMAGE == sRank.llDAMAGE  ) return true;
		return false;

	}
};

struct SCTF_RANK_SELF
{
	WORD	wRanking;
	LONGLONG llDAMAGE;
	WORD	wKillNum;
	WORD	wDeathNum;
	BYTE	cSCHOOL;
	BYTE	cCLASS;
	BOOL	bVALID;

	SCTF_RANK_SELF()
		: wRanking(0)
		, llDAMAGE( 0 )
		, wKillNum (0)
		, wDeathNum(0)
		, cSCHOOL(0)
		, cCLASS(0)
		, bVALID( FALSE )
	{
	}

	void Init()
	{
		wRanking	= 0;
		llDAMAGE	= 0;
		wKillNum	= 0;
		wDeathNum	= 0;
		cSCHOOL		= 0;
		cCLASS		= 0;
		bVALID		= FALSE;
	}
};

typedef std::map< DWORD, SCTF_RANK_PLAYER >		CTF_RANK_PLAYER_MAP;
typedef CTF_RANK_PLAYER_MAP::iterator			CTF_RANK_PLAYER_MAP_ITER;

typedef std::vector<SCTF_RANK_PLAYER>			CTF_RANK_PLAYER_VEC;
typedef CTF_RANK_PLAYER_VEC::iterator			CTF_RANK_PLAYER_VEC_ITER;

typedef std::vector<SCTF_RANK_PLAYER_CLIENT>	CTF_RANK_PLAYER_CLIENT_VEC;
typedef CTF_RANK_PLAYER_CLIENT_VEC::iterator	CTF_RANK_PLAYER_CLIENT_VEC_ITER;

typedef std::map< DWORD, SCTF_SCORE_TOWER >		CTF_SCORE_TOWER_MAP;
typedef CTF_SCORE_TOWER_MAP::iterator			CTF_SCORE_TOWER_MAP_ITER;

typedef std::vector<SCTF_SCORE_TOWER>			CTF_SCORE_TOWER_VEC;
typedef CTF_SCORE_TOWER_VEC::iterator			CTF_SCORE_TOWER_VEC_ITER;


typedef std::map< WORD, SCTF_HOLDER >			SCTF_HOLDER_MAP;
typedef SCTF_HOLDER_MAP::iterator				SCTF_HOLDER_MAP_ITER;

typedef std::vector<SCTF_HOLDER>				SCTF_HOLDER_VEC;
typedef SCTF_HOLDER_VEC::iterator				SCTF_HOLDER_VEC_ITER;

typedef std::set<DWORD>							CTF_AWARD_CHAR;
typedef CTF_AWARD_CHAR::iterator				CTF_AWARD_CHAR_ITER;

typedef std::map< DWORD, SCTF_SCHEDULE >		SCTF_SCHEDULE_MAP;
typedef SCTF_SCHEDULE_MAP::iterator				SCTF_SCHEDULE_MAP_ITER;

typedef std::vector<SCTF_SCHEDULE>				SCTF_SCHEDULE_VEC;
typedef SCTF_SCHEDULE_VEC::iterator				SCTF_SCHEDULE_VEC_ITER;

struct SCTF_AWARD_ITEM
{
	SNATIVEID	nAwardItem[CTF_REWARD_NUM];
	DWORD		dwAwardLimit;
	DWORD		dwKillMin;

	SCTF_AWARD_ITEM()
		: dwAwardLimit(CTF_REWARD_NUM)
		, dwKillMin( 0 )
	{	
		memset( nAwardItem, -1, sizeof( SNATIVEID ) * CTF_REWARD_NUM );
	}
};


/*
                 .,-:-,,.
                .AMMMHMMHHMII,
              .AMMHHMMMHHMMHMMMHHA.
            .AMHHMMMMHIMMMMMMHMHHHHHL
           .AHHIHHMMHIMMMMMMMHMHHHMHLH:
          ,LHHIIHHHHIHMHMMMMMHMHHHLHHAIA
         ;IHHIHHMMH:IHMHMMMMMMHMHIHLIHHIA
        .:IHHII:':'..:.:IHMHMMHHHHIHHLIHH.
       ,I:AVI::.'. .'.'.::IAHMHMHHIALVAIHA
      ,A:AVI::.'. .   . '.:IAVMMHAVLVAIVHHA
     .II:AHI:.'. .      . ':IAVHMHMAHVHIHHH;
    ,A:H:HI::.  .      . .'.:IAIHHAMAIAHIHHLA
   .AIH:AHI:'.            .'.:IIAHHMMAHHIHHIH,
  .AHI:AHI:.:..            .'.VIIHMHMMAIHIHIIA
  ;HHI:AHI:',,'   .    .,:AHVVL:IIHIHMMHHHIHIM;
  ;AII:HIPPT:TPHA. .  .::''. . .VIHHMHMAHIHI:HM
 ;IAIV:HI::.,,,,:'. .  .,:III::.:VIHHHMMHHHHIIHB
 AIHI:HII:I:VCLTV;:.  ..VK CVTPA::IHMHHMHHIHIHV
.LHH::HIHI:IA.TL/::.  ..'VPTTI:'':IIHHHIHMIIHH'
;IHHIHIHHI:. ' '..:.  ..  .'. ' .':HIHMHHMMHIH
IHMHIHIHHI:.   . .:'  . .. .     .:IHHMMMMMHIV
IHHMIHIHHI:.   ..:'.  .. ':. .  ..:HIHMMMMMHV'
HHMHIHIHHI::. ..::L..:-;. ':.. . .:IHMMHMMHIP
HHMHIIHIHHI:.:. .. :''.   .':.. ..:IHMMMHMHV
HIHMMHHHIHI::. ..,.,, ,,,,,.,:.. .:IHMMHMMM'
IIHHIMHMHIHI::. 'LP:'''''''P/. . .:IHMMMHMV
:IIHHMMHMHHII:.. V:-,,,,-''. .  ..:IMHMMMM'
 'IHHMMHHMHHHA:.''::;;;::/' . . .::IMHMMMM
 ;IHMMMHHHMHMHA:...'''''     . ..::':VHHMH:
 :IHHMMHMHHMMMHA:.. .      . ..::'.'.':VHV
 ;IHIHMHHIHMMHMMMA.. . . ...:::'.'.  .. T,
 :IIHMMHIHIHMMMMMMAAL::.::.::':. .   .    ,:.
 ;HIHHMHHIHHMHMMMMMHMHHIHI::.:.. : .   .   AHAA.
.AHIHMMMHMHMHMMHMMMMHMHII::.:.. . .  .  ..:HMMH:
AHV':HHMHHMHMMMHMMMMMHHI::.:.. ..      . .AOAVA/'-..
:I''VHHMMMHHMMMHMMMMHMHI::... :. .   . ..AOOLV/.:.:.:''--...,.
'  .AHIHHMHHMMMMHMMMMMMMI:.... :.    . .AAVAV/.:. . .:  .    .''''-.
  ,:HIIHHMMHMMMMHMMMMHMHI: .:.:: .  . .:ANOO/.:   .: . .  . ..   .. ',,
 ,;P':IHIHHMMHMMMMMMMMHMI:.  .:.. . ..AVAOV/'   .. .:.. .. .       . HA.
,AH::AHIHHHMHMMMMMMMMMMHMA:. .::. ..:.OAVO/. '...::.::.. .  .        HHA
  ' :IIHIHHMHMMMMMMMMMHMHH:..:::.:..AOAVO/:.'..::.:..::.. .       .  HHH
  .::IHHIHMMHMMMMMMMMHMMHII.:.::'.:AOOAV/..: .:.:..:. . .  .   . . . HHH
 ,IHIHHIHMHMMMMMMMHMMHMV:.::::'. .:AOOVV/:.: .:. ..:.. .  .  ..  . . HHH
.:IHHIHHHMHMMMMMMMMMHMV::....:. .:/AOAV/. .:.:.. .. .   . .  . .. . IHHH
 :IHHHMHMMMHMMMMMMHMHHI::...:...:/AOAV/..: :. :.  ..   .    .  .. . AHHH
AIHMHHMMHMMMMMMMMHMHHII:.. .:. ./OAOV/:..:... .   .    .   .  .. .. HHHH
HIHIHHMMHHMHMMHMHHHIHI::.. . ./AO/A//...:.. .   .    .      . .. .  HHHH
HHV'AHHHMHMHHHHIOIHIIII::..../AO/AV/ ..:.:..   .      .    . .. . ..::VH
V'.:HHHMMHMMHHIHOIHHIII:::../VOAVV/.'...:. . .   .       .  . ..::.::III
 .:HHHHMMHMHHMHOOIIII:I:::./OAHVO/: ..:.. . .  .   .       . .. .::::III
.:HHIHHMHMMMHHIOOIHII:::..OO//AO/.. .::.. .  . .     .    . .. .::::IIIH
HIHIIHHMMHMMMHHIOOIII:::.OOO/AO//..:..:..  . ..  .  .     .. ..I:::IIIHH
IHHIIHHMHMMHHIHI:OOO;:.OO/A:AO//. ...:.. ..  .  .          . .:IAI::IIIH
HHIHHHVVHMMHHIHI:::OOOO:O/.AO//. .. .... . ..  .          . ..:IIAI::IIH
VHHHV'.:HMHHIHHI::.:..A/A:AVO/:. . ... ..  . .   .      . ..:.:IIHAHIIII
 VHV   VHHAIVHI:.'...A/A:AOOV/... . .. .  .   .        . ..:.::IIHMHAIIH
       'VHIHA'.'O:O:W:.:A/AO/.. .. .  .   .  .         .. .:..::IHMMHIII
       :V:I:I:.:... ..:A:IOO:.:.. . .  . ....          . ..:.:::IHHHHHII
       O:I:I::. .. . /A/:IOO::. .. .  ..:::::.        . ..:.::::IHMHHVII
      O.I:.. .  . .:AV.:.IO:::.. .    ..:II::..       .. .:.::::IHMHHIII
     O :I:. .  .  /A:...IOO::.. .. . . ..::.:.       . ...:.::::IHMHVIII
     O.:I.      .AW'. ..IOI::.:.. .. .  .:.:.        . .:..:::::IMHHIIII
    ,::.I.  ..AHW'  ...IOII:I:.:.. .. .. .  .  .    . ..:..:.:::IMMVIIII
   B:I:.:I.AHW'     . :IOII:I::.:... ... .. ..  . . ....::.:.:::IMMHIIII
   'VHHHHV:' .     . :V.OO:I::.:... .:.. ... .. .. ..:::. .::.::AHMVIIII
     V:. .V.    . . :V:HOO:II::.::.:. :.... ..:...::I::. ...::::MHMIIIII
     ':.. .V.. . .:V:.A:OO:III::::::.::..:.:.:I.::::.. . .. .:::MMHIIIII
      ':....V:OOO;V..:W:OO::IIII:II::II:I:I:II:::::.    .. ..:::MHHAIIII
       '::.:..'.'. ..W:.OO.:II:::II::IIII:II:::.:..    .  ...:::MMHMIIII
        ':I:.:.:....W:..OO:::II:::::I::::::..:..    .'.    ..:::MMHVIIII
         ':III::.:.W/::OO:::.:I::I:::::.:.:.. .. .. ..    ...:::MMHIIIII
          OO'WII:::W:I:OO::..:I:::II::..:... .. ... .     ..:::AMMMIIIHH
          'O O'WI:W:II:OO.:..:.:II:::I:..:... ... .      . ..::MHVIIIHHH
           OO'OOOV::II:OO:.. .::.:II::.:.. .. .. .    . .:..::AMMIIIIHHH
            O   II:.:::OO.:.. ...:.:II:.:.. ... . . .  ...:.::HMMIIIIHHH
            OO  A:::.:OO:... . ...:.:I.::.:... . . .  . ..:::AMHMIIIIHHH
            OO AM::.::OO::... . ...:.:.:.:.:..:.. . .. ...::IMMMMIIIIHHH
             O HHM.:.:OO::.. . . .:.:.:.:.:..:... .. .  ..:AMHMMMIHIIHHI
             OOMM..:.:OO.:... . ...:...:..:.:..:.. .. . ..:HHMMHMIHIIHHI
            AMOOV..:.:OO:.:... . . ..:..:..:.::..:.. .. .:AHHMMMMIHIIHHH
           AMMOO.:.:::OO::.:.:.. . .:..:....::..:.::..:.:IHHMMMHVIHHIHHH
          AMMMOO.::.:OO::..:..:.. ...:..:..:..:..:.::.:::IHHMMMHAIHHIHHH
         AMMMM'OO::::OO:::..:... .. ...:..:..:..:.:.:::.:IHHMMMHIHHHIHHH
         MMMV..:OO::OO:::.::.::.... .:...:...:.:..::.::::IHHMMMHIHHHIHHH
        AMM'... .:OOO::::.:::..:..:. ..:. .:..:..:.::::.:::HHMMMIHHIIHHH
       AMM' . .. .:::::.:::.::...:.:. . .. . ..::.::.:::::IIVMMVIHHIIHHH
       MM' .  . .:.:.::I:.:.:.:::..::.. . .. ..::..::.::I:IIIVMIIHHIIHHH
      AM' .. . . .::.:.::I:.::.:.:::..:. . . . ..:..::.:I:IIIIVIHHHIIHHH
     AM' . ... . ..:::.::..::.:::..:..:.. .  .. .:.:.:I:IIIHIIVIHHHIIHHH
    AMV .. .. .  .. .::.::..:.::::.:.:. .. . ... ..:I:IIIHIH:IIHHHHIIHII
   AMV . .. ...  . .:. :.:...:I:..:.:.:.. . .:. ..:.:.:IIHIHH:AHHHHIIHII
  AMM' .. .. ...  ..:::... . NV::..:..:.. .... ..:.:::IIHIHHI:HHHHIIIIII
 AMMV . ... .:.. ..: ..:. . . .  .:..:. . .. .:..::::IIIHIHHI:VHHHHIIIIH
AMMM' .. .:. .... .::..:.. . .. . ..  .. . ..:...:::I:IHIHHHH:I:VHHHHIII
MMMV . ... ... ...::. ...:.. ... . ...:..:..:.:.::I:I:IHIHHVII::HHHHHHIH
MMM'. ... .:..:..:...:... ..:. .. ...:.....::.:.:::I:IHHIHHIII:AHHHHHI'H
MMV .. ....:.::.:..:... ... ..:.... .. ..:.. .:...I:IIHIHHVIII.HHHHHH' H
MMI ... ..::..::...::... . .:..:...:... ...:..:..:::IIIHIHIIIV.HHHHHH AH
MM'.. ... ..::.:::..::...:.:.:. .:...:..:..:.:..::::I:IIHIIII..HHHHHH HH
MM.. .....:.::..::.:.:.::..::.::..::... ...:.::.:::I:IIHIHIII..HHHHHVAHH
MV...: ..:.:::.::.:.:::..:.:.:::.:.:.:.:..:..:::.:::IIHIHIHHV.AHIHHH'AHH
MI.. ..:..::::I:.:.::.:::.:::.:.:::.:.:.:.:.:I:.:::I:IIHIHVHI.HHHHHH.HHH
MI.. . ..:..:::I::.::..:.:.:.:.:.::.::..:.:II::.::::I:IHIIVH:.HHHHHH.HIH
MI... . ..:..:::II::I::.:.I.:.:.:.::.::II:I:.:.:.::I:IIIIVHV:AHHHHHHA IH
MA.:..:. ..:. .::IIHHHI:I.IHI.::I:I:I:I::.::. ..:..::I:IIHHIIHHHHHHHH IH
MM..:...... . .::IHHHIHIIHHIHIIH:IHII:::. .:.. ..:.:::IIAHHIHHHHHHHHV HH
MM.:. .:... .:..:IHHMHWHMHMWMHMHMIIH::..:.. ..:..:.::IIAHHHIHHIHHHHH' IH
MM:..:.:. .. ...::IMMHWMMHMWMMHMHHMI:.:. ... . .::.:IIHAHHHIHIIH HHH  IH
MM::.:. ... .. ..:IMWMMWMWMWMMMWHII.:... ... . ..:.:.:IHIHHIHHIV HHH  IH
MMI::.:. ... .. .::VMMMMWMWMWMMHV:.:.. . . .. ..:.:..:IHIIHHHMM AHHH. IH
MMA:::.:.:. . . ..::VMMMMMWMMMHV:.:... . .  ....:..:.:IHHIHHHHMMMHIHI IH
MMM::::.:.:. . ....::VMMMMMMMV:::.:. . ..  . ... .:..:IHIIHHHHMMMHIHI IH
MMMI:::.:. . ... ...::VMMMWMV::..:... . . . .. .::..:IIHIIHHHHHHHIHHI.'H
MMHM:::..:.. .. ...:.::IWMMV:::.:.. .. . . . ...:.:.:IIHIIHHMHHHHIHHI
MHMMI:::.:. . ... ...:::II:::.:... .. .. . . . :.:.:IIHIIHHHMMHHHIIHII
HIHMA::::.:. .. ... ..::II::.:.:.. . . . .. . :.:.:.IIHIVVIHIIHHHHHHII
IVVMM::::.:.:. . ... .::II:.::..:.. .. .. . . .:.:::IHH:.:HHIIHIHH':-'
'::VMI:::.:.:.. .. . .::II.::.:.:. .. .. . . ..:..::IHH..:HIIIHIHH
    HA::::.:..  ... ...:II.:.:.:... . .. .. ..:..:.:IHII..HHIIHIHI
    HM:::::.:. . .. ...:II.::.:.::.. ...  .  ..:.:::IHIH..HIIIHIH'
   IHMA:::.:... .. .. .:II:.:.::.:.. .. .. .. .:.:::HHIH..VIIIHIH
   HHHM::::.:.. .. ....::II:.:..:.:.. . . . . ..::::HIHH...HIIHHH
   HHMMA::::.:. . .. ..::II.:.:.:.:... . . .. .:.:::HIHHA..HHHHHV
   ''MMM:::::.:. . .. .::II:.:.::.:.. .. .. . .:::::HIHHH..HHHHVI
     VMMI::::.:. ... ..:::II:.:.::.:.. .. . . .:.:::H:HHI...IHHII
      MHA:::.:.. .. ....::II.:.:.::. . ... . . .::::I:HI I..IHHHV
      MMM::::.:. . .. ..::IA:.:.:.:.. .. .. .. ..:::I.H:.I..IHVH
      V'HA:::..:. .. .. ::IIH:.:.:.:.. .. ..  ..:.:I:.II.I.:VV'V
          :::..:... .. .::IIH..:.::.:.. . ... . .:.::.II:I::'III
          ':::.:.. ... .::IIH::.:.:.:. .. .. . .:..::.::.:::  HI
           ::::.:.. .. .::IIH:.:.::.:. . .. . . .:...:.:.:.'  HI
           '::::.. .. ..::IIH::.::.:.:.. ... . . .:.:.:.:.:   II
*/
                                                               