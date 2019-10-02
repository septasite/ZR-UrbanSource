#include "stdafx.h"
#include "GLogicEx.h"
#include "GLItemMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
namespace GLOGICEX
{

};//
BOOL GLCHARLOGIC::DOPERFECTGRINDING (	SITEMCUSTOM &sCusItem, 
								const SITEM *pHold, 
								bool &_bRESET, 
								bool &_bTERMINATE, 
								EMANTIDISAPPEAR &emANTIDISAPPEAR )								
{
   	bool bSUCCEED(false);
	_bRESET = false;
	_bTERMINATE = false;

	const EMGRINDING_TYPE emGRINDING = pHold->sGrindingOp.emTYPE;
	const EMGRINDER_TYPE emGRINDINGRESIST = pHold->sGrindingOp.emGRINDER_TYPE;
	const SITEMCUSTOM& sHOLD_ITEM = GET_HOLD_ITEM();
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sHOLD_ITEM.sNativeID );
	BYTE cGRADE = sCusItem.GETGRADE ( emGRINDING );
    // stop me when im working - weapon types :p Eduj
	 if ( !pItem->sBasicOp.IsPerfectGrinder() ) 
		 return FALSE;
    // stop me when im working - weapon types :p Eduj
	if ( emGRINDINGRESIST == EMGRINDER_RESIST_FIRE 
		|| emGRINDINGRESIST == EMGRINDER_RESIST_ICE
		|| emGRINDINGRESIST == EMGRINDER_RESIST_ELEC
		|| emGRINDINGRESIST == EMGRINDER_RESIST_POISON
		|| emGRINDINGRESIST == EMGRINDER_RESIST_SPIRIT 
		|| emGRINDINGRESIST == EMGRINDER_DUMMY6  ) 
		return FALSE;

	if ( emGRINDING == EMGRINDING_DAMAGE || emGRINDING == EMGRINDING_DEFENSE )
	{
		if ( cGRADE >= GLCONST_CHAR::wGRADE_MAX )	
			return FALSE;
	}
	else
	{
		if ( cGRADE >= GLCONST_CHAR::wGRADE_MAX_REGI )	
			return FALSE;
	}
	
	switch ( pHold->sGrindingOp.emTYPE )
	{
	case EMGRINDING_DAMAGE:
		{
			//1
			if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY1 ) 
			{
				int iMin=1; int iMax=1;	
				int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
				sCusItem.cDAMAGE = (BYTE)n;
			}
			else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=1; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=1; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=1; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=1; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}
			else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY6 )
			{
				int iMin=1; int iMax=6;	
				int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
				sCusItem.cDAMAGE = (BYTE)RandomNumber(1,6);//(BYTE)n;		
			}
			else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=1; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=1; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;	
			}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=1; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=1; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			//2
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=2; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=2; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=2; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=2; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=2; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=2; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=2; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;	
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=2; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=2; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=2; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			//3
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=3; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=3; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=3; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=3; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=3; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=3; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=3; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=3; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=3; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=3; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;	
				
			//4
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=4; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=4; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=4; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=4; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=4; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=4; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=4; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=4; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=4; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=4; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			//5
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=5; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;				
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=5; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;				
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=5; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;				
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=5; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;				
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=5; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=5; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=5; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;				
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=5; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;				
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=5; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=5; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			//6
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=6; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=6; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=6; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=6; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=6; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=6; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=6; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=6; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=6; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=6; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			//7
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=7; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=7; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=7; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=7; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=7; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=7; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=7; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=7; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=7; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=7; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			//8
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=8; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=8; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=8; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=8; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=8; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=8; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=8; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=8; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=8; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=8; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			//9
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=9; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=9; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=9; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=9; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=9; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=9; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=9; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=9; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=9; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=9; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			//10
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
			int iMin=10; int iMax=1;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
			int iMin=10; int iMax=2;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
			int iMin=10; int iMax=3;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;		
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
			int iMin=10; int iMax=4;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
			int iMin=10; int iMax=5;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
			int iMin=10; int iMax=6;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
			int iMin=10; int iMax=7;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
			int iMin=10; int iMax=8;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
			int iMin=10; int iMax=9;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
			}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
			int iMin=10; int iMax=10;	
			int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
			sCusItem.cDAMAGE = (BYTE)n;			
		// AUTO + 11 ~ 20
			}else if( pHold->sGrindingOp.emLOW==LDUMMY11 && pHold->sGrindingOp.emHIGH==HDUMMY11 ){
			sCusItem.cDAMAGE = (BYTE)11;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY12 && pHold->sGrindingOp.emHIGH==HDUMMY12 ){
			sCusItem.cDAMAGE = (BYTE)12;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY13 && pHold->sGrindingOp.emHIGH==HDUMMY13 ){
			sCusItem.cDAMAGE = (BYTE)13;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY14 && pHold->sGrindingOp.emHIGH==HDUMMY14 ){
			sCusItem.cDAMAGE = (BYTE)14;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY15 && pHold->sGrindingOp.emHIGH==HDUMMY15 ){
			sCusItem.cDAMAGE = (BYTE)15;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY16 && pHold->sGrindingOp.emHIGH==HDUMMY16 ){
			sCusItem.cDAMAGE = (BYTE)16;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY17 && pHold->sGrindingOp.emHIGH==HDUMMY17 ){
			sCusItem.cDAMAGE = (BYTE)17;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY18 && pHold->sGrindingOp.emHIGH==HDUMMY18 ){
			sCusItem.cDAMAGE = (BYTE)18;
			}else if( pHold->sGrindingOp.emLOW==LDUMMY19 && pHold->sGrindingOp.emHIGH==HDUMMY19 ){
			sCusItem.cDAMAGE = (BYTE)19;
			}
			else if( pHold->sGrindingOp.emLOW==LDUMMY20 && pHold->sGrindingOp.emHIGH==HDUMMY20 )
			{
				sCusItem.cDAMAGE = (BYTE)20;
			}
			// PERPECT GRINDING W/OUT FAIL ++ || Eduj Developments
			else if ( pHold->sGrindingOp.emLOW==LDUMMY0 && pHold->sGrindingOp.emHIGH==HDUMMY0 )
			{
				sCusItem.cDAMAGE++;
			}
			break;
		}
	case EMGRINDING_DEFENSE:
		{	//1
	if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY1 ) {
	int iMin=1; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=1; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=1; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=1; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=1; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=1; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=1; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
    }else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=1; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;	
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=1; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY1 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=1; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
    //2
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=2; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=2; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=2; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
    }else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=2; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=2; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=2; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=2; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;	
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=2; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=2; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY2 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=2; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	//3
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=3; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=3; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=3; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
    }else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=3; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=3; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=3; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=3; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=3; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=3; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY3 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=3; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;	
		
	//4
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=4; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=4; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=4; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=4; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=4; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=4; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=4; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=4; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=4; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY4 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=4; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	//5
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=5; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;				
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=5; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;				
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=5; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;				
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=5; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;				
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=5; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=5; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=5; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;				
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=5; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;				
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=5; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY5 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=5; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
    //6
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=6; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=6; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=6; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=6; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=6; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=6; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=6; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=6; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=6; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY6 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=6; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	//7
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=7; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=7; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=7; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=7; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=7; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=7; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=7; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=7; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=7; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY7 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=7; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	//8
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=8; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=8; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=8; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=8; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=8; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=8; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=8; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=8; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=8; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY8 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=8; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	//9
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=9; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=9; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=9; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=9; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=9; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=9; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=9; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=9; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=9; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY9 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=9; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
    //10
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY1 ){
	int iMin=10; int iMax=1;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY2 ){
	int iMin=10; int iMax=2;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY3 ){
	int iMin=10; int iMax=3;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;		
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY4 ){
	int iMin=10; int iMax=4;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY5 ){
	int iMin=10; int iMax=5;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY6 ){
	int iMin=10; int iMax=6;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY7 ){
	int iMin=10; int iMax=7;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY8 ){
	int iMin=10; int iMax=8;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY9 ){
	int iMin=10; int iMax=9;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;			
	}else if( pHold->sGrindingOp.emLOW==LDUMMY10 && pHold->sGrindingOp.emHIGH==HDUMMY10 ){
	int iMin=10; int iMax=10;	
	int n = ((rand() % (abs(iMax-iMin)+1))+iMin);
	sCusItem.cDEFENSE = (BYTE)n;
// AUTO + 11 ~ 20
	}else if( pHold->sGrindingOp.emLOW==LDUMMY11 && pHold->sGrindingOp.emHIGH==HDUMMY11 ){
	sCusItem.cDEFENSE = (BYTE)11;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY12 && pHold->sGrindingOp.emHIGH==HDUMMY12 ){
	sCusItem.cDEFENSE = (BYTE)12;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY13 && pHold->sGrindingOp.emHIGH==HDUMMY13 ){
	sCusItem.cDEFENSE = (BYTE)13;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY14 && pHold->sGrindingOp.emHIGH==HDUMMY14 ){
	sCusItem.cDEFENSE = (BYTE)14;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY15 && pHold->sGrindingOp.emHIGH==HDUMMY15 ){
	sCusItem.cDEFENSE = (BYTE)15;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY16 && pHold->sGrindingOp.emHIGH==HDUMMY16 ){
	sCusItem.cDEFENSE = (BYTE)16;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY17 && pHold->sGrindingOp.emHIGH==HDUMMY17 ){
	sCusItem.cDEFENSE = (BYTE)17;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY18 && pHold->sGrindingOp.emHIGH==HDUMMY18 ){
	sCusItem.cDEFENSE = (BYTE)18;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY19 && pHold->sGrindingOp.emHIGH==HDUMMY19 ){
	sCusItem.cDEFENSE = (BYTE)19;
	}else if( pHold->sGrindingOp.emLOW==LDUMMY20 && pHold->sGrindingOp.emHIGH==HDUMMY20 ){
	sCusItem.cDEFENSE = (BYTE)20;

// PERPECT GRINDING W/OUT FAIL ++ || Eduj Developments
	}else if ( pHold->sGrindingOp.emLOW==LDUMMY0 && pHold->sGrindingOp.emHIGH==HDUMMY0 )
	{
      sCusItem.cDEFENSE++;
	}
	break;
	}
};
 
	return TRUE;
}

	